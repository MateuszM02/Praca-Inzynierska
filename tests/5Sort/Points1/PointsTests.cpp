#include "PointsTests.hpp"

#define SMALL_TEST 100'000
#define MEDIUM_TEST 250'000
#define BIG_TEST 500'000

namespace tests::Sort
{

INSTANTIATE_TEST_SUITE_P(
    PointsSortPrefix,
    PointsSortFixture,
    ::testing::Values(
        PointsSortArgs(PointsSortFixture::sortedGenerator, SMALL_TEST),
        PointsSortArgs(PointsSortFixture::sortedGenerator, MEDIUM_TEST),
        PointsSortArgs(PointsSortFixture::sortedGenerator, BIG_TEST),
        PointsSortArgs(PointsSortFixture::reverseSortedGenerator, SMALL_TEST),
        PointsSortArgs(PointsSortFixture::reverseSortedGenerator, MEDIUM_TEST),
        PointsSortArgs(PointsSortFixture::reverseSortedGenerator, BIG_TEST),
        PointsSortArgs(PointsSortFixture::randomGenerator, SMALL_TEST),
        PointsSortArgs(PointsSortFixture::randomGenerator, MEDIUM_TEST),
        PointsSortArgs(PointsSortFixture::randomGenerator, BIG_TEST)
    ));

} // namespace tests::Sort
