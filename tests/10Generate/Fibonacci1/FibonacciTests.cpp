#include "FibonacciTests.hpp"

namespace tests::Generate::Fibonacci1tests
{

template <class Number>
requires std::is_arithmetic_v<Number>
FibonacciArgs<Number>::FibonacciArgs(
    Fibonacci1::FibonacciFunctor<Number> f, 
    unsigned int n, 
    const std::vector<Number>& expectedResult)
: GenerateTestStruct<Number>(
    std::make_shared<Fibonacci1::FibonacciFunctor<Number>>(f), 
    n, expectedResult)
{ }

INSTANTIATE_TEST_SUITE_P(
    FibonacciIntPrefix, 
    FibonacciIntFixture,
    ::testing::Values( 
        FibonacciArgs<int>({1, 1}, 10u, 
                        std::vector<int>{ 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }),
        FibonacciArgs<int>({2, 2}, 9u,  
                        std::vector<int>{ 2, 4, 6, 10, 16, 26, 42, 68, 110 })
));

INSTANTIATE_TEST_SUITE_P(
    FibonacciDoublePrefix, 
    FibonacciDoubleFixture,
    ::testing::Values( 
        FibonacciArgs<double>({1.0, 1.0}, 10u, 
                        std::vector<double>{ 1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0, 55.0, 89.0 }),
        FibonacciArgs<double>({1.5, 2.5}, 9u,  
                        std::vector<double>{ 2.5, 4.0, 6.5, 10.5, 17.0, 27.5, 44.5, 72.0, 116.5 })
));

} // namespace tests::Generate::Fibonacci1tests
