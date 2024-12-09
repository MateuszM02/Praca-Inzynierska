#include "PointsTests.hpp"

namespace tests::Merge::Points1tests
{

PointsArgs::PointsArgs(
    const std::string& path,
    const VectorStruct<Points1::Point2D>& vectors)
: MergeTestStruct<Points1::Point2D>(
    path,
    std::make_shared<Points1::Points>(),
    vectors)
{ }

INSTANTIATE_TEST_SUITE_P(
    PointsPrefix,
    PointsFixture,
    ::testing::Values(
        PointsArgs(
            Path::Create(MergePoints, 1),
            PointsFixture::initPoints(PointsFixture::fmod3i3_mod7i64, PointsFixture::f3i_mod9i64, 300000, 200000)),
        PointsArgs(
            Path::Create(MergePoints, 2),
            PointsFixture::initPoints(PointsFixture::fmod3i3_mod7i64, PointsFixture::f3i_mod9i64, 700000, 300000)),
        PointsArgs(
            Path::Create(MergePoints, 3),
            PointsFixture::initPoints(PointsFixture::fmod3i3_mod7i64, PointsFixture::f3i_mod9i64, 4000000, 1000000))
    ));

} // namespace tests::Merge::Points1tests
