#pragma once

#include "../../../src/Concepts/DataTypeConcepts.hpp"
#include "../../../src/Structures/FibonacciImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Concepts;
using namespace src::Structures;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciGenerateArgs final : public GenerateTestStruct<DataType, std::pair<DataType, DataType>>
{
    FibonacciGenerateArgs(
        const std::pair<DataType, DataType>& initialPair,
        unsigned int n)
    : GenerateTestStruct<DataType, std::pair<DataType, DataType>>(
        GenerateFibonacci,
        std::move(FibonacciImpl::createGenerator(n, initialPair)))
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
