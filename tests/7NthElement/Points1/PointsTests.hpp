#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

struct PointsArgs : public NthElementTestStruct<Point2D>
{
    PointsArgs(
        DataWrapper<Point2D> (*fun)(const unsigned int),
        const unsigned int n,
        const unsigned int vectorSize)
    : NthElementTestStruct<Point2D>(
        NthElementPoints,
        std::move(std::make_shared<NthFinder<Point2D>>(
            NthElementTestFixture<Point2D>::initTestData(fun, n, vectorSize))))
    { }
};

class PointsNthElementFixture : public NthElementTestFixture<Point2D>
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

TEST_P(PointsNthElementFixture, PointsNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

} // namespace tests::NthElement
