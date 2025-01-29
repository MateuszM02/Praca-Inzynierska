#include "TransformTests.hpp"

#define BASE_COUNT 500
#define BASE_SIZE 500
#define TEST_SIZES TEST_SIZES10_PAIRS(BASE_COUNT, BASE_SIZE)

namespace tests::Transform
{

static std::vector<std::shared_ptr<Base2>> getTests()
{
    std::vector<std::shared_ptr<Base2>> tests;
    using T = InType2(*)(const unsigned int);

    createTestArgs<Base2, VectorToMapTransformArgs, T>(tests, TEST_SIZES,
        &VectorToMapTransformFixture::randomGeneratorOftenCopies);
    createTestArgs<Base2, VectorToMapTransformArgs, T>(tests, TEST_SIZES,
        &VectorToMapTransformFixture::randomGeneratorRareCopies);
    return tests;
}

TEST_P(VectorToMapTransformFixture, VectorToMapTransformTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    TransformPrefix,
    VectorToMapTransformFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Transform
