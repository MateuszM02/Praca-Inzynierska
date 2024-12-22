#include "PointsTests.hpp"

#define SMALL_N 500
#define MEDIUM_N 5'000
#define BIG_N 40'000
#define HUGE_N 75'000

#define FEW_POINTS 10'000
#define MEDIUM_POINTS 50'000
#define MANY_POINTS 100'000

namespace tests::NthElement
{

INSTANTIATE_TEST_SUITE_P(
    PointsPrefix,
    PointsNthElementFixture,
    ::testing::Values(
        // Mala ilosc punktow
        PointsArgs(PointsNthElementFixture::fmod3i3_mod7i64, SMALL_N, FEW_POINTS),
        PointsArgs(PointsNthElementFixture::f3i_mod9i64, SMALL_N, FEW_POINTS),
        PointsArgs(PointsNthElementFixture::fmod3i3_mod7i64, MEDIUM_N, FEW_POINTS),
        PointsArgs(PointsNthElementFixture::f3i_mod9i64, MEDIUM_N, FEW_POINTS)
        
        // TODO: Naprawic niedzialajace testy
        
        // // Srednia ilosc punktow
        // PointsArgs(PointsNthElementFixture::fmod3i3_mod7i64, MEDIUM_N, MEDIUM_POINTS),
        // PointsArgs(PointsNthElementFixture::f3i_mod9i64, MEDIUM_N, MEDIUM_POINTS),
        // PointsArgs(PointsNthElementFixture::fmod3i3_mod7i64, BIG_N, MEDIUM_POINTS),
        // PointsArgs(PointsNthElementFixture::f3i_mod9i64, BIG_N, MEDIUM_POINTS),
        // // Duza ilosc punktow
        // PointsArgs(PointsNthElementFixture::fmod3i3_mod7i64, BIG_N, MANY_POINTS),
        // PointsArgs(PointsNthElementFixture::fmod3i3_mod7i64, HUGE_N, MANY_POINTS)
    ));

} // namespace tests::NthElement
