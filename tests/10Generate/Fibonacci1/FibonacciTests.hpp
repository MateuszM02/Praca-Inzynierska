#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/Structures/FibonacciFunctor.hpp"

using namespace src::Structures;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciArgs : public GenerateTestStruct<DataType>
{
    FibonacciArgs(
        const std::string& path,
        FibonacciFunctor<DataType> f, 
        unsigned int n, 
        const std::vector<DataType>& expectedResult);
};

class FibonacciIntFixture : public GenerateTestFixture<int>
{ };

class FibonacciDoubleFixture : public GenerateTestFixture<double>
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
