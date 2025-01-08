#include "IntVectorTests.hpp"

#define SMALL_TEST 1'000
#define MEDIUM_TEST 5'000
#define BIG_TEST 10'000

namespace tests::MinMax
{

INSTANTIATE_TEST_SUITE_P(
    VectorOfVectorsMinMaxPrefix,
    VectorOfVectorsMinMaxFixture,
    ::testing::Values(
        // generator rosnacych liczb
        VectorOfVectorsMinMaxArgs(VectorOfVectorsMinMaxFixture::sortedLastElementGenerator,
                   SMALL_TEST),
        VectorOfVectorsMinMaxArgs(VectorOfVectorsMinMaxFixture::sortedLastElementGenerator,
                   MEDIUM_TEST),
        VectorOfVectorsMinMaxArgs(VectorOfVectorsMinMaxFixture::sortedLastElementGenerator,
                   BIG_TEST),
        // generator malejacych liczb
        VectorOfVectorsMinMaxArgs(VectorOfVectorsMinMaxFixture::randomGenerator,
                   SMALL_TEST),
        VectorOfVectorsMinMaxArgs(VectorOfVectorsMinMaxFixture::randomGenerator,
                   MEDIUM_TEST),
        VectorOfVectorsMinMaxArgs(VectorOfVectorsMinMaxFixture::randomGenerator,
                   BIG_TEST)
    ));

} // namespace tests::MinMax
