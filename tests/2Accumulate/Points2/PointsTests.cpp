#include "PointsTests.hpp"

#define TEST_SIZES { 100'000, 200'000, 300'000 }

namespace tests::Accumulate
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::sortedGenerator, AccType::SumOnly);
    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::sortedGenerator, AccType::SumAndExtremes);
    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::sortedGenerator, AccType::SumAndMean);
    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::sortedGenerator, AccType::DoItAll);

    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::reverseSortedGenerator, AccType::SumOnly);
    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::reverseSortedGenerator, AccType::SumAndExtremes);
    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::reverseSortedGenerator, AccType::SumAndMean);
    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::reverseSortedGenerator, AccType::DoItAll);
    return tests;
}

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    PointsAccumulateFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Accumulate
