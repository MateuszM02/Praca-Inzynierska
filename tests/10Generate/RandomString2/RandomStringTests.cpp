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
        std::make_shared<RandomStringGenerateArgs>(1u, 1000000u),
        std::make_shared<RandomStringGenerateArgs>(20u, 50000u),
        std::make_shared<RandomStringGenerateArgs>(200u, 5000u),
        std::make_shared<RandomStringGenerateArgs>(1000u, 1000u),
        std::make_shared<RandomStringGenerateArgs>(5000u, 200u),
        std::make_shared<RandomStringGenerateArgs>(50000u, 20u),
        std::make_shared<RandomStringGenerateArgs>(1000000u, 1u)
));

} // namespace tests::Generate
