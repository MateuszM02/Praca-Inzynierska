#pragma once

#include "../../../src/Structures/PointsImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

struct PointsAccumulateArgs final : public AccumulateTestStruct<Point2D>
{
    explicit PointsAccumulateArgs(
        Point2D (*f)(const unsigned int)&,
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<Point2D>(
        TestType::AccumulatePoints,
        std::make_shared<Accumulator<Point2D>>(
            initTestData(f, n),
            accType))
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
