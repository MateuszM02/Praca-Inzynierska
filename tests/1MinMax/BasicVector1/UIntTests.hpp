#pragma once

#include "../MinMaxTestFixture.hpp"

namespace tests::MinMax
{

struct BasicVectorMinMaxArgs final : public MinMaxTestStruct<std::vector<unsigned int>>
{
    explicit BasicVectorMinMaxArgs(
        unsigned int (*dataCreator)(const unsigned int),
        const unsigned int n)
    : MinMaxTestStruct<std::vector<unsigned int>>(
        TestType::MinMaxBasicVector,
        [dataCreator, n]()
        {
            std::vector<unsigned int> data =
                BaseTestStruct::initTestData<std::vector<unsigned int>>(dataCreator, n);
            return std::make_shared<MinMaxFinder<std::vector<unsigned int>>>(std::move(data));
        })
    { }
};

class BasicVectorMinMaxFixture : public MinMaxTestFixture<std::vector<unsigned int>>
{
public:
    static unsigned int sortedGenerator(const unsigned int i)
    {
        return i;
    }

    static unsigned int reverseSortedGenerator(const unsigned int i)
    {
        return UINT32_MAX - i;
    }
};

TEST_P(BasicVectorMinMaxFixture, BasicVectorMinMaxTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::MinMax
