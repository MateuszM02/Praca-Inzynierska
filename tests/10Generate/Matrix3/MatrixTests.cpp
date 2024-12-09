#include "MatrixTests.hpp"
#include "ExampleMatrixes.hpp"

namespace tests::Generate::Matrix3tests
{

template <class Number>
requires std::is_arithmetic_v<Number>
MatrixArgs<Number>::MatrixArgs(
        const std::string& path,
        Matrix3::MatrixFunctor<Number> f, 
        unsigned int n, 
        const std::vector<Matrix3::Matrix<Number>>& expectedResult)
: GenerateTestStruct<Matrix3::Matrix<Number>>(
    path,
    std::make_shared<Matrix3::MatrixFunctor<Number>>(f), 
    n, expectedResult)
{ }

INSTANTIATE_TEST_SUITE_P(
    MatrixIntPrefix, 
    MatrixIntFixture,
    ::testing::Values(
        MatrixArgs<int>(
            Path::Create(GenerateMatrix, 1),
            Matrix3::MatrixFunctor<int>(Examples::a1()), 
            10000u, 
            Examples::A(10000u)),
        MatrixArgs<int>(
            Path::Create(GenerateMatrix, 2),
            Matrix3::MatrixFunctor<int>(Examples::c1(50u)), 
            100u, 
            Examples::C(50u, 100u)),
        MatrixArgs<int>(
            Path::Create(GenerateMatrix, 3),
            Matrix3::MatrixFunctor<int>(Examples::c1(100u)), 
            50u, 
            Examples::C(100u, 50u))
    ));

INSTANTIATE_TEST_SUITE_P(
    MatrixDoublePrefix,
    MatrixDoubleFixture,
    ::testing::Values( 
        MatrixArgs<double>(
            Path::Create(GenerateMatrix, 4),
            Matrix3::MatrixFunctor<double>(Examples::b1(10u)), 
            1000u, 
            Examples::B(10u, 1000u)),
        MatrixArgs<double>(
            Path::Create(GenerateMatrix, 5),
            Matrix3::MatrixFunctor<double>(Examples::b1(25u)), 
            500u, 
            Examples::B(25u, 500u)),
        MatrixArgs<double>(
            Path::Create(GenerateMatrix, 6),
            Matrix3::MatrixFunctor<double>(Examples::b1(50u)), 
            100u, 
            Examples::B(50u, 100u))
    ));

} // namespace tests::Generate::Matrix3tests
