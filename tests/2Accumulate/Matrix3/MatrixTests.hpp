#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

template <typename Number>
requires std::is_arithmetic_v<Number>
struct MatrixAccumulateArgs final : public AccumulateTestStruct<Matrix<Number>>
{
    explicit MatrixAccumulateArgs(
        Matrix<Number>(*f)(),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<Matrix<Number>>(
        TestType::AccumulateMatrix,
        std::make_shared<Accumulator<Matrix<Number>>>(
            this->template initTestData<std::vector<Matrix<Number>>>(f, n),
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
