#include "RandomStringTests.hpp"

namespace tests::Generate
{

TEST_P(RandomStringGenerateFixture, RandomStringGenerateTest)
{
    VerifyTestCustomForRandomStringGenerator(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    GeneratePrefix,
    RandomStringGenerateFixture,
    ::testing::Values( // dlugosc slowa, ilosc slow
        std::make_shared<RandomStringGenerateArgs>(10u, 1'000'000u),
        std::make_shared<RandomStringGenerateArgs>(10u, 2'000'000u),
        std::make_shared<RandomStringGenerateArgs>(1'000u, 50'000u),
        std::make_shared<RandomStringGenerateArgs>(1'000u, 100'000u),
        std::make_shared<RandomStringGenerateArgs>(50'000u, 1'000u),
        std::make_shared<RandomStringGenerateArgs>(100'000u, 1'000u),
        std::make_shared<RandomStringGenerateArgs>(1'000'000u, 10u),
        std::make_shared<RandomStringGenerateArgs>(2'000'000u, 10u)
));

} // namespace tests::Generate
