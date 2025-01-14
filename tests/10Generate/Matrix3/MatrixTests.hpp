#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <typename Number>
requires std::is_arithmetic_v<Number>
struct MatrixGenerateArgs final : public GenerateTestStruct<CopyableMatrix<Number>>
{
    explicit MatrixGenerateArgs(
        CopyableMatrix<Number>&& initialMatrix,
        const unsigned int n)
    : GenerateTestStruct<CopyableMatrix<Number>>(
        TestType::GenerateMatrix,
        [initialMatrix_ = std::move(initialMatrix), n]() mutable
        {
            auto stateCreator = [initialMatrix_](CopyableMatrix<Number>& currentState)
            {
                currentState *= initialMatrix_;
                return currentState;
            };

            return std::make_shared<Generator<CopyableMatrix<Number>>>(
                n, std::move(initialMatrix_), std::move(stateCreator));
        })
    { }
};

class MatrixGenerateIntFixture : public GenerateTestFixture<CopyableMatrix<int>>
{ };

class MatrixGenerateDoubleFixture : public GenerateTestFixture<CopyableMatrix<double>>
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
