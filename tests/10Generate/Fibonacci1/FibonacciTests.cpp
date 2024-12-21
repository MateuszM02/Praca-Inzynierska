#include "FibonacciTests.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    FibonacciIntPrefix,
    FibonacciIntFixture,
    ::testing::Values(
        FibonacciArgs<int>(std::make_pair(1, 1), 45u),
        FibonacciArgs<int>(std::make_pair(2, 2), 40u)
    ));

INSTANTIATE_TEST_SUITE_P(
    FibonacciDoublePrefix, 
    FibonacciDoubleFixture,
    ::testing::Values(
        FibonacciArgs<double>(std::make_pair(1.0, 1.0), 80u),
        FibonacciArgs<double>(std::make_pair(1.5, 2.5), 60u)
    ));

} // namespace tests::Generate
