#pragma once

#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct MatrixArgs : public GenerateTestStruct<Matrix<Number>>
{
    MatrixArgs(
        const Matrix<Number>& initialMatrix,
        unsigned int n)
    : GenerateTestStruct<Matrix<Number>>(
    GenerateMatrix,
    std::move(src::Algorithms::GeneratorImpl::createMatrixGenerator(n, initialMatrix)))
    { }
};

class MatrixIntFixture : public GenerateTestFixture<Matrix<int>>
{ };

class MatrixDoubleFixture : public GenerateTestFixture<Matrix<double>>
{ };

TEST_P(MatrixIntFixture, intTest)
{ 
    VerifyTest(GetParam());
}

TEST_P(MatrixDoubleFixture, doubleTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Generate
