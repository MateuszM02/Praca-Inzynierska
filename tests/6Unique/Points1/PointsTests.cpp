#include "PointsTests.hpp"

#define BASE_SIZE 200'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::Unique
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, UniquePointsArgs, T>(tests, TEST_SIZES,
         &UniquePointsFixture::noCopiesGenerator);
    createTestArgs<Base, UniquePointsArgs, T>(tests, TEST_SIZES,
        &UniquePointsFixture::onlyCopiesGenerator);
    return tests;
}

TEST_P(UniquePointsFixture, UniquePointsTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    UniquePrefix,
    UniquePointsFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Unique
