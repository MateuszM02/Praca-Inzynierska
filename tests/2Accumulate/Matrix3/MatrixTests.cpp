#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

#define FEW_MATRIXES 1'000
#define MANY_MATRIXES 2'000

#define SMALL_MATRIXES 100
#define BIG_MATRIXES 200

#define TEST_SIZES { TestPair(FEW_MATRIXES, SMALL_MATRIXES), TestPair(MANY_MATRIXES, SMALL_MATRIXES), \
    TestPair(FEW_MATRIXES, BIG_MATRIXES), TestPair(MANY_MATRIXES, BIG_MATRIXES) }

namespace tests::Accumulate
{

static std::vector<std::shared_ptr<Base<int>>> getIntTests()
{
    std::vector<std::shared_ptr<Base<int>>> tests;
    using T = CopyableMatrix<int>(*)(const unsigned int);

    createTestArgs<Base<int>, MatrixAccumulateArgs<int>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomIntMatrix, AccType::SumOnly);
    createTestArgs<Base<int>, MatrixAccumulateArgs<int>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomIntMatrix, AccType::SumAndExtremes);
    createTestArgs<Base<int>, MatrixAccumulateArgs<int>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomIntMatrix, AccType::SumAndMean);
    createTestArgs<Base<int>, MatrixAccumulateArgs<int>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomIntMatrix, AccType::DoItAll);
    return tests;
}

static std::vector<std::shared_ptr<Base<double>>> getDoubleTests()
{
    std::vector<std::shared_ptr<Base<double>>> tests;
    using T = CopyableMatrix<double>(*)(const unsigned int);

    createTestArgs<Base<double>, MatrixAccumulateArgs<double>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomDoubleMatrix, AccType::SumOnly);
    createTestArgs<Base<double>, MatrixAccumulateArgs<double>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomDoubleMatrix, AccType::SumAndExtremes);
    createTestArgs<Base<double>, MatrixAccumulateArgs<double>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomDoubleMatrix, AccType::SumAndMean);
    createTestArgs<Base<double>, MatrixAccumulateArgs<double>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomDoubleMatrix, AccType::DoItAll);
    return tests;
}

TEST_P(MatrixAccumulateIntFixture, intTest)
{
    VerifyTestCustomFor2(GetParam());
}

TEST_P(MatrixAccumulateDoubleFixture, doubleTest)
{
    VerifyTestCustomFor2(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    MatrixAccumulateIntFixture,
    ::testing::ValuesIn(getIntTests()));

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    MatrixAccumulateDoubleFixture,
    ::testing::ValuesIn(getDoubleTests()));

} // namespace tests::Accumulate
