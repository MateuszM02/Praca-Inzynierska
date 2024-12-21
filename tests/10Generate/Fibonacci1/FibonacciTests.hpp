#pragma once

#include "../../../src/Concepts/DataTypeConcepts.hpp"
#include "../../../src/Structures/FibonacciImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Concepts;
using namespace src::Structures;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciArgs final : public GenerateTestStruct<DataType, std::pair<DataType, DataType>>
{
    FibonacciArgs(
        const std::pair<DataType, DataType>& initialPair,
        unsigned int n)
    : GenerateTestStruct<DataType, std::pair<DataType, DataType>>(
        GenerateFibonacci,
        std::move(FibonacciImpl::createGenerator(n, initialPair)))
    { }
};

class FibonacciIntFixture : public GenerateTestFixture<int, std::pair<int, int>>
{ };

class FibonacciDoubleFixture : public GenerateTestFixture<double, std::pair<double, double>>
{ };

TEST_P(FibonacciIntFixture, intTest)
{ 
    VerifyTest(GetParam());
}

TEST_P(FibonacciDoubleFixture, doubleTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Generate
