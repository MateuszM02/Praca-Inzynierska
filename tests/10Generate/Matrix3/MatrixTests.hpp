#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/10Generate/Matrix3/MatrixFunctor.hpp"

namespace tests::Generate::Matrix3tests
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct MatrixArgs : public GenerateTestStruct<Matrix3::Matrix<Number>>
{
    MatrixArgs(
        const std::string& path,
        Matrix3::MatrixFunctor<Number> f, 
        unsigned int n, 
        const std::vector<Matrix3::Matrix<Number>>& expectedResult);
};

class MatrixIntFixture : public GenerateTestFixture<Matrix3::Matrix<int>>
{ };

class MatrixDoubleFixture : public GenerateTestFixture<Matrix3::Matrix<double>>
{ };

TEST_P(MatrixIntFixture, intTest)
{ 
    VerifyTest(GetParam());
}

TEST_P(MatrixDoubleFixture, doubleTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Generate::Matrix3tests
