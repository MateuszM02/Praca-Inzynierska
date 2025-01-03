#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <typename Number>
requires std::is_arithmetic_v<Number>
struct MatrixGenerateArgs final : public GenerateTestStruct<Matrix<Number>>
{
    explicit MatrixGenerateArgs(
        const Matrix<Number>& initialMatrix,
        const unsigned int n)
    : GenerateTestStruct<Matrix<Number>>(
    TestType::GenerateMatrix,
    std::make_shared<Generator<Matrix<Number>>>(n, initialMatrix,
        [initialState = initialMatrix](Matrix<Number>& currentState)
        {
            currentState *= initialState;
            return currentState;
        }))
    { }
};

class MatrixGenerateIntFixture : public GenerateTestFixture<Matrix<int>>
{ };

class MatrixGenerateDoubleFixture : public GenerateTestFixture<Matrix<double>>
{ };

TEST_P(MatrixGenerateIntFixture, intTest)
{ 
    VerifyTest(GetParam());
}

TEST_P(MatrixGenerateDoubleFixture, doubleTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Generate
