#include "IntVectorTests.hpp"

#define SMALL_TEST 1'000
#define MEDIUM_TEST 5'000
#define BIG_TEST 10'000

namespace tests::Sort
{

INSTANTIATE_TEST_SUITE_P(
    SortPrefix,
    IntVectorSortFixture,
    ::testing::Values(
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::sortedFirstElementGenerator, SMALL_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::sortedFirstElementGenerator, MEDIUM_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::sortedFirstElementGenerator, BIG_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::sortedLastElementGenerator, SMALL_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::sortedLastElementGenerator, MEDIUM_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::sortedLastElementGenerator, BIG_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::randomGenerator, SMALL_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::randomGenerator, MEDIUM_TEST),
        std::make_shared<IntVectorSortArgs>(IntVectorSortFixture::randomGenerator, BIG_TEST)
    ));

} // namespace tests::Sort
