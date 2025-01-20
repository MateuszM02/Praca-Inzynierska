#include "TransformTests.hpp"

#define FEW_VECTORS 1'000
#define MANY_VECTORS 5'000

#define SMALL_VECTORS 1'000
#define MEDIUM_VECTORS 2'000
#define BIG_VECTORS 3'000

#define TEST_SIZES { TestPair(FEW_VECTORS, SMALL_VECTORS), TestPair(MANY_VECTORS, SMALL_VECTORS), \
    TestPair(FEW_VECTORS, MEDIUM_VECTORS), TestPair(MANY_VECTORS, MEDIUM_VECTORS), \
    TestPair(FEW_VECTORS, BIG_VECTORS), TestPair(MANY_VECTORS, BIG_VECTORS) }

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
