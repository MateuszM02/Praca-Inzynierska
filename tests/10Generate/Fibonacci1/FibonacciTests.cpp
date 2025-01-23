#include "FibonacciTests.hpp"

namespace tests::Generate
{

TEST_P(FibonacciGenerateIntFixture, intTest)
{
    VerifyTest(GetParam());
}

TEST_P(FibonacciGenerateDoubleFixture, doubleTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    FibonacciGenerateIntFixture,
    ::testing::Values(
        std::make_shared<FibonacciGenerateArgs<int>>(CopyablePair(1, 1), 30u),
        std::make_shared<FibonacciGenerateArgs<int>>(CopyablePair(1, 1), 60u)
    ));

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    FibonacciGenerateDoubleFixture,
    ::testing::Values(
        std::make_shared<FibonacciGenerateArgs<double>>(CopyablePair(1.0, 1.0), 40u),
        std::make_shared<FibonacciGenerateArgs<double>>(CopyablePair(1.0, 1.0), 80u)
    ));

} // namespace tests::Generate
