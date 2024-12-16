#pragma once
#include "../RemoveEraseIfTestFixture.hpp"
#include "../../Path.hpp"

#include <cmath>

namespace tests::RemoveEraseIf
{

template <Removable Container = std::vector<unsigned int>>
struct SequenceArgs final : public RemoveEraseIfTestStruct<unsigned int>
{
    SequenceArgs(
        const std::string& path,
        RemoverData<unsigned int, Container> elements);
};

class SequenceIntFixture : public RemoveEraseIfTestFixture<unsigned int>
{
public:
    static unsigned int identity(const unsigned int n)
    {
        return n;
    }

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
        unsigned int p = 1;
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
        unsigned int divisors = 2;
        const unsigned int sqrtValue = std::sqrt(value);
        for (unsigned int div = 2; div < sqrtValue; div++)
        {
            if (value % div == 0)
                divisors += 2;
        }
        if (value % sqrtValue)
            divisors++;
        return divisors <= 4;
    }

    static bool is1toNSumOdd(const unsigned int& value)
    {
        unsigned int sum = 0;
        for (unsigned int i = 1; i < value; i++)
        {
            sum = (sum + i) % 2;
        }
        
        return sum == 0;
    }
};

TEST_P(SequenceIntFixture, SequenceRemoveEraseIfTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::RemoveEraseIf
