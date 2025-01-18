#include "IntVectorTests.hpp"

#define TEST_SIZES { 1'000, 5'000, 10'000 }

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

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    VectorSetMinMaxFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::MinMax
