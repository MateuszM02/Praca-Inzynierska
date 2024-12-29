#pragma once

#include "../AccumulateTestFixture.hpp"

using namespace src::Wrappers;

namespace tests::Accumulate
{

struct UIntAccumulateArgs : public AccumulateTestStruct<unsigned int>
{
    UIntAccumulateArgs(
        AccumulableWrapper<unsigned int> (*f)(const unsigned int),
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
    static AccumulableWrapper<unsigned int> sortedGenerator(const unsigned int i)
    {
        return { i, std::plus<unsigned int>(), std::equal_to<unsigned int>(), std::less<unsigned int>() };
    }

    static AccumulableWrapper<unsigned int> reverseSortedGenerator(const unsigned int i)
    {
        return { UINT32_MAX - i, std::plus<unsigned int>(), std::equal_to<unsigned int>(), std::less<unsigned int>() };
    }
};

TEST_P(UIntAccumulateFixture, UIntAccumulateTest)
{ 
    VerifyTestCustomFor2(GetParam());
}

} // namespace tests::Accumulate
