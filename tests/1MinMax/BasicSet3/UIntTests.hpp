#pragma once

#include "../MinMaxTestFixture.hpp"

namespace tests::MinMax
{

struct BasicSetMinMaxArgs final : public MinMaxTestStruct<std::set<unsigned int>>
{
    explicit BasicSetMinMaxArgs(
        unsigned int (*f)(const unsigned int),
        const unsigned int n)
    : MinMaxTestStruct<std::set<unsigned int>>(
        TestType::MinMaxBasicSet,
        std::make_shared<MinMaxFinder<std::set<unsigned int>>>(
            initTestData<std::set<unsigned int>>(f, n)))
    { }
};

class BasicSetMinMaxFixture : public MinMaxTestFixture<std::set<unsigned int>>
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
    VerifyTest(GetParam());
}

} // namespace tests::MinMax
