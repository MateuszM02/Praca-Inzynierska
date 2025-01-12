#include "UIntTests.hpp"

#define SMALL_TEST 1'000'000
#define MEDIUM_TEST 5'000'000
#define BIG_TEST 15'000'000

namespace tests::MinMax
{

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    BasicVectorMinMaxFixture,
    ::testing::Values(
        // generator rosnacych liczb
        std::make_shared<BasicVectorMinMaxArgs>(
            BasicVectorMinMaxFixture::sortedGenerator, SMALL_TEST),
        std::make_shared<BasicVectorMinMaxArgs>(
            BasicVectorMinMaxFixture::sortedGenerator, MEDIUM_TEST),
        std::make_shared<BasicVectorMinMaxArgs>(
            BasicVectorMinMaxFixture::sortedGenerator, BIG_TEST),

        // generator malejacych liczb
        std::make_shared<BasicVectorMinMaxArgs>(
            BasicVectorMinMaxFixture::reverseSortedGenerator, SMALL_TEST),
        std::make_shared<BasicVectorMinMaxArgs>(
            BasicVectorMinMaxFixture::reverseSortedGenerator, MEDIUM_TEST),
        std::make_shared<BasicVectorMinMaxArgs>(
            BasicVectorMinMaxFixture::reverseSortedGenerator, BIG_TEST)
    ));

} // namespace tests::MinMax
