#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciArgs : public GenerateTestStruct<DataType, std::pair<DataType, DataType>>
{
    FibonacciArgs(
        const std::string& path,
        const std::pair<DataType, DataType>& initialPair,
        unsigned int n,
        const std::vector<DataType>& expectedResult);
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
