#include "IntVectorTests.hpp"

#define BASE_SIZE 2'500
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::MinMax
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableIntVector(*)(const unsigned int);
    createTestArgs<Base, VectorSetMinMaxArgs, T>(
        tests, TEST_SIZES, &VectorSetMinMaxFixture::sortedLastElementGenerator);
    createTestArgs<Base, VectorSetMinMaxArgs, T>(
        tests, TEST_SIZES, &VectorSetMinMaxFixture::randomGenerator);
    return tests;
}

TEST_P(VectorSetMinMaxFixture, VectorSetMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    VectorSetMinMaxFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::MinMax
