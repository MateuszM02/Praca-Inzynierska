#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/3Merge/Points1/Points.hpp"

#include <functional>
#include <random>

namespace tests::Merge::Points1tests
{

struct PointsArgs : public MergeTestStruct<Points1::Point2D>
{
    PointsArgs(
        const std::string& path,
        VectorStruct<Points1::Point2D> vectors);
};

class PointsFixture : public MergeTestFixture<Points1::Point2D>
{
public:
    static Points1::Point2D fmod3i3_mod7i64(const unsigned int i)
    {
        return { 3*i + (i % 3), 7*i % 64 };
    }

    static Points1::Point2D f3i_mod9i64(const unsigned int i)
    {
        return { 3*i, 9*i % 64 };
    }
};

TEST_P(PointsFixture, pointsTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge::Points1tests
