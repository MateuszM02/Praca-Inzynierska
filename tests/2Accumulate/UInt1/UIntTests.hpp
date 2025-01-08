#pragma once

#include "../AccumulateTestFixture.hpp"


namespace tests::Accumulate
{

struct UIntAccumulateArgs final : public AccumulateTestStruct<unsigned int>
{
    explicit UIntAccumulateArgs(
        unsigned int (*f)(const unsigned int),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<unsigned int>(
        TestType::AccumulateUint,
        std::make_shared<Accumulator<unsigned int>>(
            initTestData<std::vector<unsigned int>>(f, n),
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
