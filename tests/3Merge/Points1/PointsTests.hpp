#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;
using namespace src::Wrappers;

namespace tests::Merge
{

struct PointsMergeArgs : public MergeTestStruct<Point2D>
{
    PointsMergeArgs(
        ComparableWrapper<Point2D> (*fun1)(const unsigned int),
        ComparableWrapper<Point2D> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    : MergeTestStruct<Point2D>(
        MergePoints,
        std::move(std::make_shared<Merger<Point2D>>(
            MergeTestFixture<Point2D>::initTestData(fun1, fun2, n1, n2))))
    { }
};

class PointsMergeFixture : public MergeTestFixture<Point2D>
{
public:
    static ComparableWrapper<Point2D> fmod3i3_mod7i64(const unsigned int i)
    {
        return { { 3*i + (i % 3), 7*i % 64 }, Point2DImpl::equal, Point2DImpl::less };
    }

    static ComparableWrapper<Point2D> f3i_mod9i64(const unsigned int i)
    {
        return { { 3*i, 9*i % 64 }, Point2DImpl::equal, Point2DImpl::less };
    }
};

TEST_P(PointsMergeFixture, PointsMergeTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge
