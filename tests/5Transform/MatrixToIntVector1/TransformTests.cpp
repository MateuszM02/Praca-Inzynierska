#include "TransformTests.hpp"

#define TEST_SIZES { 200, 400, 600 }

namespace tests::Transform
{

static std::vector<std::shared_ptr<Base1>> getTests()
{
    std::vector<std::shared_ptr<Base1>> tests;
    using T = NonCopyableMatrix<int>(*)(const unsigned int);

    createTestArgs<Base1, MatrixToIntVectorTransformArgs, T>(tests, TEST_SIZES,
        &MatrixToIntVectorTransformFixture::sortedFirstElementGenerator);
    return tests;
}

TEST_P(MatrixToIntVectorTransformFixture, MatrixToIntVectorTransformTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    TransformPrefix,
    MatrixToIntVectorTransformFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Transform
