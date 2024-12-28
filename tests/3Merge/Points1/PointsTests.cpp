#include "PointsTests.hpp"

namespace tests::Merge
{

INSTANTIATE_TEST_SUITE_P(
    PointsMergePrefix,
    PointsMergeFixture,
    ::testing::Values(
        PointsMergeArgs(PointsMergeFixture::fmod3i3_mod7i64,
                   PointsMergeFixture::f3i_mod9i64,
                   300000, 200000),
        PointsMergeArgs(PointsMergeFixture::fmod3i3_mod7i64,
                   PointsMergeFixture::f3i_mod9i64,
                   700000, 300000),
        PointsMergeArgs(PointsMergeFixture::fmod3i3_mod7i64,
                   PointsMergeFixture::f3i_mod9i64,
                   2000000, 1000000)
    ));

} // namespace tests::Merge
