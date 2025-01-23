#include "PointsTests.hpp"

#define FEW_POINTS 100'000
#define MEDIUM_POINTS 200'000
#define MANY_POINTS 300'000

#define TEST_SIZES { TestPair(FEW_POINTS / 100, FEW_POINTS), \
    TestPair(FEW_POINTS / 2, FEW_POINTS), TestPair(FEW_POINTS * 0.99, FEW_POINTS), \
    TestPair(MEDIUM_POINTS / 100, MEDIUM_POINTS), TestPair(MEDIUM_POINTS / 2, MEDIUM_POINTS), \
    TestPair(MEDIUM_POINTS * 0.99, MEDIUM_POINTS), TestPair(MANY_POINTS / 100, MANY_POINTS), \
    TestPair(MANY_POINTS / 2, MANY_POINTS), TestPair(MANY_POINTS * 0.99, MANY_POINTS) }

namespace tests::NthElement
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, PointsNthElementArgs, T>(tests, TEST_SIZES,
        &PointsNthElementFixture::fmod3i3_mod7i64);
    createTestArgs<Base, PointsNthElementArgs, T>(tests, TEST_SIZES,
        &PointsNthElementFixture::f3i_mod9i64);
    return tests;
}

TEST_P(PointsNthElementFixture, PointsNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    NthElementPrefix,
    PointsNthElementFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::NthElement
