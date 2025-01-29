#pragma once

#include "../AccumulateTestFixture.hpp"

namespace tests::Accumulate
{

using Base = BaseTestStruct<AccResults<unsigned int>>;
using Parent = AccumulateTestStruct<unsigned int>;

struct UIntAccumulateArgs final : public Parent
{
    explicit UIntAccumulateArgs(
        unsigned int (*dataCreator)(const unsigned int),
        AccType accType,
        const unsigned int n)
    : Parent(TestType::AccumulateUint,
        [dataCreator, accType, n]()
        {
            std::vector<unsigned int> data =
                initTestData<std::vector<unsigned int>>(dataCreator, n);
            return std::make_shared<Accumulator<unsigned int>>(std::move(data), accType);
        })
    { }
};

class UIntAccumulateFixture : public AccumulateTestFixture<unsigned int>
{
public:
    static unsigned int sortedGenerator(const unsigned int i)
    {
        return i;
    }
};

} // namespace tests::Accumulate
