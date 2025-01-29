#include "UIntTests.hpp"

#define BASE_SIZE 10'000'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Accumulate
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = unsigned int(*)(const unsigned int);

    createTestArgs<Base, UIntAccumulateArgs, T, AccType>(
        tests, TEST_SIZES, &UIntAccumulateFixture::sortedGenerator, AccType::DoItAll);
    return tests;
}

TEST_P(UIntAccumulateFixture, UIntAccumulateTest)
{
    VerifyTestCustomFor2(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    UIntAccumulateFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Accumulate
