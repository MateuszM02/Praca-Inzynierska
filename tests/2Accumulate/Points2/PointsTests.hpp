#pragma once

#include "../../../src/Structures/CustomPairImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

struct PointsAccumulateArgs final : public AccumulateTestStruct<CopyableUIntPair>
{
    explicit PointsAccumulateArgs(
        CopyableUIntPair (*dataCreator)(const unsigned int),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<CopyableUIntPair>(
        TestType::AccumulatePoints,
        [dataCreator, n, accType]()
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

TEST_P(PointsAccumulateFixture, PointsAccumulateTest)
{
    VerifyTestCustomFor2(GetParam());
}

} // namespace tests::Accumulate
