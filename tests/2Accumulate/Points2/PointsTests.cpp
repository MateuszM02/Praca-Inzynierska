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
                   SMALL_TEST, AccType::SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::DoItAll),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::DoItAll),
        // generator malejacych liczb
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::DoItAll),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::SumOnly),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::SumAndExtremes),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::SumAndMean),
        PointsAccumulateArgs(PointsAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::DoItAll)
    ));

} // namespace tests::Accumulate
