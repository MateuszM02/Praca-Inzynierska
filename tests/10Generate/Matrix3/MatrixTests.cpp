#include "MatrixTests.hpp"
#include "ExampleMatrixes.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    MatrixIntPrefix, 
    MatrixIntFixture,
    ::testing::Values(
        MatrixArgs<int>(Examples::a1(), 10000u),
        MatrixArgs<int>(Examples::c1(50u), 100u),
        MatrixArgs<int>(Examples::c1(100u), 50u)
    ));

INSTANTIATE_TEST_SUITE_P(
    MatrixDoublePrefix,
    MatrixDoubleFixture,
    ::testing::Values(
        MatrixArgs<double>(Examples::b1(10u), 1000u),
        MatrixArgs<double>(Examples::b1(25u), 500u),
        MatrixArgs<double>(Examples::b1(50u), 100u)
    ));

} // namespace tests::Generate
