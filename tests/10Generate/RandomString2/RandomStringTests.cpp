#include "RandomStringTests.hpp"

namespace tests::Generate::RandomString2tests
{
void RandomStringTest::createTest(
    const unsigned int n,
    const src::MethodType& methodType,
    const std::vector<std::string>& args)
{
    auto functor = RandomString2::RandomStringFunctor(args[0].size());
    runTest(functor, n, methodType);
}
} // namespace tests::Generate::RandomString2tests
