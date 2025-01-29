#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Merge
{

using Base = BaseTestStruct<std::vector<CopyableIntVector>>;
using Parent = MergeTestStruct<CopyableIntVector>;

struct IntVectorMergeArgs final : public Parent
{
    explicit IntVectorMergeArgs(
        CopyableIntVector (*dataCreator1)(const unsigned int),
        CopyableIntVector (*dataCreator2)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::MergeIntVector,
        [dataCreator1, dataCreator2, n]()
        {
            return initTestData3(dataCreator1, dataCreator2, n);
        })
    { }
};

class IntVectorMergeFixture : public MergeTestFixture<CopyableIntVector>
{
public:
    static CopyableIntVector fun1(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + ((i+1) % 7));
        }
        return CopyableIntVector(std::move(v));
    }

    static CopyableIntVector fun2(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + (i % 9));
        }
        return CopyableIntVector(std::move(v));
    }
};

} // namespace tests::Merge
