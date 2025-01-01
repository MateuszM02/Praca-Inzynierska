#include "PointsTests.hpp"

#define SMALL_N 500
#define MEDIUM_N 5'000
#define BIG_N 40'000
#define HUGE_N 75'000

#define FEW_POINTS 75'000
#define MEDIUM_POINTS 250'000
#define MANY_POINTS 500'000

namespace tests::NthElement
{

INSTANTIATE_TEST_SUITE_P(
    PointsNthElementPrefix,
    PointsNthElementFixture,
    ::testing::Values(
        // Mala ilosc punktow
        PointsNthElementArgs(PointsNthElementFixture::fmod3i3_mod7i64, SMALL_N, FEW_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::f3i_mod9i64, SMALL_N, FEW_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::fmod3i3_mod7i64, MEDIUM_N, FEW_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::f3i_mod9i64, MEDIUM_N, FEW_POINTS),
        // Srednia ilosc punktow
        PointsNthElementArgs(PointsNthElementFixture::fmod3i3_mod7i64, MEDIUM_N, MEDIUM_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::f3i_mod9i64, MEDIUM_N, MEDIUM_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::fmod3i3_mod7i64, BIG_N, MEDIUM_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::f3i_mod9i64, BIG_N, MEDIUM_POINTS),
        // Duza ilosc punktow
        PointsNthElementArgs(PointsNthElementFixture::fmod3i3_mod7i64, BIG_N, MANY_POINTS),
        PointsNthElementArgs(PointsNthElementFixture::fmod3i3_mod7i64, HUGE_N, MANY_POINTS)
    ));

} // namespace tests::NthElement
