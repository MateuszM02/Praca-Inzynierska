#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

#define BASE_COUNT1 100'000
#define TEST_COUNTS1 TEST_SIZES10(BASE_COUNT1)

#define CMATRIX_SIZE 75
#define BASE_COUNT2 50
#define TEST_COUNTS2 TEST_SIZES10(BASE_COUNT2)

namespace tests::Generate
{

TEST_P(MatrixGenerateIntFixture, intTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    MatrixGenerateIntFixture,
    ::testing::Values(
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[0]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[1]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[2]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[3]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[4]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[5]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[6]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[7]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[8]),
        std::make_shared<MatrixGenerateArgs>(Examples::a1(), TEST_COUNTS1[9]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[0]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[1]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[2]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[3]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[4]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[5]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[6]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[7]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[8]),
        std::make_shared<MatrixGenerateArgs>(Examples::b1(CMATRIX_SIZE), TEST_COUNTS2[9])
    ));

} // namespace tests::Generate
