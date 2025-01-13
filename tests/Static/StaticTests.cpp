#include "StaticFixture.hpp"
#include <utility>

namespace tests::Static
{

// Matrix
static const std::vector<int> vec1{ 11, 1 };
static const std::vector<int> vec2{ 20, 25 };
static const std::vector<std::vector<int>> vecOfVecs{ vec1, vec2 };
static const Matrix<int> m1(vecOfVecs);

// IntVector - posortowane rosnaco - kolejnosc leksykograficzna
static const IntVector iv1({ 1 });
static const IntVector iv2({ 1, 2 });
static const IntVector iv3({ 3 });
static const IntVector iv4({ 3, 4 });
static const IntVector iv5({ 3, 5 });
static const IntVector iv6({ 4, 1 });

static const std::vector<IntVector> ivVector = { iv2, iv4, iv6, iv1, iv5, iv3 };
static const std::set<IntVector> ivSet = { iv2, iv4, iv6, iv1, iv5, iv3 };

// Point2D - posortowane rosnaco - liczy sie najpierw 1 wspolrzedna x, potem druga y jesli x1 = x2
static const Point2D<int> p1(1, 12);
static const Point2D<int> p2(5, 2);
static const Point2D<int> p3(5, 5);
static const Point2D<int> p4(6, 1);
static const Point2D<int> p5(10, 1);

static const std::vector<Point2D<int>> pointVector = { p2, p4, p1, p5, p3 };
static const std::set<Point2D<int>> pointSet = { p2, p4, p1, p5, p3 };

// przykladowe napisy wygenerowane przez RandomString - posortowane rosnaco
static const std::string s1 = "cccc";
static const std::string s2 = "ccccc";
static const std::string s3 = "cccd";
static const std::string s4 = "daaa";
static const std::string s5 = "daaaa";

static const std::vector<std::string> stringVector = { s2, s4, s1, s5, s3 };

// testy poprawnosci dzialania konstruktorow/operatorow kopiujacych/przenoszacych
TEST_F(StaticTestFixture, MoveCopyTest)
{
    VerifyMoveCopyWorks<IntVector, false>(iv6);
    VerifyMoveCopyWorks<Matrix<int>, false>(m1);
    VerifyMoveCopyWorks<Point2D<int>, true>(p5);
    VerifyMoveCopyWorks<RandomString, true>(RandomString(4));
}

// 1. MinMax
TEST_F(StaticTestFixture, MinMaxTest)
{
    static const Point2D<Point2D<int>> minMaxIntResult(p1, p5);
    VerifyMinMaxWorks(pointVector, minMaxIntResult);
    VerifyMinMaxWorks(pointSet, minMaxIntResult);

    static const Point2D<IntVector> minMaxIvResult(iv1, iv6);
    VerifyMinMaxWorks(ivVector, minMaxIvResult);
    VerifyMinMaxWorks(ivSet, minMaxIvResult);
}

// TODO:
// 2. Accumulate
// 3. Merge
// 4. Sort
// 5. Transform
// 6. ???

// 7. Nth element
TEST_F(StaticTestFixture, NthElementTest) 
{
    static const std::vector<Point2D<int>> nthPointResult1 = { p1, p4, p2, p5, p3 };
    static const std::vector<Point2D<int>> nthPointResult3 = { p2, p1, p3, p5, p4 };
    static const std::vector<Point2D<int>> nthPointResult5 = { p4, p2, p3, p1, p5 };

    VerifyNthFinderWorks(pointVector, 0, nthPointResult1);
    VerifyNthFinderWorks(pointVector, 2, nthPointResult3);
    VerifyNthFinderWorks(pointVector, 4, nthPointResult5);

    static const std::vector<std::string> nthStringResult1 = { s1, s4, s2, s5, s3 };
    static const std::vector<std::string> nthStringResult3 = { s2, s1, s3, s5, s4 };
    static const std::vector<std::string> nthStringResult5 = { s4, s2, s3, s1, s5 };

    VerifyNthFinderWorks(stringVector, 0, nthStringResult1);
    VerifyNthFinderWorks(stringVector, 2, nthStringResult3);
    VerifyNthFinderWorks(stringVector, 4, nthStringResult5);
}

// TODO:
// 8. Regex
// 9. Remove erase if
// 10. Generate

} // namespace tests::Static
