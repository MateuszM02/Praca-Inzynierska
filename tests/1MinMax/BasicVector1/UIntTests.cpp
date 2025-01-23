#include "UIntTests.hpp"

#define TEST_SIZES { 100'000'000, 200'000'000, 300'000'000 }

namespace tests::MinMax
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = unsigned int(*)(const unsigned int);
    createTestArgs<Base, BasicVectorMinMaxArgs, T>(
        tests, TEST_SIZES, &BasicVectorMinMaxFixture::sortedGenerator);
    createTestArgs<Base, BasicVectorMinMaxArgs, T>(
        tests, TEST_SIZES, &BasicVectorMinMaxFixture::reverseSortedGenerator);
    return tests;
}

TEST_P(BasicVectorMinMaxFixture, BasicVectorMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    BasicVectorMinMaxFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::MinMax
