#include "SequenceTests.hpp"

#define MERSENNE_TEST_SIZES std::vector<unsigned int>{ 1'000'000, 2'000'000 }
#define DIVISORS_TEST_SIZES std::vector<unsigned int>{ 300'000, 600'000 }
#define SUM_TEST_SIZES std::vector<unsigned int>{ 20'000, 40'000 }

namespace tests::RemoveEraseIf
{

static std::vector<std::shared_ptr<Base1>> getTests()
{
    static std::vector<std::shared_ptr<Base1>> tests;
    using T = bool(*)(const unsigned int&);

    createTestArgs<Base1, SequenceRemoveEraseIfArgs, T>(
        tests, MERSENNE_TEST_SIZES, SequenceRemoveEraseIfFixture::isMersenneNumber);
    createTestArgs<Base1, SequenceRemoveEraseIfArgs, T>(
        tests, DIVISORS_TEST_SIZES, SequenceRemoveEraseIfFixture::hasAtMost4Divisors);
    createTestArgs<Base1, SequenceRemoveEraseIfArgs, T>(
        tests, SUM_TEST_SIZES, SequenceRemoveEraseIfFixture::is1toNSumOdd);
    return tests;
}

TEST_P(SequenceRemoveEraseIfFixture, SequenceRemoveEraseIfTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    SequencePrefix,
    SequenceRemoveEraseIfFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::RemoveEraseIf
