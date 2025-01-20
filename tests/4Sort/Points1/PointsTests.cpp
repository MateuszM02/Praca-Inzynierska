#include "PointsTests.hpp"

#define TEST_SIZES { 50'000, 100'000, 150'000, 200'000 }

namespace tests::Sort
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, PointsSortArgs, T>(tests, TEST_SIZES,
        &PointsSortFixture::sortedGenerator);
    createTestArgs<Base, PointsSortArgs, T>(tests, TEST_SIZES,
        &PointsSortFixture::reverseSortedGenerator);
    createTestArgs<Base, PointsSortArgs, T>(tests, TEST_SIZES,
        &PointsSortFixture::randomGenerator);
    return tests;
}

TEST_P(PointsSortFixture, pointsSortTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    SortPrefix,
    PointsSortFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Sort
