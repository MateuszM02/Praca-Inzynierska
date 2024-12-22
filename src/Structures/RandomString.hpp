#pragma once

#include <random>

namespace src::Structures
{

struct RandomString
{
    RandomString(const unsigned int l) 
    : length(l)
    , randomGenerator(std::random_device{}())
    , distribution('a', 'z')
    { }

    unsigned int length;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<> distribution;
};

} // namespace src::Structures
