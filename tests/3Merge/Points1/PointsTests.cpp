#include "PointsTests.hpp"

#define TEST_SIZES { TestPair(100'000, 100'000), TestPair(200'000, 200'000), \
    TestPair(300'000, 300'000), TestPair(400'000, 400'000) }

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
