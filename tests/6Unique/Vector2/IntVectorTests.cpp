#include "IntVectorTests.hpp"

#define FEW_VECTORS 2'000
#define MANY_VECTORS 4'000

#define SMALL_VECTORS 20'000
#define MEDIUM_VECTORS 40'000
#define BIG_VECTORS 60'000

#define TEST_SIZES { TestPair(FEW_VECTORS, SMALL_VECTORS), TestPair(MANY_VECTORS, SMALL_VECTORS), \
    TestPair(FEW_VECTORS, MEDIUM_VECTORS), TestPair(MANY_VECTORS, MEDIUM_VECTORS), \
    TestPair(FEW_VECTORS, BIG_VECTORS), TestPair(MANY_VECTORS, BIG_VECTORS) }

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
