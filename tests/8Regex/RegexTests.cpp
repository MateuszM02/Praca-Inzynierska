#include "RegexTests.hpp"

#define SMALL_TEXT_SIZE 100'000
#define MEDIUM_TEXT_SIZE 1'000'000

namespace tests::Regex
{

INSTANTIATE_TEST_SUITE_P(
    RegexPrefix,
    RegexTestFixture,
    ::testing::Values(
        RegexTestStruct(SMALL_TEXT_SIZE, ERegexTestType::date),
        RegexTestStruct(MEDIUM_TEXT_SIZE, ERegexTestType::date),
        RegexTestStruct(SMALL_TEXT_SIZE, ERegexTestType::phone),
        RegexTestStruct(MEDIUM_TEXT_SIZE, ERegexTestType::phone)
    ));

} // namespace tests::Regex
