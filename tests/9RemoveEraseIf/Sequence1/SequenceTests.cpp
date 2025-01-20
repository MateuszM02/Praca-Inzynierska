#include "SequenceTests.hpp"

#define MERSENNE_TEST_SIZES std::vector<unsigned int>{ 100'000, 200'000 }
#define DIVISORS_TEST_SIZES std::vector<unsigned int>{ 100'000, 200'000 }
#define SUM_TEST_SIZES std::vector<unsigned int>{ 25'000, 50'000 }

namespace tests::RemoveEraseIf
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    static std::vector<std::shared_ptr<Base>> tests;
    using T = bool(*)(const unsigned int&);

    createTestArgs<Base, SequenceArgs, T>(tests, MERSENNE_TEST_SIZES, SequenceIntFixture::isMersenneNumber);
    createTestArgs<Base, SequenceArgs, T>(tests, DIVISORS_TEST_SIZES, SequenceIntFixture::hasAtMost4Divisors);
    createTestArgs<Base, SequenceArgs, T>(tests, SUM_TEST_SIZES, SequenceIntFixture::is1toNSumOdd);
    return tests;
}

TEST_P(SequenceIntFixture, SequenceRemoveEraseIfTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    SequencePrefix,
    SequenceIntFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::RemoveEraseIf
