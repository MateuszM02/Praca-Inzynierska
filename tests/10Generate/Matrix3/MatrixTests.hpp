#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct MatrixArgs : public GenerateTestStruct<Matrix<Number>>
{
    MatrixArgs(
        const std::string& path,
        const Matrix<Number>& initialMatrix,
        unsigned int n);
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
