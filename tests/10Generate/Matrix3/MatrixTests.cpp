#include "MatrixTests.hpp"
#include "ExampleMatrixes.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    MatrixGenerateIntPrefix, 
    MatrixGenerateIntArgs,
    ::testing::Values(
        MatrixGenerateArgs<int>(Examples::a1(), 10000u),
        MatrixGenerateArgs<int>(Examples::c1(50u), 100u),
        MatrixGenerateArgs<int>(Examples::c1(100u), 50u)
    ));

INSTANTIATE_TEST_SUITE_P(
    MatrixGenerateDoublePrefix,
    MatrixGenerateDoubleArgs,
    ::testing::Values(
        MatrixGenerateArgs<double>(Examples::b1(10u), 1000u),
        MatrixGenerateArgs<double>(Examples::b1(25u), 500u),
        MatrixGenerateArgs<double>(Examples::b1(50u), 100u)
    ));

} // namespace tests::Generate
