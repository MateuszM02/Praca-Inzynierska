#include "IntVectorTests.hpp"

#define SMALL_TEST 1'000
#define MEDIUM_TEST 5'000
#define BIG_TEST 10'000

namespace tests::MinMax
{

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    VectorOfVectorsMinMaxFixture,
    ::testing::Values(
        // generator rosnacych liczb
        std::make_shared<VectorOfVectorsMinMaxArgs>(
            VectorOfVectorsMinMaxFixture::sortedLastElementGenerator, SMALL_TEST),
        std::make_shared<VectorOfVectorsMinMaxArgs>(
            VectorOfVectorsMinMaxFixture::sortedLastElementGenerator, MEDIUM_TEST),
        std::make_shared<VectorOfVectorsMinMaxArgs>(
            VectorOfVectorsMinMaxFixture::sortedLastElementGenerator, BIG_TEST),

        // generator malejacych liczb
        std::make_shared<VectorOfVectorsMinMaxArgs>(
            VectorOfVectorsMinMaxFixture::randomGenerator, SMALL_TEST),
        std::make_shared<VectorOfVectorsMinMaxArgs>(
            VectorOfVectorsMinMaxFixture::randomGenerator, MEDIUM_TEST),
        std::make_shared<VectorOfVectorsMinMaxArgs>(
            VectorOfVectorsMinMaxFixture::randomGenerator, BIG_TEST)
    ));

} // namespace tests::MinMax
