#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/Structures/Points.hpp"

using namespace src::Structures;

namespace tests::Merge
{

struct PointsArgs : public MergeTestStruct<Point2D>
{
    PointsArgs(
        const std::string& path,
        VectorStruct<Point2D> vectors);
};

class PointsFixture : public MergeTestFixture<Point2D>
{
public:
    static Mergeable<Point2D> fmod3i3_mod7i64(const unsigned int i)
    {
        return { { 3*i + (i % 3), 7*i % 64 },
                 src::Algorithms::MergerImpl::pointEqFunc,
                 src::Algorithms::MergerImpl::pointLessFunc,
                 src::Algorithms::MergerImpl::pointCopyAssignFunc };
    }

    static Mergeable<Point2D> f3i_mod9i64(const unsigned int i)
    {
        return { { 3*i, 9*i % 64 },
                 src::Algorithms::MergerImpl::pointEqFunc,
                 src::Algorithms::MergerImpl::pointLessFunc,
                 src::Algorithms::MergerImpl::pointCopyAssignFunc };
    }
};

TEST_P(PointsFixture, pointsTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge
