#include "UIntTests.hpp"

#define SMALL_TEST 75'000
#define MEDIUM_TEST 500'000

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    UIntAccumulatePrefix,
    UIntAccumulateFixture,
    ::testing::Values(
        // generator rosnacych liczb
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, AccType::DoItAll),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, AccType::DoItAll),
        // generator malejacych liczb
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, AccType::DoItAll),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, AccType::DoItAll)
    ));

} // namespace tests::Accumulate
