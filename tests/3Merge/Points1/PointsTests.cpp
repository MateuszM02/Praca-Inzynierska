#include "PointsTests.hpp"

namespace tests::Merge::Points1tests
{

PointsArgs::PointsArgs(
    const std::string& path,
    VectorStruct<Points1::Point2D> vectors)
: MergeTestStruct<Points1::Point2D>(
    path,
    std::make_shared<Points1::Points>(),
    std::move(vectors.v1),
    std::move(vectors.v2),
    std::move(vectors.expectedResult))
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
                                4000000,
                                1000000))))
    ));

} // namespace tests::Merge::Points1tests
