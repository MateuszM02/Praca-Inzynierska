#include "../../src/Structures/RandomStringImpl.hpp"
#include "../5Transform/MatrixToIntVector1/TransformTests.hpp"
#include "../5Transform/VectorToMap2/TransformTests.hpp"
#include "../9RemoveEraseIf/Sequence1/SequenceTests.hpp"
#include "../9RemoveEraseIf/RandomString2/RandomStringTests.hpp"
#include "../10Generate/Fibonacci1/FibonacciTests.hpp"
#include "../ExampleMatrixes.hpp"
#include "StaticFixture.hpp"

namespace tests::Static
{

// CopyableMatrix
CopyableMatrix<int> M1()
{
    std::vector<std::vector<int>> vecOfVecs{ { 11, 1 }, { 20, 25 } };
    CopyableMatrix<int> m(std::move(vecOfVecs));
    return m;
}

CopyableMatrix<int> M2()
{
    std::vector<std::vector<int>> vecOfVecs{ { 7, 3 }, { 25, 45 } };
    CopyableMatrix<int> m(std::move(vecOfVecs));
    return m;
}

CopyableMatrix<int> M3()
{
    std::vector<std::vector<int>> vecOfVecs{ { 12, 2 }, { 3, 29 } };
    CopyableMatrix<int> m(std::move(vecOfVecs));
    return m;
}

// NonCopyableMatrix
NonCopyableMatrix<int> NCM1()
{
    std::vector<std::vector<int>> vecOfVecs{ { 11, 1 }, { 20, 25 } };
    NonCopyableMatrix<int> m(std::move(vecOfVecs));
    return m;
}

// CopyableIntVector - posortowane rosnaco - kolejnosc leksykograficzna
CopyableIntVector iv1() { return CopyableIntVector({ 1 }); }
CopyableIntVector iv2() { return CopyableIntVector({ 1, 2 }); }
CopyableIntVector iv3() { return CopyableIntVector({ 3 }); }
CopyableIntVector iv4() { return CopyableIntVector({ 3, 4 }); }
CopyableIntVector iv5() { return CopyableIntVector({ 3, 5 }); }
CopyableIntVector iv6() { return CopyableIntVector({ 4, 1 }); }

std::vector<CopyableIntVector> sortedIvVector() { return { iv1(), iv2(), iv3(), iv4(), iv5(), iv6() }; }
std::vector<CopyableIntVector> IvVector() { return { iv2(), iv4(), iv6(), iv1(), iv5(), iv3() }; }
std::set<CopyableIntVector> IvSet() { return { iv2(), iv4(), iv6(), iv1(), iv5(), iv3() }; }

// NonCopyableIntVector
std::vector<NonCopyableIntVector> matrixIvVector()
{
    std::vector<NonCopyableIntVector> vec;
    vec.emplace_back(std::vector<int>{11, 1});
    vec.emplace_back(std::vector<int>{20, 25});
    return vec;
}

// CopyablePair - posortowane rosnaco - liczy sie najpierw 1 wspolrzedna x, potem druga y jesli x1 = x2

CopyablePair<int> p1() { return CopyablePair(1, 12); }
CopyablePair<int> p2() { return CopyablePair(5, 2); }
CopyablePair<int> p3() { return CopyablePair(5, 5); }
CopyablePair<int> p4() { return CopyablePair(6, 5); }
CopyablePair<int> p5() { return CopyablePair(13, 1); }

std::vector<CopyablePair<int>> sortedPointVector() { return { p1(), p2(), p3(), p4(), p5() }; }
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

// 2. Accumulate
TEST_F(StaticTestFixture, AccumulateTest)
{
    AccResults<int> accumulateUIntResult;
    accumulateUIntResult.minimum = 1;
    accumulateUIntResult.maximum = 7;
    accumulateUIntResult.mean = 4;
    accumulateUIntResult.sum = 28;
    VerifyAccumulateWorks({ 2, 1, 3, 7, 5, 6, 4 }, accumulateUIntResult);

    AccResults<CopyablePair<int>> accumulatePointResult;
    accumulatePointResult.minimum = p1();
    accumulatePointResult.maximum = p5();
    accumulatePointResult.mean = p4();
    accumulatePointResult.sum = CopyablePair<int>(30, 25);
    VerifyAccumulateWorks(PointVector(), accumulatePointResult);

    auto values1 = []() -> std::vector<std::vector<int>> { return {{10, 2}, {16, 33}}; };
    auto values2 = []() -> std::vector<std::vector<int>> { return {{30, 6}, {48, 99}}; };
    auto matrixes = []() -> std::vector<CopyableMatrix<int>> { return { M1(), M2(), M3() }; };

    AccResults<CopyableMatrix<int>> accumulateMatrixResult;
    accumulateMatrixResult.minimum = M2();
    accumulateMatrixResult.maximum = M3();
    accumulateMatrixResult.mean = CopyableMatrix<int>(values1());
    accumulateMatrixResult.sum = CopyableMatrix<int>(values2());
    VerifyAccumulateWorks(matrixes(), accumulateMatrixResult);
}

// 3. Merge
TEST_F(StaticTestFixture, MergeTest)
{
    auto mergePoint1 = []() -> std::vector<CopyablePair<int>> { return { p1(), p3(), p4() }; };
    auto mergePoint2 = []() -> std::vector<CopyablePair<int>> { return { p2(), p5() }; };
    VerifyMergeWorks(MergerData<CopyablePair<int>>(mergePoint1(), mergePoint2()), sortedPointVector());

    auto mergeIntVec1 = []() -> std::vector<CopyableIntVector> { return { iv1(), iv3(), iv4(), iv6() }; };
    auto mergeIntVec2 = []() -> std::vector<CopyableIntVector> { return { iv2(), iv5() }; };
    VerifyMergeWorks(MergerData<CopyableIntVector>(mergeIntVec1(), mergeIntVec2()), sortedIvVector());
}

// 4. Sort
TEST_F(StaticTestFixture, SortTest)
{
    VerifySortWorks(PointVector(), sortedPointVector());
    VerifySortWorks(IvVector(), sortedIvVector());
}

// 5. Transform
TEST_F(StaticTestFixture, TransformTest)
{
    NonCopyableMatrix<int> ncm = NCM1();
    std::vector<NonCopyableMatrix<int>> inVec;
    inVec.emplace_back(std::move(ncm));

    std::vector<NonCopyableIntVector> mIntVec = matrixIvVector();
    std::vector<std::vector<NonCopyableIntVector>> outVec;
    outVec.emplace_back(std::move(mIntVec));

    VerifyTransformWorks<NonCopyableMatrix<int>, std::vector<NonCopyableIntVector>>(
        std::move(inVec),
        &Transform::MatrixToIntVectorTransformArgs::transformer,
        outVec);

    std::vector<unsigned int> vectorWithDuplicates = { 2, 1, 2, 3, 1, 7, 7, 2 };
    std::vector<std::vector<unsigned int>> inVec2;
    inVec2.emplace_back(std::move(vectorWithDuplicates));

    std::map<unsigned int, unsigned int> mapWithoutDuplicates = { { 1, 2 }, { 2, 3 }, { 3, 1 }, { 7, 2 } };
    std::vector<std::map<unsigned int, unsigned int>> outVec2;
    outVec2.emplace_back(std::move(mapWithoutDuplicates));

    VerifyTransformWorks<std::vector<unsigned int>, std::map<unsigned int, unsigned int>>(
        std::move(inVec2),
        &Transform::VectorToMapTransformArgs::transformer,
        outVec2);
}

// 6. Unique
TEST_F(StaticTestFixture, UniqueTest)
{
    std::vector<CopyablePair<int>> inVec1 = { p1(), p2(), p2(), p3(), p2(), p4(), p4(), p4() };
    const std::vector<CopyablePair<int>> outVec1 = { p1(), p2(), p3(), p2(), p4() };
    VerifyUniqueWorks<CopyablePair<int>>(std::move(inVec1), outVec1);

    std::vector<CopyableIntVector> inVec2 = { iv1(), iv2(), iv2(), iv3(), iv2(), iv4(), iv4(), iv4() };
    const std::vector<CopyableIntVector> outVec2 = { iv1(), iv2(), iv3(), iv2(), iv4() };
    VerifyUniqueWorks<CopyableIntVector>(std::move(inVec2), outVec2);
}

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

// 8. Regex
TEST_F(StaticTestFixture, RegexTest)
{
    const std::string text =
        "fakedatepatternis20012025realis20-01-2025fakepatternnumberis123456goodnumberis123 456 789endtext";
    const std::string datePattern = R"((0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4})";
    const std::string phonePattern = R"(\d{3} \d{3} \d{3})";
    const std::vector<std::string> expectedDateResult = { "20-01-2025" };
    const std::vector<std::string> expectedPhoneResult = { "123 456 789" };
    VerifyRegexWorks(text, datePattern, expectedDateResult);
    VerifyRegexWorks(text, phonePattern, expectedPhoneResult);
}

// 9. Remove erase if
TEST_F(StaticTestFixture, RemoveEraseIfTest)
{
    const std::vector<unsigned int> elements = { 1, 2, 3, 7, 16, 18, 22, 31 };
    const std::vector<unsigned int> expectedNonMersenneNumbers = { 1, 2, 16, 18, 22 };
    const std::vector<unsigned int> expectedNumbersWithMoreThan4Divisors = { 16, 18 };
    const std::vector<unsigned int> expectedNumbersWith1ToNSumEven = { 3, 7, 16, 31 };

    VerifyRemoveEraseIfWorks(elements,
        &RemoveEraseIf::SequenceIntFixture::isMersenneNumber,
        expectedNonMersenneNumbers);
    VerifyRemoveEraseIfWorks(elements,
        &RemoveEraseIf::SequenceIntFixture::hasAtMost4Divisors,
        expectedNumbersWithMoreThan4Divisors);
    VerifyRemoveEraseIfWorks(elements,
        &RemoveEraseIf::SequenceIntFixture::is1toNSumOdd,
        expectedNumbersWith1ToNSumEven);

    const std::vector<std::string> elements2 = { "aba", "ca", "", "@a", "ABBAI##", "BO$o", "Y" };
    const std::vector<std::string> expectedDoesntStartWithVowel = { "ca", "", "@a", "BO$o" };
    const std::vector<std::string> expectedNotMoreVowelsThanConsonants = { "ca", "" };

    VerifyRemoveEraseIfWorks(elements2,
        &RemoveEraseIf::RandomStringRemoveEraseIfFixture::startsWithVowel,
        expectedDoesntStartWithVowel);
    VerifyRemoveEraseIfWorks(elements2,
        &RemoveEraseIf::RandomStringRemoveEraseIfFixture::moreVowelsThanConsonants,
        expectedNotMoreVowelsThanConsonants);
}

TEST_F(StaticTestFixture, GenerateTest)
{
    const std::size_t elementCount = 8;
    const std::vector<int> expectedFibonacciResult = { 1, 2, 3, 5, 8, 13, 21, 34 };

    VerifyGenerateWorks<int, CopyablePair<int>>(elementCount,
        CopyablePair<int>(1, 1),
        &Generate::FibonacciGenerateArgs<int>::stateCreator,
        expectedFibonacciResult);

    // sprawdzamy tylko czy rozmiar sie zgadza
    const std::size_t stringSize = 4;
    const std::vector<std::string> expectedRandomStringResult(elementCount, std::string(stringSize, 'a'));

    VerifyGenerateRandomStringWorks(elementCount,
        CopyableRandomString(stringSize),
        &RandomStringImpl::creator,
        expectedRandomStringResult);

    const std::vector<CopyableMatrix<int>> expectedMatrixResult = {
        Examples::a1(2), Examples::a1(3), Examples::a1(4) };

    auto matrixStateGenerator = [initialMatrix = Examples::a1()](CopyableMatrix<int>& currentState)
    {
        currentState *= initialMatrix;
        return currentState;
    };

    VerifyGenerateWorks<CopyableMatrix<int>, CopyableMatrix<int>>(expectedMatrixResult.size(),
        Examples::a1(),
        std::move(matrixStateGenerator),
        expectedMatrixResult);
}

} // namespace tests::Static
