#pragma once

#include "../../../src/Structures/PointsImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

struct PointsAccumulateArgs final : public AccumulateTestStruct<Point2D>
{
    explicit PointsAccumulateArgs(
        Point2D (*dataCreator)(const unsigned int),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<Point2D>(
        TestType::AccumulatePoints,
        [dataCreator, n, accType]()
        {
            std::vector<Point2D> data =
                initTestData<std::vector<Point2D>>(dataCreator, n);
            return std::make_shared<Accumulator<Point2D>>(std::move(data), accType);
        })
    { }
};

class PointsAccumulateFixture : public AccumulateTestFixture<Point2D>
{
public:
    static Point2D sortedGenerator(const unsigned int i)
    {
        return Point2D(i, i);
    }

    static Point2D reverseSortedGenerator(const unsigned int i)
    {
        return Point2D(UINT32_MAX - i, i);
    }
};

TEST_P(PointsAccumulateFixture, PointsAccumulateTest)
{
    VerifyTestCustomFor2(GetParam());
}

} // namespace tests::Accumulate
