#include "PointsTests.hpp"

#define SMALL_TEST 100'000
#define MEDIUM_TEST 250'000
#define BIG_TEST 500'000

namespace tests::Sort
{

INSTANTIATE_TEST_SUITE_P(
    SortPrefix,
    PointsSortFixture,
    ::testing::Values(
        std::make_shared<PointsSortArgs>(PointsSortFixture::sortedGenerator, SMALL_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::sortedGenerator, MEDIUM_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::sortedGenerator, BIG_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::reverseSortedGenerator, SMALL_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::reverseSortedGenerator, MEDIUM_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::reverseSortedGenerator, BIG_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::randomGenerator, SMALL_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::randomGenerator, MEDIUM_TEST),
        std::make_shared<PointsSortArgs>(PointsSortFixture::randomGenerator, BIG_TEST)
    ));

} // namespace tests::Sort
