#include "FibonacciTests.hpp"

namespace tests::Generate::Fibonacci1tests
{

template <class Number>
requires std::is_arithmetic_v<Number>
FibonacciArgs<Number>::FibonacciArgs(
    Fibonacci1::FibonacciFunctor<Number> f, 
    unsigned int n, 
    std::vector<Number> v)
: functor{std::move(f)}
, GenerateTestStruct<Number>(f, n, std::move(v))
{ }

// TODO: Odkomentowac testy jak naprawie SEGFAULT

// INSTANTIATE_TEST_SUITE_P(
//     FibonacciIntTests, 
//     FibonacciIntFixture,
//     ::testing::Values( 
//         FibonacciArgs<int>({1, 1}, 10u, 
//                         std::vector<int>{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 559 }),
//         FibonacciArgs<int>({2, 2}, 9u,  
//                         std::vector<int>{ 2, 2, 4, 6, 10, 16, 26, 42, 68})
// ));

// INSTANTIATE_TEST_SUITE_P(
//     FibonacciDoubleTests, 
//     FibonacciDoubleFixture,
//     ::testing::Values( 
//         FibonacciArgs<double>({1.0, 1.0}, 10u, 
//                         std::vector<double>{ 1.0, 1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0, 55.0 }),
//         FibonacciArgs<double>({1.5, 2.5}, 9u,  
//                         std::vector<double>{ 1.5, 2.5, 4.0, 6.5, 10.5, 17.0, 27.5, 44.5, 72.0})
// ));

} // namespace tests::Generate::Fibonacci1tests
