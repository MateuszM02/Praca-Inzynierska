#include "UIntTests.hpp"

#define TEST_SIZES { 25'000'000, 50'000'000, 75'000'000 }

namespace tests::Accumulate
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = unsigned int(*)(const unsigned int);

    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::sortedGenerator, AccType::SumOnly);
    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::sortedGenerator, AccType::SumAndExtremes);
    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::sortedGenerator, AccType::SumAndMean);
    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::sortedGenerator, AccType::DoItAll);

    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::reverseSortedGenerator, AccType::SumOnly);
    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::reverseSortedGenerator, AccType::SumAndExtremes);
    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::reverseSortedGenerator, AccType::SumAndMean);
    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::reverseSortedGenerator, AccType::DoItAll);
    return tests;
}

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    UIntAccumulateFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Accumulate
