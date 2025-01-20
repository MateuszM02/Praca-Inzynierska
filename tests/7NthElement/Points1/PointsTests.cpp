#include "PointsTests.hpp"

#define SMALL_N 500
#define MEDIUM_N 5'000
#define BIG_N 40'000
#define HUGE_N 75'000

#define FEW_POINTS 75'000
#define MEDIUM_POINTS 250'000
#define MANY_POINTS 500'000

#define TEST_SIZES { TestPair(SMALL_N, FEW_POINTS), TestPair(MEDIUM_N, FEW_POINTS), \
    TestPair(MEDIUM_N, MEDIUM_POINTS), TestPair(BIG_N, MEDIUM_POINTS), \
    TestPair(HUGE_N, MANY_POINTS) }

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
