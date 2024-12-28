#include "IntVectorTests.hpp"

#define SMALL_TEST 1'000
#define MEDIUM_TEST 5'000
#define BIG_TEST 10'000

namespace tests::Sort
{

INSTANTIATE_TEST_SUITE_P(
    IntVectorSortPrefix,
    IntVectorSortFixture,
    ::testing::Values(
        IntVectorSortArgs(IntVectorSortFixture::sortedFirstElementGenerator, SMALL_TEST),
        IntVectorSortArgs(IntVectorSortFixture::sortedFirstElementGenerator, MEDIUM_TEST),
        IntVectorSortArgs(IntVectorSortFixture::sortedFirstElementGenerator, BIG_TEST),
        IntVectorSortArgs(IntVectorSortFixture::sortedLastElementGenerator, SMALL_TEST),
        IntVectorSortArgs(IntVectorSortFixture::sortedLastElementGenerator, MEDIUM_TEST),
        IntVectorSortArgs(IntVectorSortFixture::sortedLastElementGenerator, BIG_TEST),
        IntVectorSortArgs(IntVectorSortFixture::randomGenerator, SMALL_TEST),
        IntVectorSortArgs(IntVectorSortFixture::randomGenerator, MEDIUM_TEST),
        IntVectorSortArgs(IntVectorSortFixture::randomGenerator, BIG_TEST)
    ));

} // namespace tests::Sort
