#include "DynamicFeaturesFixture.hpp"
#include <utility>

namespace tests::Wrapper
{

TEST_F(DynamicFeatureTestFixture, DynamicIntVectorTest) 
{
    VerifyMoveCopyWorks<IntVector, false>(IntVector({ 11, 1, 2025, 15, 26 }));

    // posortowane rosnaco - kolejnosc leksykograficzna
    static const IntVector v1({ 1 });
    static const IntVector v2({ 1, 2 });
    static const IntVector v3({ 3 });
    static const IntVector v4({ 3, 4 });
    static const IntVector v5({ 3, 5 });
    static const IntVector v6({ 4, 1 });
    static const std::vector<IntVector> inVector = { v2, v4, v6, v1, v5, v3 };

    static const Point2D<IntVector> minMaxResult(v1, v6);
    VerifyMinMaxWorks(inVector, minMaxResult);
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
    VerifyMoveCopyWorks<Point2D<int>, true>(Point2D(15, 26));

    // posortowane rosnaco - liczy sie najpierw 1 wspolrzedna x, potem druga y jesli x1 = x2
    static const Point2D<int> p1(1, 12);
    static const Point2D<int> p2(5, 2);
    static const Point2D<int> p3(5, 5);
    static const Point2D<int> p4(6, 1);
    static const Point2D<int> p5(10, 1);
    static const std::vector<Point2D<int>> inVector = { p2, p4, p1, p5, p3 };

    static const Point2D<Point2D<int>> minMaxResult(p1, p5);
    VerifyMinMaxWorks(inVector, minMaxResult);

    static const std::vector<Point2D<int>> nthResult1 = { p1, p4, p2, p5, p3 };
    static const std::vector<Point2D<int>> nthResult3 = { p2, p1, p3, p5, p4 };
    static const std::vector<Point2D<int>> nthResult5 = { p4, p2, p3, p1, p5 };
    VerifyNthFinderWorks(inVector, 0, nthResult1);
    VerifyNthFinderWorks(inVector, 2, nthResult3);
    VerifyNthFinderWorks(inVector, 4, nthResult5);
}

TEST_F(DynamicFeatureTestFixture, DynamicRandomStringTest) 
{
    VerifyMoveCopyWorks<RandomString, true>(RandomString(4));
}

} // namespace tests::Wrapper
