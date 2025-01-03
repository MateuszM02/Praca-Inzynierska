#pragma once

#include "../../../src/Concepts/DataTypeConcepts.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Concepts;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciGenerateArgs final : public GenerateTestStruct<DataType, std::pair<DataType, DataType>>
{
    explicit FibonacciGenerateArgs(
        const std::pair<DataType, DataType>& initialPair,
        unsigned int n)
    : GenerateTestStruct<DataType, std::pair<DataType, DataType>>(
        TestType::GenerateFibonacci,
        std::make_shared<Generator<DataType, std::pair<DataType, DataType>>>(n, initialPair,
            [](std::pair<DataType, DataType>& currentState)
            {
                currentState = std::make_pair(currentState.second, currentState.first + currentState.second);
                return currentState.first;
            }))
    { }
};

class FibonacciGenerateIntFixture : public GenerateTestFixture<int, std::pair<int, int>>
{ };

class FibonacciGenerateDoubleFixture : public GenerateTestFixture<double, std::pair<double, double>>
{ };

TEST_P(FibonacciGenerateIntFixture, intTest)
{ 
    VerifyTest(GetParam());
}

TEST_P(FibonacciGenerateDoubleFixture, doubleTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Generate
