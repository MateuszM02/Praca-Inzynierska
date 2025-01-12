#include "SequenceTests.hpp"

#define MERSENNE_TEST_SIZE 100'000
#define DIVISORS_TEST_SIZE 150'000
#define SUM_TEST_SIZE 25'000

namespace tests::RemoveEraseIf
{

INSTANTIATE_TEST_SUITE_P(
    SequencePrefix,
    SequenceIntFixture,
    ::testing::Values(
        std::make_shared<SequenceArgs>(MERSENNE_TEST_SIZE, SequenceIntFixture::isMersenneNumber),
        std::make_shared<SequenceArgs>(DIVISORS_TEST_SIZE, SequenceIntFixture::hasAtMost4Divisors),
        std::make_shared<SequenceArgs>(SUM_TEST_SIZE, SequenceIntFixture::is1toNSumOdd)
    ));

} // namespace tests::RemoveEraseIf
