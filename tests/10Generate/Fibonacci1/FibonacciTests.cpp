#include "FibonacciTests.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    FibonacciGenerateIntFixture,
    ::testing::Values(
        std::make_shared<FibonacciGenerateArgs<int>>(std::make_pair(1, 1), 45u),
        std::make_shared<FibonacciGenerateArgs<int>>(std::make_pair(2, 2), 40u)
    ));

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix, 
    FibonacciGenerateDoubleFixture,
    ::testing::Values(
        std::make_shared<FibonacciGenerateArgs<double>>(std::make_pair(1.0, 1.0), 80u),
        std::make_shared<FibonacciGenerateArgs<double>>(std::make_pair(1.5, 2.5), 60u)
    ));

} // namespace tests::Generate
