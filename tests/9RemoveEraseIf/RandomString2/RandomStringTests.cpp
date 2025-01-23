#include "RandomStringTests.hpp"

#define FEW_STRINGS 20'000
#define MANY_STRINGS 40'000

#define SHORT_STRINGS 1'000
#define LONG_STRINGS 2'000

#define TEST_SIZES { TestPair(FEW_STRINGS, SHORT_STRINGS), TestPair(MANY_STRINGS, SHORT_STRINGS), \
    TestPair(FEW_STRINGS, LONG_STRINGS), TestPair(MANY_STRINGS, LONG_STRINGS) }

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
