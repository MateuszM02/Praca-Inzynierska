#include "MatrixTests.hpp"
#include "ExampleMatrixes.hpp"

namespace tests::Generate
{

template <class Number>
requires std::is_arithmetic_v<Number>
MatrixArgs<Number>::MatrixArgs(
        const std::string& path,
        MatrixFunctor<Number> f, 
        unsigned int n, 
        const std::vector<Matrix<Number>>& expectedResult)
: GenerateTestStruct<Matrix<Number>>(
    path,
    std::make_shared<MatrixFunctor<Number>>(f), 
    n, expectedResult)
{ }

INSTANTIATE_TEST_SUITE_P(
    MatrixIntPrefix, 
    MatrixIntFixture,
    ::testing::Values(
        MatrixArgs<int>(
            Path::Create(GenerateMatrix, 1),
            MatrixFunctor<int>(Examples::a1()), 
            10000u, 
            Examples::A(10000u)),
        MatrixArgs<int>(
            Path::Create(GenerateMatrix, 2),
            MatrixFunctor<int>(Examples::c1(50u)), 
            100u, 
            Examples::C(50u, 100u)),
        MatrixArgs<int>(
            Path::Create(GenerateMatrix, 3),
            MatrixFunctor<int>(Examples::c1(100u)), 
            50u, 
            Examples::C(100u, 50u))
    ));

INSTANTIATE_TEST_SUITE_P(
    MatrixDoublePrefix,
    MatrixDoubleFixture,
    ::testing::Values( 
        MatrixArgs<double>(
            Path::Create(GenerateMatrix, 4),
            MatrixFunctor<double>(Examples::b1(10u)), 
            1000u, 
            Examples::B(10u, 1000u)),
        MatrixArgs<double>(
            Path::Create(GenerateMatrix, 5),
            MatrixFunctor<double>(Examples::b1(25u)), 
            500u, 
            Examples::B(25u, 500u)),
        MatrixArgs<double>(
            Path::Create(GenerateMatrix, 6),
            MatrixFunctor<double>(Examples::b1(50u)), 
            100u, 
            Examples::B(50u, 100u))
    ));

} // namespace tests::Generate
