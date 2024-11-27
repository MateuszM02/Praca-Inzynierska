#pragma once
#include "../TestFixture.hpp"
#include "../../../src/10Generate/Fibonacci1/FibonacciFunctor.hpp"

namespace tests::Generate::Fibonacci1tests
{

template <class Number>
requires std::is_arithmetic_v<Number>
struct FibonacciArgs : public GenerateTestStruct<Number>
{
    FibonacciArgs(Fibonacci1::FibonacciFunctor<Number> f, unsigned int n, std::vector<Number> v);

    Fibonacci1::FibonacciFunctor<Number> functor;
};

class FibonacciIntFixture : public GenerateTestFixture<int>
{ };

class FibonacciDoubleFixture : public GenerateTestFixture<double>
{ };

// TODO: Odkomentowac TEST_P jak naprawie SEGFAULT

// TEST_P(FibonacciIntFixture, intTest)
// { 
//     VerifyTest(GetParam());
// }

// TEST_P(FibonacciDoubleFixture, doubleTest)
// { 
//     VerifyTest(GetParam());
// }
} // namespace tests::Generate::Fibonacci1tests
