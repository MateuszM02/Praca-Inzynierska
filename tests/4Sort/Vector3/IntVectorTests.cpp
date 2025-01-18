#include "IntVectorTests.hpp"

#define TEST_SIZES { 2'000, 4'000, 8'000, 16'000 }

namespace tests::Sort
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableIntVector(*)(const unsigned int);

    createTestArgs<Base, IntVectorSortArgs, T>(tests, TEST_SIZES,
        &IntVectorSortFixture::sortedFirstElementGenerator);
    createTestArgs<Base, IntVectorSortArgs, T>(tests, TEST_SIZES,
        &IntVectorSortFixture::sortedLastElementGenerator);
    createTestArgs<Base, IntVectorSortArgs, T>(tests, TEST_SIZES,
        &IntVectorSortFixture::randomGenerator);
    return tests;
}

INSTANTIATE_TEST_SUITE_P(
    SortPrefix,
    IntVectorSortFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Sort
