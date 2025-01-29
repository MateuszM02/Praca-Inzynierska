#include "RandomStringTests.hpp"

#define BASE_COUNT 10'000
#define BASE_SIZE 1'000

#define TEST_SIZES TEST_SIZES10_PAIRS(BASE_COUNT, BASE_SIZE)

namespace tests::RemoveEraseIf
{

static std::vector<std::shared_ptr<Base2>> getTests()
{
    static std::vector<std::shared_ptr<Base2>> tests;
    using T = bool(*)(const std::string&);

    createTestArgs<Base2, RandomStringRemoveEraseIfArgs, T>(
        tests, TEST_SIZES, RandomStringRemoveEraseIfFixture::startsWithVowel);
    createTestArgs<Base2, RandomStringRemoveEraseIfArgs, T>(
        tests, TEST_SIZES, RandomStringRemoveEraseIfFixture::moreVowelsThanConsonants);
    return tests;
}

TEST_P(RandomStringRemoveEraseIfFixture, RandomStringRemoveEraseIfTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    RandomStringPrefix,
    RandomStringRemoveEraseIfFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::RemoveEraseIf
