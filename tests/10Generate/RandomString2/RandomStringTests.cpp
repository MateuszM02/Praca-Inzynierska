#include "RandomStringTests.hpp"

#define STRING_LENGTH 1'000
#define BASE_COUNT 50'000
#define TEST_COUNTS TEST_SIZES10(BASE_COUNT)

namespace tests::Generate
{

TEST_P(RandomStringGenerateFixture, RandomStringGenerateTest)
{
    VerifyTestCustomForRandomStringGenerator(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    RandomStringGenerateFixture,
    ::testing::Values(
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[0]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[1]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[2]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[3]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[4]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[5]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[6]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[7]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[8]),
        std::make_shared<RandomStringGenerateArgs>(STRING_LENGTH, TEST_COUNTS[9])
));

} // namespace tests::Generate
