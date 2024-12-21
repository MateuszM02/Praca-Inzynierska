#include "PointsTests.hpp"

namespace tests::Merge
{

INSTANTIATE_TEST_SUITE_P(
    PointsPrefix,
    PointsFixture,
    ::testing::Values(
        PointsArgs(PointsFixture::fmod3i3_mod7i64,
                   PointsFixture::f3i_mod9i64,
                   300000, 200000),
        PointsArgs(PointsFixture::fmod3i3_mod7i64,
                   PointsFixture::f3i_mod9i64,
                   700000, 300000),
        PointsArgs(PointsFixture::fmod3i3_mod7i64,
                   PointsFixture::f3i_mod9i64,
                   2000000, 1000000)
    ));

} // namespace tests::Merge
