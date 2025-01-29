#include "IntVectorTests.hpp"

#define BASE_SIZE 2'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Merge
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableIntVector(*)(const unsigned int);

    createTestArgs<Base, IntVectorMergeArgs, T, T>(tests, TEST_SIZES,
        &IntVectorMergeFixture::fun1,
        &IntVectorMergeFixture::fun2);
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
