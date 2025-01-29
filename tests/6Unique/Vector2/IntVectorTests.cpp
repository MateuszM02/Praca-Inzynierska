#include "IntVectorTests.hpp"

#define BASE_COUNT 10'000
#define VECTOR_SIZE 2'000
#define TEST_SIZES TEST_SIZES10_PAIRS_ONLY1RISE(BASE_COUNT, VECTOR_SIZE)

namespace tests::Unique
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = std::vector<int>(*)(const unsigned int);

    createTestArgs<Base, UniqueIntVectorArgs, T>(tests, TEST_SIZES,
        &UniqueIntVectorFixture::noCopiesGenerator);
    createTestArgs<Base, UniqueIntVectorArgs, T>(tests, TEST_SIZES,
        &UniqueIntVectorFixture::onlyCopiesGenerator);
    return tests;
}

TEST_P(UniqueIntVectorFixture, UniqueIntVectorTest)
{
    VerifyTest(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    UniquePrefix,
    UniqueIntVectorFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::Unique
