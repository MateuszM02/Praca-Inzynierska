#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/Structures/IntVector.hpp"

using namespace src::Structures;

namespace tests::Merge
{

struct IntVectorArgs final : public MergeTestStruct<IntVector>
{
    IntVectorArgs(
        Mergeable<IntVector> (*fun1)(const unsigned int),
        Mergeable<IntVector> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    : MergeTestStruct<IntVector>(
        this->createPath(MergeIntVector),
        std::move(std::make_shared<Merger<IntVector>>(
            MergeTestFixture<IntVector>::initTestData(fun1, fun2, n1, n2))))
    { }
};

class IntVectorFixture : public MergeTestFixture<IntVector>
{
public:
    static Mergeable<IntVector> f10i_imod7(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + ((i+1) % 7));
        }
        IntVector iv(std::move(v));
        return { std::move(iv),
                 src::Algorithms::MergerImpl::intVectorEqFunc,
                 src::Algorithms::MergerImpl::intVectorLessFunc,
                 src::Algorithms::MergerImpl::intVectorCopyAssignFunc };
    }

    static Mergeable<IntVector> f10i_imod9(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + (i % 9));
        }
        IntVector iv(std::move(v));
        return { std::move(iv),
                 src::Algorithms::MergerImpl::intVectorEqFunc,
                 src::Algorithms::MergerImpl::intVectorLessFunc,
                 src::Algorithms::MergerImpl::intVectorCopyAssignFunc };
    }
};

TEST_P(IntVectorFixture, IntVectorTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge
