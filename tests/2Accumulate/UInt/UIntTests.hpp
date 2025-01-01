#pragma once

#include "../AccumulateTestFixture.hpp"


namespace tests::Accumulate
{

struct UIntAccumulateArgs : public AccumulateTestStruct<unsigned int>
{
    UIntAccumulateArgs(
        unsigned int (*f)(const unsigned int),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<unsigned int>(
        AccumulateUint,
        std::make_shared<Accumulator<unsigned int>>(
            AccumulateTestFixture<unsigned int>::initTestData(f, n),
            accType))
    { }
};

class UIntAccumulateFixture : public AccumulateTestFixture<unsigned int>
{
public:
    static unsigned int sortedGenerator(const unsigned int i)
    {
        return i;
    }

    static unsigned int reverseSortedGenerator(const unsigned int i)
    {
        return UINT32_MAX - i;
    }
};

TEST_P(UIntAccumulateFixture, UIntAccumulateTest)
{ 
    VerifyTestCustomFor2(GetParam());
}

} // namespace tests::Accumulate
