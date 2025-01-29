#include "PointsTests.hpp"

#define BASE_SIZE 100'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Merge
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, PointsMergeArgs, T, T>(tests, TEST_SIZES,
        &PointsMergeFixture::fmod3i3_mod7i64,
        &PointsMergeFixture::f3i_mod9i64);
    return tests;
}

TEST_P(PointsMergeFixture, PointsMergeTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MergePrefix,
    PointsMergeFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Merge
