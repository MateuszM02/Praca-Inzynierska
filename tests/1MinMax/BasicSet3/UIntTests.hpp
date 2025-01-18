#pragma once

#include "../MinMaxTestFixture.hpp"

namespace tests::MinMax
{

using Base = BaseTestStruct<CopyableUIntPair>;
using Parent = MinMaxTestStruct<std::set<unsigned int>, CopyableUIntPair>;

struct BasicSetMinMaxArgs final : public Parent
{
    explicit BasicSetMinMaxArgs(
        unsigned int (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::MinMaxBasicSet,
        [dataCreator, n]()
        {
            std::set<unsigned int> data =
                BaseTestStruct::initTestData<std::set<unsigned int>>(dataCreator, n);
            return std::make_shared<MinMaxFinder<
                std::set<unsigned int>>>(std::move(data));
        })
    { }
};

class BasicSetMinMaxFixture : public MinMaxUIntTestFixture
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
