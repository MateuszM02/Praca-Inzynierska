#pragma once

#include "../Algorithms/10Generate/Generator.hpp"
#include "RandomString.hpp"

using namespace src::Algorithms;

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie RandomString
class RandomStringImpl final
{
public:
    RandomStringImpl() = delete;

    using GeneratorPtr = std::shared_ptr<Generator<std::string, RandomString>>;

    static GeneratorPtr createGenerator(
        const unsigned int n,
        const unsigned int length) 
    {
        RandomString rs(length);
        GeneratorData<std::string, RandomString> data(n, rs,
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
        return std::make_shared<Generator<std::string, RandomString>>(std::move(data));
    }
};

} // namespace src::Structures
