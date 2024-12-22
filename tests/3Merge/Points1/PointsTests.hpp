#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;

namespace tests::Merge
{

struct PointsArgs : public MergeTestStruct<Point2D>
{
    PointsArgs(
        DataWrapper<Point2D> (*fun1)(const unsigned int),
        DataWrapper<Point2D> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    : MergeTestStruct<Point2D>(
        MergePoints,
        std::move(std::make_shared<Merger<Point2D>>(
            MergeTestFixture<Point2D>::initTestData(fun1, fun2, n1, n2))))
    { }
};

class PointsFixture : public MergeTestFixture<Point2D>
{
public:
    static DataWrapper<Point2D> fmod3i3_mod7i64(const unsigned int i)
    {
        return { { 3*i + (i % 3), 7*i % 64 }, Point2DImpl::equal, Point2DImpl::less };
    }

    static DataWrapper<Point2D> f3i_mod9i64(const unsigned int i)
    {
        return { { 3*i, 9*i % 64 }, Point2DImpl::equal, Point2DImpl::less };
    }
};

TEST_P(PointsFixture, pointsMergeTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge
