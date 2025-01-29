#pragma once

#include "../../../src/Structures/CustomPairImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

using Base = BaseTestStruct<AccResults<CopyableUIntPair>>;
using Parent = AccumulateTestStruct<CopyableUIntPair>;

struct PointsAccumulateArgs final : public Parent
{
    explicit PointsAccumulateArgs(
        CopyableUIntPair (*dataCreator)(const unsigned int),
        AccType accType,
        const unsigned int n)
    : Parent(TestType::AccumulatePoints,
        [dataCreator, accType, n]()
        {
            std::vector<CopyableUIntPair> data =
                initTestData<std::vector<CopyableUIntPair>>(dataCreator, n);
            return std::make_shared<Accumulator<CopyableUIntPair>>(std::move(data), accType);
        })
    { }
};

class PointsAccumulateFixture : public AccumulateTestFixture<CopyableUIntPair>
{
public:
    static CopyableUIntPair sortedGenerator(const unsigned int i)
    {
        unsigned int arg1 = i;
        unsigned int arg2 = i;
        return CopyableUIntPair(std::move(arg1), std::move(arg2));
    }
};

} // namespace tests::Accumulate
