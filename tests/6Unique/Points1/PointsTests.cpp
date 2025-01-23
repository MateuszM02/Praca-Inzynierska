#include "PointsTests.hpp"

#define TEST_SIZES { 100'000, 200'000, 300'000 }

namespace tests::Unique
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = CopyableUIntPair(*)(const unsigned int);

    createTestArgs<Base, UniquePointsArgs, T>(tests, TEST_SIZES,
        &UniquePointsFixture::noCopiesGenerator);
    createTestArgs<Base, UniquePointsArgs, T>(tests, TEST_SIZES,
        &UniquePointsFixture::randomGeneratorOftenCopies);
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
