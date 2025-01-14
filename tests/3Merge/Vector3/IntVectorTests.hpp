#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Merge
{

struct IntVectorMergeArgs final : public MergeTestStruct<IntVector>
{
    explicit IntVectorMergeArgs(
        IntVector (*dataCreator1)(const unsigned int),
        IntVector (*dataCreator2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    : MergeTestStruct<IntVector>(
        TestType::MergeIntVector,
        [dataCreator1, dataCreator2, n1, n2]()
        {
            return initTestData3(dataCreator1, dataCreator2, n1, n2);
        })
    { }
};

class IntVectorMergeFixture : public MergeTestFixture<IntVector>
{
public:
    static IntVector f10i_imod7(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + ((i+1) % 7));
        }
        return IntVector(v);
    }

    static IntVector f10i_imod9(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + (i % 9));
        }
        return IntVector(v);
    }
};

TEST_P(IntVectorMergeFixture, IntVectorTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Merge
