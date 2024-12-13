#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/Structures/MatrixFunctor.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct MatrixArgs : public GenerateTestStruct<Matrix<Number>>
{
    MatrixArgs(
        const std::string& path,
        MatrixFunctor<Number> f, 
        unsigned int n, 
        const std::vector<Matrix<Number>>& expectedResult);
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
