#include "RandomStringTests.hpp"

#define BASE_SIZE 1'000'000
#define STRING_LENGTH 32

#define TEST_SIZES TEST_SIZES10_PAIRS(BASE_SIZE / 2, BASE_SIZE)

namespace tests::NthElement
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    createTestArgs<Base, RandomStringNthElementArgs, unsigned int>(tests, TEST_SIZES, STRING_LENGTH);
    return tests;
}

TEST_P(RandomStringNthElementFixture, RandomStringNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    NthElementPrefix,
    RandomStringNthElementFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::NthElement
