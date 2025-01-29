#include "UIntTests.hpp"

#define BASE_SIZE 2'000'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::MinMax
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = unsigned int(*)(const unsigned int);
    createTestArgs<Base, BasicSetMinMaxArgs, T>(
        tests, TEST_SIZES, &BasicSetMinMaxFixture::sortedGenerator);
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
