#pragma once

#include "../../../src/Structures/MatrixImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

struct MatrixGenerateArgs final : public GenerateTestStruct<CopyableMatrix<int>>
{
    explicit MatrixGenerateArgs(
        CopyableMatrix<int>&& initialMatrix,
        const unsigned int n)
    : GenerateTestStruct<CopyableMatrix<int>>(
        TestType::GenerateMatrix,
        [initialMatrix_ = std::move(initialMatrix), n]() mutable
        {
            auto stateCreator = [initialMatrix_](CopyableMatrix<int>& currentState)
            {
                currentState *= initialMatrix_;
                return currentState;
            };

            return std::make_shared<Generator<CopyableMatrix<int>>>(
                n, std::move(initialMatrix_), std::move(stateCreator));
        })
    { }
};

class MatrixGenerateIntFixture : public GenerateTestFixture<CopyableMatrix<int>>
{ };

} // namespace tests::Generate
