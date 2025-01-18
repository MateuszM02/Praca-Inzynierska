#pragma once

#include "../Algorithms/NthFinder.hpp"
#include "../Algorithms/Generator.hpp"
#include "RandomString.hpp"

#define nth first
#define numberOfElements second

using namespace src::Algorithms;
using namespace src::Structures;

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie RandomString
class RandomStringImpl final
{
private:
    using StrGenerator = Generator<std::string, CopyableRandomString>;
    
    static std::string creator(CopyableRandomString& currentState)
    {
        return currentState();
    }

    static StrGenerator
    createGeneratorData(const unsigned int vectorSize, const unsigned int length)
    {
        return StrGenerator(vectorSize, CopyableRandomString(length), creator);
    }

public:
    RandomStringImpl() = delete;

    static std::shared_ptr<StrGenerator> 
    createGenerator(const unsigned int vectorSize, const unsigned int length)
    {
        StrGenerator generator = createGeneratorData(vectorSize, length);
        return std::make_shared<StrGenerator>(std::move(generator));
    }

    static std::shared_ptr<NthFinder<std::vector<std::string>>> createFinder(
        const unsigned int length, const TestPair& info)
    {
        const StrGenerator& generator = createGeneratorData(info.numberOfElements, length);
        std::vector<std::string> elements;
        elements.reserve(info.numberOfElements);
        for (unsigned int i = 0; i < info.numberOfElements; i++)
        {
            elements.emplace_back(generator.create());
        }

        NthFinderData<std::vector<std::string>> data(std::move(elements), info.nth);
        return std::make_shared<NthFinder<std::vector<std::string>>>(std::move(data));
    }
};

} // namespace src::Structures
