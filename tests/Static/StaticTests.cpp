#include "StaticFixture.hpp"
#include <utility>

namespace tests::Static
{

// CopyableMatrix
CopyableMatrix<int> M1() 
{
    std::vector<std::vector<int>> vecOfVecs{ { 11, 1 }, { 20, 25 } };
    CopyableMatrix<int> m(std::move(vecOfVecs));
    return m;
}

// CopyableIntVector - posortowane rosnaco - kolejnosc leksykograficzna
CopyableIntVector iv1() { return CopyableIntVector({ 1 }); }
CopyableIntVector iv2() { return CopyableIntVector({ 1, 2 }); }
CopyableIntVector iv3() { return CopyableIntVector({ 3 }); }
CopyableIntVector iv4() { return CopyableIntVector({ 3, 4 }); }
CopyableIntVector iv5() { return CopyableIntVector({ 3, 5 }); }
CopyableIntVector iv6() { return CopyableIntVector({ 4, 1 }); }

std::vector<CopyableIntVector> IvVector() { return { iv2(), iv4(), iv6(), iv1(), iv5(), iv3() }; }
std::set<CopyableIntVector> IvSet() { return { iv2(), iv4(), iv6(), iv1(), iv5(), iv3() }; }

// CopyablePair - posortowane rosnaco - liczy sie najpierw 1 wspolrzedna x, potem druga y jesli x1 = x2

CopyablePair<int> p1() { return CopyablePair(1, 12); }
CopyablePair<int> p2() { return CopyablePair(5, 2); }
CopyablePair<int> p3() { return CopyablePair(5, 5); }
CopyablePair<int> p4() { return CopyablePair(6, 1); }
CopyablePair<int> p5() { return CopyablePair(10, 1); }

std::vector<CopyablePair<int>> PointVector() { return { p2(), p4(), p1(), p5(), p3() }; }
std::set<CopyablePair<int>> PointSet() { return { p2(), p4(), p1(), p5(), p3() }; }

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
    VerifyMoveCopyWorks<CopyableIntVector, false>(iv6());
    VerifyMoveCopyWorks<CopyableMatrix<int>, false>(M1());
    VerifyMoveCopyWorks<CopyablePair<int>, true>(p5());
    VerifyMoveCopyWorks<CopyableRandomString, true>(CopyableRandomString(4));
}

// 1. MinMax
TEST_F(StaticTestFixture, MinMaxTest)
{
    CopyablePair<CopyablePair<int>> minMaxIntResult(p1(), p5());
    VerifyMinMaxWorks(PointVector(), minMaxIntResult);
    VerifyMinMaxWorks(PointSet(), minMaxIntResult);

    CopyablePair<CopyableIntVector> minMaxIvResult(iv1(), iv6());
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
    std::vector<CopyablePair<int>> nthPointResult1 = { p1(), p4(), p2(), p5(), p3() };
    std::vector<CopyablePair<int>> nthPointResult3 = { p2(), p1(), p3(), p5(), p4() };
    std::vector<CopyablePair<int>> nthPointResult5 = { p4(), p2(), p3(), p1(), p5() };

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
