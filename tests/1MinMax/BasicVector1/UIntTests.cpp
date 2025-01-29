#include "UIntTests.hpp"

#define BASE_SIZE 100'000'000
#define TEST_SIZES TEST_SIZES10(BASE_SIZE)

namespace tests::MinMax
{

static std::vector<std::shared_ptr<Base>> getTests()
{
    std::vector<std::shared_ptr<Base>> tests;
    using T = unsigned int(*)(const unsigned int);
    createTestArgs<Base, BasicVectorMinMaxArgs, T>(
        tests, TEST_SIZES, &BasicVectorMinMaxFixture::sortedGenerator);
    return tests;
}

TEST_P(BasicVectorMinMaxFixture, BasicVectorMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    MinMaxPrefix,
    BasicVectorMinMaxFixture,
    ::testing::ValuesIn(getTests()));

} // namespace tests::MinMax
