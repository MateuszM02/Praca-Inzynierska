#include "IntVectorTests.hpp"

#define TEST_SIZES { TestPair(3'000, 3'000), TestPair(6'000, 6'000), \
    TestPair(9'000, 9'000), TestPair( 12'000, 12'000) }

namespace tests::Merge
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableIntVector(*)(const unsigned int);

    createTestArgs<Base, IntVectorMergeArgs, T, T>(tests, TEST_SIZES,
        &IntVectorMergeFixture::f10i_imod7,
        &IntVectorMergeFixture::f10i_imod9);
    return tests;
}

TEST_P(IntVectorMergeFixture, IntVectorTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MergePrefix,
    IntVectorMergeFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Merge
