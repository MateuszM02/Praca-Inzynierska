#include "SequenceTests.hpp"

#define BASE_SIZE 200'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::RemoveEraseIf
{

static std::vector<std::shared_ptr<Base1>> getTests()
{
    static std::vector<std::shared_ptr<Base1>> tests;
    using T = bool(*)(const unsigned int&);

    createTestArgs<Base1, SequenceRemoveEraseIfArgs, T>(
        tests, TEST_SIZES, SequenceRemoveEraseIfFixture::hasAtMost4Divisors);
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
