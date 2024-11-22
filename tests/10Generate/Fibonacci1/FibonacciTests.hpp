#pragma once

#include "../TestFixture.hpp"
#include "../../../src/10Generate/Fibonacci1/FibonacciFunctor.hpp"

namespace tests::Generate::Fibonacci1tests
{
template <class Number>
requires std::is_arithmetic_v<Number>
class FibonacciTest : GenerateTestFixture<Number>
{ 
public:
    void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<Number>& args) override;
};
} // namespace tests::Generate::Fibonacci1tests
