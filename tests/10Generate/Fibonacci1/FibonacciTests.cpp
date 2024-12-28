#include "FibonacciTests.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    FibonacciGenerateIntPrefix,
    FibonacciGenerateIntFixture,
    ::testing::Values(
        FibonacciGenerateArgs<int>(std::make_pair(1, 1), 45u),
        FibonacciGenerateArgs<int>(std::make_pair(2, 2), 40u)
    ));

INSTANTIATE_TEST_SUITE_P(
    FibonacciGenerateDoublePrefix, 
    FibonacciGenerateDoubleFixture,
    ::testing::Values(
        FibonacciGenerateArgs<double>(std::make_pair(1.0, 1.0), 80u),
        FibonacciGenerateArgs<double>(std::make_pair(1.5, 2.5), 60u)
    ));

} // namespace tests::Generate
