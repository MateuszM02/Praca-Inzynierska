#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Merge
{

struct IntVectorMergeArgs final : public MergeTestStruct<IntVector>
{
    IntVectorMergeArgs(
        DataWrapper<IntVector> (*fun1)(const unsigned int),
        DataWrapper<IntVector> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    : MergeTestStruct<IntVector>(
        MergeIntVector,
        std::move(std::make_shared<Merger<IntVector>>(
            MergeTestFixture<IntVector>::initTestData(fun1, fun2, n1, n2))))
    { }
};

class IntVectorMergeFixture : public MergeTestFixture<IntVector>
{
public:
    static DataWrapper<IntVector> f10i_imod7(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + ((i+1) % 7));
        }
        return { { std::move(v) }, IntVectorImpl::equal, IntVectorImpl::less };
    }

    static DataWrapper<IntVector> f10i_imod9(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + (i % 9));
        }
        return { { std::move(v) }, IntVectorImpl::equal, IntVectorImpl::less };
    }
};

TEST_P(IntVectorMergeFixture, IntVectorTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge
