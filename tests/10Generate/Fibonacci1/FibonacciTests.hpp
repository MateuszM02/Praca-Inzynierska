#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"

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
        this->createPath(GenerateFibonacci),
        std::move(src::Algorithms::GeneratorImpl::createFibonacciGenerator(n, initialPair)))
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
