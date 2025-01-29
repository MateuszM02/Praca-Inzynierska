#include "PointsTests.hpp"

#define BASE_SIZE 100'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

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
