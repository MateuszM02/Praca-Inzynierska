#include "UIntTests.hpp"

#define TEST_SIZES { 250'000, 1'000'000, 2'000'000 }

namespace tests::MinMax
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = unsigned int(*)(const unsigned int);
    createTestArgs<Base, BasicSetMinMaxArgs, T>(
        tests, TEST_SIZES, &BasicSetMinMaxFixture::sortedGenerator);
    createTestArgs<Base, BasicSetMinMaxArgs, T>(
        tests, TEST_SIZES, &BasicSetMinMaxFixture::reverseSortedGenerator);
    return tests;
}

TEST_P(BasicSetMinMaxFixture, BasicSetMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    BasicSetMinMaxFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::MinMax
