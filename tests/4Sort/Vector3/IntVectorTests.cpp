#include "IntVectorTests.hpp"

#define BASE_SIZE 2'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Sort
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableIntVector(*)(const unsigned int);

    createTestArgs<Base, IntVectorSortArgs, T>(tests, TEST_SIZES,
        &IntVectorSortFixture::sortedGenerator);
    createTestArgs<Base, IntVectorSortArgs, T>(tests, TEST_SIZES,
        &IntVectorSortFixture::reverseSortedGenerator);
    createTestArgs<Base, IntVectorSortArgs, T>(tests, TEST_SIZES,
        &IntVectorSortFixture::randomGenerator);
    return tests;
}

TEST_P(IntVectorSortFixture, IntVectorSortTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    SortPrefix,
    IntVectorSortFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Sort
