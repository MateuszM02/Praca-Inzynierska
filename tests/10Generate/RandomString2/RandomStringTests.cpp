#include "RandomStringTests.hpp"

namespace tests::Generate
{

INSTANTIATE_TEST_SUITE_P(
    RandomStringPrefix, 
    RandomStringFixture,
    ::testing::Values( // dlugosc slowa, ilosc slow
        RandomStringArgs(1u, 1000000u),
        RandomStringArgs(20u, 50000u),
        RandomStringArgs(200u, 5000u),
        RandomStringArgs(1000u, 1000u),
        RandomStringArgs(5000u, 200u),
        RandomStringArgs(50000u, 20u),
        RandomStringArgs(1000000u, 1u)
));

} // namespace tests::Generate
