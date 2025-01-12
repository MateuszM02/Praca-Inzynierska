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
    NthElementPrefix,
    RandomStringNthElementFixture,
    ::testing::Values(
        // Mala ilosc napisow
        std::make_shared<RandomStringNthElementArgs>(SMALL_N, FEW_STRINGS, STRING_LENGTH),
        std::make_shared<RandomStringNthElementArgs>(MEDIUM_N, FEW_STRINGS, STRING_LENGTH),
        // Srednia ilosc napisow
        std::make_shared<RandomStringNthElementArgs>(MEDIUM_N, MEDIUM_STRINGS, STRING_LENGTH),
        std::make_shared<RandomStringNthElementArgs>(BIG_N, MEDIUM_STRINGS, STRING_LENGTH),
        // Duza ilosc napisow
        std::make_shared<RandomStringNthElementArgs>(BIG_N, MANY_STRINGS, STRING_LENGTH),
        std::make_shared<RandomStringNthElementArgs>(HUGE_N, MANY_STRINGS, STRING_LENGTH)
    ));

} // namespace tests::NthElement
