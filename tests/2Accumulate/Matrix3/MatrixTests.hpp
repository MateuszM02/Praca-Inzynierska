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
        Matrix<Number>(*dataCreator)(),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<Matrix<Number>>(
        TestType::AccumulateMatrix,
        [dataCreator, n, accType]()
        {
            std::vector<Matrix<Number>> data =
                BaseTestStruct<AccResults<Matrix<Number>>>::template
                initTestData<std::vector<Matrix<Number>>>(dataCreator, n);
            return std::make_shared<Accumulator<Matrix<Number>>>(std::move(data), accType);
        })
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
