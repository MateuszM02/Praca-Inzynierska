#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/3Merge/Points1/Points.hpp"

namespace tests::Merge::Points1tests
{
class PointsTest : MergeTestFixture<Points1::Point2D>
{ 
public:
    void createTest(
        const std::vector<Points1::Point2D>& v1,
        const std::vector<Points1::Point2D>& v2,
        const src::MethodType& methodType) override;
};
} // namespace tests::Merge::Points1tests
