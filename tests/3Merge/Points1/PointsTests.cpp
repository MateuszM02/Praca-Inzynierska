#include "PointsTests.hpp"

namespace tests::Merge
{

PointsArgs::PointsArgs(
    const std::string& path,
    MergerData<Point2D> vectors)
: MergeTestStruct<Point2D>(
    path,
    std::move(std::make_shared<Merger<Point2D>>(std::move(vectors))))
{ }

INSTANTIATE_TEST_SUITE_P(
    PointsPrefix,
    PointsFixture,
    ::testing::Values(
        std::move(PointsArgs(
                    Path::Create(MergePoints, 1),
                    std::move(PointsFixture::initTestData(
                                PointsFixture::fmod3i3_mod7i64,
                                PointsFixture::f3i_mod9i64,
                                300000,
                                200000)))),
        std::move(PointsArgs(
                    Path::Create(MergePoints, 2),
                    std::move(PointsFixture::initTestData(
                                PointsFixture::fmod3i3_mod7i64,
                                PointsFixture::f3i_mod9i64,
                                700000,
                                300000)))),
        std::move(PointsArgs(
                    Path::Create(MergePoints, 3),
                    std::move(PointsFixture::initTestData(
                                PointsFixture::fmod3i3_mod7i64,
                                PointsFixture::f3i_mod9i64,
                                2000000,
                                1000000))))
    ));

} // namespace tests::Merge
