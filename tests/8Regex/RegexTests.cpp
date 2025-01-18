#include "RegexTests.hpp"

#define TEST_SIZES { 10'000'000, 20'000'000, 30'000'000 }

namespace tests::Regex
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    static std::vector<std::shared_ptr<Base>> tests;
    createTestArgs<Base, RegexTestStruct, ERegexTestType>(tests, TEST_SIZES, ERegexTestType::date);
    createTestArgs<Base, RegexTestStruct, ERegexTestType>(tests, TEST_SIZES, ERegexTestType::phone);
    return tests;
}

INSTANTIATE_TEST_SUITE_P(
    RegexPrefix,
    RegexTestFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Regex
