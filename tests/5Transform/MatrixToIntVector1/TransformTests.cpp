#include "TransformTests.hpp"

#define TEST_SIZES { 200, 400, 800 }

namespace tests::Transform
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = NonCopyableMatrix<int>(*)(const unsigned int);

    createTestArgs<Base, MatrixToIntVectorTransformArgs, T>(tests, TEST_SIZES,
        &MatrixToIntVectorTransformFixture::sortedFirstElementGenerator);
    return tests;
}

INSTANTIATE_TEST_SUITE_P(
    TransformPrefix,
    MatrixToIntVectorTransformFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Transform
