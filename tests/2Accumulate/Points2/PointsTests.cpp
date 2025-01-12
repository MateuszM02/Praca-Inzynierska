#include "PointsTests.hpp"

#define SMALL_TEST 75'000
#define MEDIUM_TEST 400'000

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    PointsAccumulateFixture,
    ::testing::Values(
        // generator rosnacych liczb
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::SumOnly),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::SumAndExtremes),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::SumAndMean),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::DoItAll),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::SumOnly),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::SumAndExtremes),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::SumAndMean),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::DoItAll),

        // generator malejacych liczb
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::SumOnly),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::SumAndExtremes),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::SumAndMean),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::DoItAll),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::SumOnly),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::SumAndExtremes),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::SumAndMean),
        std::make_shared<PointsAccumulateArgs>(
            PointsAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::DoItAll)
    ));

} // namespace tests::Accumulate
