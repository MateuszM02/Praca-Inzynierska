#pragma once

#include "../../../src/Concepts/DataTypeConcepts.hpp"
#include "../../../src/Structures/CustomPairImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Concepts;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciGenerateArgs final : public GenerateTestStruct<DataType, CopyablePair<DataType>>
{
    explicit FibonacciGenerateArgs(
        CopyablePair<DataType>&& initialPair,
        unsigned int n)
    : GenerateTestStruct<DataType, CopyablePair<DataType>>(
        TestType::GenerateFibonacci,
        [initialPair_ = std::move(initialPair), n]() mutable
        {
            return std::make_shared<Generator<DataType, CopyablePair<DataType>>>(
                n, std::move(initialPair_), &stateCreator);
        })
    { }

    static DataType stateCreator(CopyablePair<DataType>& currentState)
    {
        currentState = CopyablePair(currentState.second_, currentState.first_ + currentState.second_);
        return currentState.first_;
    }
};

class FibonacciGenerateIntFixture : public GenerateTestFixture<int, CopyablePair<int>>
{ };

class FibonacciGenerateDoubleFixture : public GenerateTestFixture<double, CopyablePair<double>>
{ };

} // namespace tests::Generate
