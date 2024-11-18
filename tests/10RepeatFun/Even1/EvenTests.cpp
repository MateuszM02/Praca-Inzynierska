#include "EvenTests.hpp"

namespace tests::RepeatFun::Even1tests
{
void EvenTest::createTest(
    const unsigned int n,
    const src::MethodType& methodType,
    const std::vector<unsigned int>& args)
{
    auto functor = Even1::EvenFunctor();
    runTest(functor, n, methodType);
}
} // namespace tests::RepeatFun::Even1tests
