#include "RandomStringTests.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    RandomStringGeneratePrefix,
    RandomStringGenerateFixture,
    ::testing::Values( // dlugosc slowa, ilosc slow
        RandomStringGenerateArgs(1u, 1000000u),
        RandomStringGenerateArgs(20u, 50000u),
        RandomStringGenerateArgs(200u, 5000u),
        RandomStringGenerateArgs(1000u, 1000u),
        RandomStringGenerateArgs(5000u, 200u),
        RandomStringGenerateArgs(50000u, 20u),
        RandomStringGenerateArgs(1000000u, 1u)
));

} // namespace tests::Generate
