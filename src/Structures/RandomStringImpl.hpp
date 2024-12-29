#pragma once

#include "../Algorithms/NthFinder.hpp"
#include "../Algorithms/Generator.hpp"
#include "RandomString.hpp"

using namespace src::Algorithms;
using namespace src::Wrappers;

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie RandomString
class RandomStringImpl final
{
private:
    static GenerableWrapper<std::string, RandomString> createGeneratorData(
        const unsigned int vectorSize,
        const unsigned int length)
    {
        RandomString rs(length);
        GenerableWrapper<std::string, RandomString> data(vectorSize, rs,
            [](const RandomString& initialState, RandomString& currentState)
            {
                std::string randomString;
                randomString.reserve(currentState.length);
                for (unsigned int i = 0; i < currentState.length; ++i)
                {
                    randomString += currentState.distribution(currentState.randomGenerator); 
                }
                return randomString;
            });
        return data;
    }

public:
    RandomStringImpl() = delete;

    using GeneratorPtr = std::shared_ptr<Generator<std::string, RandomString>>;

    static GeneratorPtr createGenerator(
        const unsigned int vectorSize,
        const unsigned int length)
    {
        return std::make_shared<Generator<std::string, RandomString>>(
            createGeneratorData(vectorSize, length));
    }

    template <NthElementCompatible Container = std::vector<ComparableWrapper<std::string>>>
    using FinderPtr = std::shared_ptr<NthFinder<std::string, Container>>;

    template <NthElementCompatible Container = std::vector<ComparableWrapper<std::string>>>
    static FinderPtr<> createFinder(
        const unsigned int n,
        const unsigned int vectorSize,
        const unsigned int length)
    {
        GenerableWrapper<std::string, RandomString> generator = createGeneratorData(vectorSize, length);
        Container elements;
        elements.reserve(vectorSize);
        for (unsigned int i = 0; i < vectorSize; i++)
        {
            elements.emplace_back(generator(), std::equal_to<std::string>(), std::less<std::string>());
        }

        NthFinderData<std::string> data(std::move(elements), n);
        return std::make_shared<NthFinder<std::string>>(std::move(data));
    }
};

} // namespace src::Structures
