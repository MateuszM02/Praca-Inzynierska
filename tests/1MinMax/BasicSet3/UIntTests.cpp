#include "UIntTests.hpp"

#define SMALL_TEST 250'000
#define MEDIUM_TEST 1'000'000
#define BIG_TEST 2'000'000

namespace tests::MinMax
{

INSTANTIATE_TEST_SUITE_P(
    BasicSetMinMaxPrefix,
    BasicSetMinMaxFixture,
    ::testing::Values(
        // generator rosnacych liczb
        BasicSetMinMaxArgs(BasicSetMinMaxFixture::sortedGenerator,
                   SMALL_TEST),
        BasicSetMinMaxArgs(BasicSetMinMaxFixture::sortedGenerator,
                   MEDIUM_TEST),
        BasicSetMinMaxArgs(BasicSetMinMaxFixture::sortedGenerator,
                   BIG_TEST),
        // generator malejacych liczb
        BasicSetMinMaxArgs(BasicSetMinMaxFixture::reverseSortedGenerator,
                   SMALL_TEST),
        BasicSetMinMaxArgs(BasicSetMinMaxFixture::reverseSortedGenerator,
                   MEDIUM_TEST),
        BasicSetMinMaxArgs(BasicSetMinMaxFixture::reverseSortedGenerator,
                   BIG_TEST)
    ));

} // namespace tests::MinMax
