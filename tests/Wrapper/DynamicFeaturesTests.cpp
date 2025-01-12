#include "DynamicFeaturesFixture.hpp"

namespace tests::Wrapper
{

TEST_F(DynamicFeatureTestFixture, DynamicIntVectorTest) 
{
    VerifyMoveCopyWorks<IntVector, false>(IntVector({ 11, 1, 2025, 15, 26 }));
}

TEST_F(DynamicFeatureTestFixture, DynamicMatrixTest) 
{
    static const std::vector<int> inVec1{ 11, 1 };
    static const std::vector<int> inVec2{ 20, 25 };
    static const std::vector<std::vector<int>> outVec{ inVec1, inVec2 };
    VerifyMoveCopyWorks<Matrix<int>, false>(Matrix<int>(outVec));
}

TEST_F(DynamicFeatureTestFixture, DynamicPoint2DTest) 
{
    VerifyMoveCopyWorks<Point2D, true>(Point2D(15, 26));

    // posortowane rosnaco - liczy sie najpierw 1 wspolrzedna x, potem druga y jesli x1 = x2
    const Point2D p1(1, 12);
    const Point2D p2(5, 2);
    const Point2D p3(5, 5);
    const Point2D p4(6, 1);
    const Point2D p5(10, 1);

    const std::vector<Point2D> inVector = { p2, p4, p1, p5, p3 };
    const std::vector<Point2D> result1 = { p1, p4, p2, p5, p3 };
    const std::vector<Point2D> result3 = { p2, p1, p3, p5, p4 };
    const std::vector<Point2D> result5 = { p4, p2, p3, p1, p5 };

    VerifyNthFinderWorks<std::vector<Point2D>>(inVector, 0, result1);
    VerifyNthFinderWorks<std::vector<Point2D>>(inVector, 2, result3);
    VerifyNthFinderWorks<std::vector<Point2D>>(inVector, 4, result5);
}

TEST_F(DynamicFeatureTestFixture, DynamicRandomStringTest) 
{
    VerifyMoveCopyWorks<RandomString, true>(RandomString(4));
}

} // namespace tests::Wrapper
