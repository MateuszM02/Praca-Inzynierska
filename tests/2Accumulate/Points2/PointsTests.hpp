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
        return CopyableUIntPair(i, i);
    }

    static CopyableUIntPair reverseSortedGenerator(const unsigned int i)
    {
        return CopyableUIntPair(UINT32_MAX - i, i);
    }
};

} // namespace tests::Accumulate
