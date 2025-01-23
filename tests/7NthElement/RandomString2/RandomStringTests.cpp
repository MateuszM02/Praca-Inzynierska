#include "RandomStringTests.hpp"

#define FEW_STRINGS 400'000
#define MEDIUM_STRINGS 800'000
#define MANY_STRINGS 1'200'000

#define STRING_LENGTH 32

#define TEST_SIZES { TestPair(FEW_STRINGS / 100, FEW_STRINGS), \
    TestPair(FEW_STRINGS / 2, FEW_STRINGS), TestPair(FEW_STRINGS * 0.99, FEW_STRINGS), \
    TestPair(MEDIUM_STRINGS / 100, MEDIUM_STRINGS), TestPair(MEDIUM_STRINGS / 2, MEDIUM_STRINGS), \
    TestPair(MEDIUM_STRINGS * 0.99, MEDIUM_STRINGS), TestPair(MANY_STRINGS / 100, MANY_STRINGS), \
    TestPair(MANY_STRINGS / 2, MANY_STRINGS), TestPair(MANY_STRINGS * 0.99, MANY_STRINGS) }

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
