#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct MatrixGenerateArgs : public GenerateTestStruct<Matrix<Number>>
{
    MatrixGenerateArgs(
        const Matrix<Number>& initialMatrix,
        unsigned int n)
    : GenerateTestStruct<Matrix<Number>>(
    GenerateMatrix,
    std::move(MatrixImpl::createGenerator(n, initialMatrix)))
    { }
};

class MatrixGenerateIntArgs : public GenerateTestFixture<Matrix<int>>
{ };

class MatrixGenerateDoubleArgs : public GenerateTestFixture<Matrix<double>>
{ };

TEST_P(MatrixGenerateIntArgs, intTest)
{ 
    VerifyTest(GetParam());
}

TEST_P(MatrixGenerateDoubleArgs, doubleTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Generate
