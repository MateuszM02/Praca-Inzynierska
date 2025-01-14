#pragma once

#include <random>

#include "BaseWrapper.hpp"

namespace src::Structures
{

template <bool MoveEnabled, bool CopyEnabled>
class RandomString final : BaseWrapper<MoveEnabled, CopyEnabled>
{
public:
    explicit RandomString(const unsigned int l)
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &length_, &randomGenerator_, &distribution_ })
    , length_{l}
    , randomGenerator_{std::random_device{}()}
    , distribution_{'a', 'z'}
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

    // potrzebne do testow konstruktorow/operatorow kopiujacych/przenoszacych
    bool operator==(const RandomString& other) const
    {
        return  this->length_ == other.length_ &&
                this->randomGenerator_ == other.randomGenerator_ &&
                this->distribution_.a() == other.distribution_.a() &&
                this->distribution_.b() == other.distribution_.b();
    }

    bool operator!=(const RandomString& other) const
    {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const RandomString& rs)
    {
        os << "[RandomString (dlugosc slowa: " << rs.length_ << ")]";
        return os;
    }

private:
    unsigned int length_;
    mutable std::mt19937 randomGenerator_;
    mutable std::uniform_int_distribution<char> distribution_;
};

using CopyableRandomString = RandomString<ENABLE_MOVE, ENABLE_COPY>;

} // namespace src::Structures
