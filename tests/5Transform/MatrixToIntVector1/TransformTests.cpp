#include "TransformTests.hpp"

#define SMALL_TEST 100
#define MEDIUM_TEST 400
#define BIG_TEST 900

namespace tests::Transform
{

INSTANTIATE_TEST_SUITE_P(
    MatrixToIntVectorTransformPrefix,
    MatrixToIntVectorTransformFixture,
    ::testing::Values(
        MatrixToIntVectorTransformArgs(
            MatrixToIntVectorTransformFixture::sortedFirstElementGenerator, SMALL_TEST),
        MatrixToIntVectorTransformArgs(
            MatrixToIntVectorTransformFixture::sortedFirstElementGenerator, MEDIUM_TEST),
        MatrixToIntVectorTransformArgs(
            MatrixToIntVectorTransformFixture::sortedFirstElementGenerator, BIG_TEST)
    ));

} // namespace tests::Transform
