#pragma once

#include "../Algorithms/NthFinder.hpp"
#include "../Algorithms/Generator.hpp"
#include "RandomString.hpp"

using namespace src::Algorithms;
using namespace src::Structures;

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie RandomString
class RandomStringImpl final
{
private:
    using StrGenerator = Generator<std::string, RandomString>;
    
    static std::string creator(RandomString& currentState)
    {
        return currentState();
    }

    static StrGenerator
    createGeneratorData(const unsigned int vectorSize, const unsigned int length)
    {
        return StrGenerator(vectorSize, RandomString(length), creator);
    }

public:
    RandomStringImpl() = delete;

    static std::shared_ptr<StrGenerator> 
    createGenerator(const unsigned int vectorSize, const unsigned int length)
    {
        const StrGenerator& generator = createGeneratorData(vectorSize, length);
        return std::make_shared<StrGenerator>(generator);
    }

    static std::shared_ptr<NthFinder<std::vector<std::string>>> createFinder(
        const unsigned int n,
        const unsigned int vectorSize,
        const unsigned int length)
    {
        const StrGenerator& generator = createGeneratorData(vectorSize, length);
        std::vector<std::string> elements;
        elements.reserve(vectorSize);
        for (unsigned int i = 0; i < vectorSize; i++)
        {
            elements.emplace_back(generator.create());
        }

        NthFinderData<std::vector<std::string>> data(elements, n);
        return std::make_shared<NthFinder<std::vector<std::string>>>(data);
    }
};

} // namespace src::Structures
