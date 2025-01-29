#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

#define BASE_COUNT 1'000
#define MATRIX_SIZE 100
#define TEST_SIZES TEST_SIZES10_PAIRS_ONLY1RISE(BASE_COUNT, MATRIX_SIZE)

namespace tests::Accumulate
{

static std::vector<std::shared_ptr<Base<int>>> getIntTests()
{
    std::vector<std::shared_ptr<Base<int>>> tests;
    using T = CopyableMatrix<int>(*)(const unsigned int);

    createTestArgs<Base<int>, MatrixAccumulateArgs<int>, T, AccType>(
        tests, TEST_SIZES, &Examples::randomIntMatrix, AccType::DoItAll);
    return tests;
}

static std::vector<std::shared_ptr<Base<double>>> getDoubleTests()
{
    std::vector<std::shared_ptr<Base<double>>> tests;
    using T = CopyableMatrix<double>(*)(const unsigned int);

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
