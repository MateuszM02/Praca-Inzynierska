#include "PointsTests.hpp"

#define SMALL_TEST 75'000
#define MEDIUM_TEST 400'000

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    PointsAccumulatePrefix,
    PointsAccumulateFixture,
    ::testing::Values(
        // generator rosnacych liczb
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, DoItAll),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, DoItAll),
        // generator malejacych liczb
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, DoItAll),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, DoItAll)
    ));

} // namespace tests::Accumulate
