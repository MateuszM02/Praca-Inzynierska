#include "RandomStringTests.hpp"

#define SMALL_N 500
#define MEDIUM_N 5'000
#define BIG_N 60'000
#define HUGE_N 250'000

#define FEW_STRINGS 10'000
#define MEDIUM_STRINGS 75'000
#define MANY_STRINGS 300'000

#define STRING_LENGTH 32

#define TEST_SIZES { TestPair(SMALL_N, FEW_STRINGS), TestPair(MEDIUM_N, FEW_STRINGS), \
    TestPair(MEDIUM_N, MEDIUM_STRINGS), TestPair(BIG_N, MEDIUM_STRINGS), \
    TestPair(BIG_N, MANY_STRINGS), TestPair(HUGE_N, MANY_STRINGS) }

namespace tests::NthElement
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    createTestArgs<Base, RandomStringNthElementArgs, unsigned int>(tests, TEST_SIZES, STRING_LENGTH);
    return tests;
}

INSTANTIATE_TEST_SUITE_P(
    NthElementPrefix,
    RandomStringNthElementFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::NthElement
