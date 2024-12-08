#pragma once
#include "../GenerateTestFixture.hpp"
#include "../Path.hpp"
#include "../../../src/10Generate/Fibonacci1/FibonacciFunctor.hpp"

namespace tests::Generate::Fibonacci1tests
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct FibonacciArgs : public GenerateTestStruct<Number>
{
    FibonacciArgs(
        const std::string& path,
        Fibonacci1::FibonacciFunctor<Number> f, 
        unsigned int n, 
        const std::vector<Number>& expectedResult);
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

} // namespace tests::Generate::Fibonacci1tests
