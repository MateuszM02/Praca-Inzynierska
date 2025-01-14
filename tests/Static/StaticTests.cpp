#include "StaticFixture.hpp"
#include <utility>

namespace tests::Static
{

// Matrix
Matrix<int> M1() 
{
    std::vector<std::vector<int>> vecOfVecs{ { 11, 1 }, { 20, 25 } };
    Matrix<int> m(std::move(vecOfVecs));
    return m;
}

// IntVector - posortowane rosnaco - kolejnosc leksykograficzna
IntVector iv1() { return IntVector({ 1 }); }
IntVector iv2() { return IntVector({ 1, 2 }); }
IntVector iv3() { return IntVector({ 3 }); }
IntVector iv4() { return IntVector({ 3, 4 }); }
IntVector iv5() { return IntVector({ 3, 5 }); }
IntVector iv6() { return IntVector({ 4, 1 }); }

std::vector<IntVector> IvVector() { return { iv2(), iv4(), iv6(), iv1(), iv5(), iv3() }; }
std::set<IntVector> IvSet() { return { iv2(), iv4(), iv6(), iv1(), iv5(), iv3() }; }

// Point2D - posortowane rosnaco - liczy sie najpierw 1 wspolrzedna x, potem druga y jesli x1 = x2

Point2D<int> p1() { return Point2D(1, 12); }
Point2D<int> p2() { return Point2D(5, 2); }
Point2D<int> p3() { return Point2D(5, 5); }
Point2D<int> p4() { return Point2D(6, 1); }
Point2D<int> p5() { return Point2D(10, 1); }

std::vector<Point2D<int>> PointVector() { return { p2(), p4(), p1(), p5(), p3() }; }
std::set<Point2D<int>> PointSet() { return { p2(), p4(), p1(), p5(), p3() }; }

// przykladowe napisy wygenerowane przez RandomString - posortowane rosnaco
std::string s1() { return "cccc"; }
std::string s2() { return "ccccc"; }
std::string s3() { return "cccd"; }
std::string s4() { return "daaa"; }
std::string s5() { return "daaaa"; }

std::vector<std::string> stringVector() { return { s2(), s4(), s1(), s5(), s3() }; }

// testy poprawnosci dzialania konstruktorow/operatorow kopiujacych/przenoszacych
TEST_F(StaticTestFixture, MoveCopyTest)
{
    VerifyMoveCopyWorks<IntVector, false>(iv6());
    VerifyMoveCopyWorks<Matrix<int>, false>(M1());
    VerifyMoveCopyWorks<Point2D<int>, true>(p5());
    VerifyMoveCopyWorks<RandomString, true>(RandomString(4));
}

// 1. MinMax
TEST_F(StaticTestFixture, MinMaxTest)
{
    Point2D<Point2D<int>> minMaxIntResult(p1(), p5());
    VerifyMinMaxWorks(PointVector(), minMaxIntResult);
    VerifyMinMaxWorks(PointSet(), minMaxIntResult);

    Point2D<IntVector> minMaxIvResult(iv1(), iv6());
    VerifyMinMaxWorks(IvVector(), minMaxIvResult);
    VerifyMinMaxWorks(IvSet(), minMaxIvResult);
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
    std::vector<Point2D<int>> nthPointResult1 = { p1(), p4(), p2(), p5(), p3() };
    std::vector<Point2D<int>> nthPointResult3 = { p2(), p1(), p3(), p5(), p4() };
    std::vector<Point2D<int>> nthPointResult5 = { p4(), p2(), p3(), p1(), p5() };

    VerifyNthFinderWorks(PointVector(), 0, nthPointResult1);
    VerifyNthFinderWorks(PointVector(), 2, nthPointResult3);
    VerifyNthFinderWorks(PointVector(), 4, nthPointResult5);

    std::vector<std::string> nthStringResult1 = { s1(), s4(), s2(), s5(), s3() };
    std::vector<std::string> nthStringResult3 = { s2(), s1(), s3(), s5(), s4() };
    std::vector<std::string> nthStringResult5 = { s4(), s2(), s3(), s1(), s5() };

    VerifyNthFinderWorks(stringVector(), 0, nthStringResult1);
    VerifyNthFinderWorks(stringVector(), 2, nthStringResult3);
    VerifyNthFinderWorks(stringVector(), 4, nthStringResult5);
}

// TODO:
// 8. Regex
// 9. Remove erase if
// 10. Generate

} // namespace tests::Static
