#include "TransformTests.hpp"

#define BASE_SIZE 75
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

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
