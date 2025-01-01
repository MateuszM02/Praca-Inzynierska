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
                   SMALL_TEST, SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   SMALL_TEST, DoItAll),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::sortedGenerator,
                   MEDIUM_TEST, DoItAll),
        // generator malejacych liczb
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   SMALL_TEST, DoItAll),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, SumOnly),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, SumAndExtremes),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, SumAndMean),
        UIntAccumulateArgs(UIntAccumulateFixture::reverseSortedGenerator,
                   MEDIUM_TEST, DoItAll)
    ));

} // namespace tests::Accumulate
