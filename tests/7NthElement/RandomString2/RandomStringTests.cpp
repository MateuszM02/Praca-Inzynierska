#include "RandomStringTests.hpp"

#define SMALL_N 500
#define MEDIUM_N 5'000
#define BIG_N 60'000
#define HUGE_N 250'000

#define FEW_STRINGS 10'000
#define MEDIUM_STRINGS 75'000
#define MANY_STRINGS 300'000

#define STRING_LENGTH 32

namespace tests::NthElement
{

INSTANTIATE_TEST_SUITE_P(
    RandomStringPrefix,
    RandomStringNthElementFixture,
    ::testing::Values(
        // Mala ilosc napisow
        RandomStringArgs(SMALL_N, FEW_STRINGS, STRING_LENGTH),
        RandomStringArgs(MEDIUM_N, FEW_STRINGS, STRING_LENGTH),
        // Srednia ilosc napisow
        RandomStringArgs(MEDIUM_N, MEDIUM_STRINGS, STRING_LENGTH),
        RandomStringArgs(BIG_N, MEDIUM_STRINGS, STRING_LENGTH),
        // Duza ilosc napisow
        RandomStringArgs(BIG_N, MANY_STRINGS, STRING_LENGTH),
        RandomStringArgs(HUGE_N, MANY_STRINGS, STRING_LENGTH)
    ));

} // namespace tests::NthElement
