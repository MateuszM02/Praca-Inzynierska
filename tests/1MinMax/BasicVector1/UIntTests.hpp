#pragma once

#include "../MinMaxTestFixture.hpp"

namespace tests::MinMax
{

using Base = BaseTestStruct<CopyableUIntPair>;
using Parent = MinMaxTestStruct<std::vector<unsigned int>, CopyableUIntPair>;

struct BasicVectorMinMaxArgs final : public Parent
{
    explicit BasicVectorMinMaxArgs(
        unsigned int (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::MinMaxBasicVector,
        [dataCreator, n]()
        {
            std::vector<unsigned int> data =
                BaseTestStruct::initTestData<std::vector<unsigned int>>(dataCreator, n);
            return std::make_shared<MinMaxFinder<
                std::vector<unsigned int>>>(std::move(data));
        })
    { }
};

class BasicVectorMinMaxFixture : public MinMaxUIntTestFixture
{
public:
    static unsigned int sortedGenerator(const unsigned int i)
    {
        return i;
    }
};

} // namespace tests::MinMax
