#include "UIntTests.hpp"

#define SMALL_TEST 75'000
#define MEDIUM_TEST 500'000

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    UIntAccumulateFixture,
    ::testing::Values(
        // generator rosnacych liczb
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::SumOnly),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::SumAndExtremes),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::SumAndMean),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, SMALL_TEST, AccType::DoItAll),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::SumOnly),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::SumAndExtremes),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::SumAndMean),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::sortedGenerator, MEDIUM_TEST, AccType::DoItAll),

        // generator malejacych liczb
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::SumOnly),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::SumAndExtremes),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::SumAndMean),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, SMALL_TEST, AccType::DoItAll),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::SumOnly),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::SumAndExtremes),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::SumAndMean),
        std::make_shared<UIntAccumulateArgs>(
            UIntAccumulateFixture::reverseSortedGenerator, MEDIUM_TEST, AccType::DoItAll)
    ));

} // namespace tests::Accumulate
