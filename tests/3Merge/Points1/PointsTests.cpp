#include "PointsTests.hpp"

namespace tests::Merge::Points1tests
{
void PointsTest::createTest(
    const std::vector<Points1::Point2D>& v1,
    const std::vector<Points1::Point2D>& v2,
    const src::MethodType& methodType)
{ 
    auto merger = Points1::Points(); 
    runTest(merger, v1, v2, methodType);
}
} // namespace tests::Merge::Points1tests
