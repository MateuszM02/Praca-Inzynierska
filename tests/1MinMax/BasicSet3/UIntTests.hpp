#pragma once

#include "../MinMaxTestFixture.hpp"

namespace tests::MinMax
{

struct BasicSetMinMaxArgs final : public MinMaxTestStruct<
    std::set<unsigned int>, Point2D<>>
{
    explicit BasicSetMinMaxArgs(
        unsigned int (*dataCreator)(const unsigned int),
        const unsigned int n)
    : MinMaxTestStruct<std::set<unsigned int>, Point2D<>>(
        TestType::MinMaxBasicSet,
        [dataCreator, n]()
        {
            std::set<unsigned int> data =
                BaseTestStruct::initTestData<std::set<unsigned int>>(dataCreator, n);
            return std::make_shared<MinMaxFinder<
                std::set<unsigned int>>>(std::move(data));
        })
    { }
};

class BasicSetMinMaxFixture : public MinMaxTestFixture<>
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

TEST_P(BasicSetMinMaxFixture, BasicSetMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

} // namespace tests::MinMax
