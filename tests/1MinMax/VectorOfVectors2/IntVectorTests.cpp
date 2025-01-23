#include "IntVectorTests.hpp"

#define TEST_SIZES { 10'000, 20'000, 30'000 }

namespace tests::MinMax
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableIntVector(*)(const unsigned int);
    createTestArgs<Base, VectorOfVectorsMinMaxArgs, T>(
        tests, TEST_SIZES, &VectorOfVectorsMinMaxFixture::sortedLastElementGenerator);
    createTestArgs<Base, VectorOfVectorsMinMaxArgs, T>(
        tests, TEST_SIZES, &VectorOfVectorsMinMaxFixture::randomGenerator);
    return tests;
}

TEST_P(VectorOfVectorsMinMaxFixture, VectorOfVectorsMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    VectorOfVectorsMinMaxFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::MinMax
