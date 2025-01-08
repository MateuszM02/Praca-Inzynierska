#include "UIntTests.hpp"

#define SMALL_TEST 1'000'000
#define MEDIUM_TEST 5'000'000
#define BIG_TEST 15'000'000

namespace tests::MinMax
{

INSTANTIATE_TEST_SUITE_P(
    BasicVectorMinMaxPrefix,
    BasicVectorMinMaxFixture,
    ::testing::Values(
        // generator rosnacych liczb
        BasicVectorMinMaxArgs(BasicVectorMinMaxFixture::sortedGenerator,
                   SMALL_TEST),
        BasicVectorMinMaxArgs(BasicVectorMinMaxFixture::sortedGenerator,
                   MEDIUM_TEST),
        BasicVectorMinMaxArgs(BasicVectorMinMaxFixture::sortedGenerator,
                   BIG_TEST),
        // generator malejacych liczb
        BasicVectorMinMaxArgs(BasicVectorMinMaxFixture::reverseSortedGenerator,
                   SMALL_TEST),
        BasicVectorMinMaxArgs(BasicVectorMinMaxFixture::reverseSortedGenerator,
                   MEDIUM_TEST),
        BasicVectorMinMaxArgs(BasicVectorMinMaxFixture::reverseSortedGenerator,
                   BIG_TEST)
    ));

} // namespace tests::MinMax
