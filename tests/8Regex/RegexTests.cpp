#include "RegexTests.hpp"

#define BASE_SIZE 5'000'000

#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Regex
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    static std::vector<std::shared_ptr<Base>> tests;
    createTestArgs<Base, RegexTestStruct, ERegexTestType>(tests, TEST_SIZES, ERegexTestType::date);
    createTestArgs<Base, RegexTestStruct, ERegexTestType>(tests, TEST_SIZES, ERegexTestType::phone);
    return tests;
}

TEST_P(RegexTestFixture, RegexTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    RegexPrefix,
    RegexTestFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Regex
