#include "PointsTests.hpp"

#define BASE_SIZE 100'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Accumulate
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, PointsAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &PointsAccumulateFixture::sortedGenerator, AccType::DoItAll);
    return tests;
}

TEST_P(PointsAccumulateFixture, PointsAccumulateTest)
{
    VerifyTestCustomFor2(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    PointsAccumulateFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Accumulate
