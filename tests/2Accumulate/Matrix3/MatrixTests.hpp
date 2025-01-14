#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../AccumulateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Accumulate
{

template <typename Number>
requires std::is_arithmetic_v<Number>
struct MatrixAccumulateArgs final : public AccumulateTestStruct<CopyableMatrix<Number>>
{
    explicit MatrixAccumulateArgs(
        CopyableMatrix<Number>(*dataCreator)(),
        const unsigned int n,
        AccType accType)
    : AccumulateTestStruct<CopyableMatrix<Number>>(
        TestType::AccumulateMatrix,
        [dataCreator, n, accType]()
        {
            std::vector<CopyableMatrix<Number>> data =
                BaseTestStruct<AccResults<CopyableMatrix<Number>>>::template
                initTestData<std::vector<CopyableMatrix<Number>>>(dataCreator, n);
            return std::make_shared<Accumulator<CopyableMatrix<Number>>>(std::move(data), accType);
        })
    { }
};

class MatrixAccumulateIntFixture : public AccumulateTestFixture<CopyableMatrix<int>>
{ };

class MatrixAccumulateDoubleFixture : public AccumulateTestFixture<CopyableMatrix<double>>
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
