#include "FibonacciTests.hpp"

namespace tests::RepeatFun::Fibonacci2tests
{
template <class Number>
requires std::is_arithmetic_v<Number>
void FibonacciTest<Number>::createTest(
    const unsigned int n,
    const src::MethodType& methodType,
    const std::vector<Number>& args)
{
    auto functor = Fibonacci2::FibonacciFunctor<Number>(args[0], args[1]);
    runTest(functor, n, methodType);
}
} // namespace tests::RepeatFun::Fibonacci2tests
