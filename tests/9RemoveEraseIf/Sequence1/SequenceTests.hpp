#pragma once

#include "../RemoveEraseIfTestFixture.hpp"

#include <cmath> // std::pow, std::sqrt

namespace tests::RemoveEraseIf
{

using Container1 = std::vector<unsigned int>;
using Base1 = BaseTestStruct<Container1>;
using Parent1 = RemoveEraseIfTestStruct<Container1>;

struct SequenceRemoveEraseIfArgs final : public Parent1
{
    explicit SequenceRemoveEraseIfArgs(
        bool(*predicate)(const unsigned int&),
        const unsigned int n)
    : Parent1(TestType::RemoveEraseIfSequence,
        [predicate, n]()
        {
            return initTestData9(identity, predicate, n);
        })
    { }

    static unsigned int identity(const unsigned int n)
    {
        return n;
    }
};

class SequenceRemoveEraseIfFixture : public RemoveEraseIfTestFixture<Container1>
{
public:
    // predykaty
    static bool isNotPrime(const unsigned int value)
    {
        if (value <= 1) return true;
        else if (value == 2) return false;
        else if (value % 2 == 0) return true;

        for (unsigned int div = 3; div < std::sqrt(value); div+=2)
        {
            if (value % div == 0)
                return true;
        }
        return false;
    }

    static bool isMersenneNumber(const unsigned int& value)
    {
        unsigned int p = 2;
        while (true)
        {
            unsigned int mersenneNumber = std::pow(2, p) - 1;

            if (mersenneNumber == value)
                return true;
            else if (mersenneNumber > value)
                return false;

            p++;
            while (isNotPrime(p))   p++;
        }
    }

    static bool hasAtMost4Divisors(const unsigned int& value)
    {
        if (value < 2) return true;
        unsigned int divisors = 2;
        const unsigned int sqrtValue = std::sqrt(value);
        for (unsigned int div = 2; div <= sqrtValue; ++div)
        {
            if (value % div == 0)
            {
                if (div * div == value) divisors += 1;
                else divisors += 2;
            }
            if (divisors > 4) return false;
        }
        return divisors <= 4;
    }

    static bool is1toNSumOdd(const unsigned int& value)
    {
        unsigned int sum = 0;
        for (unsigned int i = 1; i <= value; i++)
        {
            sum = (sum + i) % 2;
        }

        return sum == 1;
    }
};

} // namespace tests::RemoveEraseIf
