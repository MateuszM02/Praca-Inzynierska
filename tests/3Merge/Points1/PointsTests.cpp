#include "PointsTests.hpp"

namespace tests::Merge
{

INSTANTIATE_TEST_SUITE_P(
    PointsMergePrefix,
    PointsMergeFixture,
    ::testing::Values(
        PointsMergeArgs(PointsMergeFixture::fmod3i3_mod7i64,
                   PointsMergeFixture::f3i_mod9i64,
                   300'000, 200'000),
        PointsMergeArgs(PointsMergeFixture::fmod3i3_mod7i64,
                   PointsMergeFixture::f3i_mod9i64,
                   700'000, 300'000),
        PointsMergeArgs(PointsMergeFixture::fmod3i3_mod7i64,
                   PointsMergeFixture::f3i_mod9i64,
                   1'000'000, 600'000)
    ));

} // namespace tests::Merge
