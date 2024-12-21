#include "PointsTests.hpp"

namespace tests::NthElement
{

INSTANTIATE_TEST_SUITE_P(
    PointsPrefix,
    PointsFixture,
    ::testing::Values(
        PointsArgs(PointsFixture::fmod3i3_mod7i64,
                   1000, 30000),
        PointsArgs(PointsFixture::f3i_mod9i64,
                   1000, 70000)
    ));

} // namespace tests::NthElement
