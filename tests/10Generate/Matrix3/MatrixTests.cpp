#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

namespace tests::Generate
{

TEST_P(MatrixGenerateIntFixture, intTest)
{
    VerifyTest(GetParam());
}

TEST_P(MatrixGenerateDoubleFixture, doubleTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    MatrixGenerateIntFixture,
    ::testing::Values(
        std::make_shared<MatrixGenerateArgs<int>>(Examples::a1(), 100'000u),
        std::make_shared<MatrixGenerateArgs<int>>(Examples::a1(), 200'000u),
        std::make_shared<MatrixGenerateArgs<int>>(Examples::c1(75u), 100u),
        std::make_shared<MatrixGenerateArgs<int>>(Examples::c1(75u), 200u)
    ));

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    MatrixGenerateDoubleFixture,
    ::testing::Values(
        std::make_shared<MatrixGenerateArgs<double>>(Examples::b1(75u), 100u),
        std::make_shared<MatrixGenerateArgs<double>>(Examples::b1(75u), 200u),
        std::make_shared<MatrixGenerateArgs<double>>(Examples::b1(75u), 300u)
    ));

} // namespace tests::Generate
