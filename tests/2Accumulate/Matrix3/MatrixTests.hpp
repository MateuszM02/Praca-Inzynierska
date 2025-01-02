#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct MatrixAccumulateArgs : public AccumulateTestStruct<Matrix<Number>>
{
    MatrixAccumulateArgs(
        Matrix<Number>(*f)()&,
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<Matrix<Number>>(
        AccumulateMatrix,
        std::make_shared<Accumulator<Matrix<Number>>>(
            AccumulateTestFixture<Matrix<Number>>::initTestData(f, n),
            accType))
    { }
};

class MatrixAccumulateIntFixture : public AccumulateTestFixture<Matrix<int>>
{ };

class MatrixAccumulateDoubleFixture : public AccumulateTestFixture<Matrix<double>>
{ };

TEST_P(MatrixAccumulateIntFixture, intTest)
{
    VerifyTestCustomFor2(GetParam());
}

TEST_P(MatrixAccumulateDoubleFixture, doubleTest)
{
    VerifyTestCustomFor2(GetParam());
}

} // namespace tests::Accumulate
