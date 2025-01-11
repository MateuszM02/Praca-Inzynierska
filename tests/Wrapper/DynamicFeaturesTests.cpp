#include "DynamicFeaturesFixture.hpp"

namespace tests::Wrapper
{

TEST_F(DynamicFeatureTestFixture, DynamicIntVectorTest) 
{
    VerifyEverythingWorks<IntVector, false>(IntVector({ 11, 1, 2025, 15, 26 }));
}

TEST_F(DynamicFeatureTestFixture, DynamicMatrixTest) 
{
    static const std::vector<int> inVec1{ 11, 1 };
    static const std::vector<int> inVec2{ 20, 25 };
    static const std::vector<std::vector<int>> outVec{ inVec1, inVec2 };
    VerifyEverythingWorks<Matrix<int>, false>(Matrix<int>(outVec));
}

TEST_F(DynamicFeatureTestFixture, DynamicPoint2DTest) 
{
    VerifyEverythingWorks<Point2D, true>(Point2D(15, 26));
}

TEST_F(DynamicFeatureTestFixture, DynamicRandomStringTest) 
{
    VerifyEverythingWorks<RandomString, true>(RandomString(4));
}

} // namespace tests::Wrapper
