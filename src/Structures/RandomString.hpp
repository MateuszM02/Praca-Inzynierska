#pragma once

#include <random>

#include "BaseWrapper.hpp"

using namespace src::Structures;

namespace src::Structures
{

class RandomString final : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>
{
public:
    explicit RandomString(const unsigned int l)
    : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>({ &length_, &randomGenerator_, &distribution_ })
    , length_(l)
    , randomGenerator_(std::random_device{}())
    , distribution_('a', 'z')
    { }

    std::string operator()() const
    {
        std::string randomString;
        randomString.reserve(length_);
        for (unsigned int i = 0; i < length_; ++i)
        {
            randomString += distribution_(randomGenerator_);
        }
        return randomString;
    }

private:
    unsigned int length_;
    mutable std::mt19937 randomGenerator_;
    mutable std::uniform_int_distribution<char> distribution_;
};

} // namespace src::Structures
