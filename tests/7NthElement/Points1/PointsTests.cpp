#include "PointsTests.hpp"

#define BASE_SIZE 100'000
#define TEST_SIZES TEST_SIZES10_PAIRS(BASE_SIZE / 2, BASE_SIZE)

namespace tests::NthElement
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, PointsNthElementArgs, T>(tests, TEST_SIZES,
       &PointsNthElementFixture::sortedGenerator);
    return tests;
}

TEST_P(PointsNthElementFixture, PointsNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    NthElementPrefix,
    PointsNthElementFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::NthElement
