#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/CustomPairImpl.hpp"

using namespace src::Structures;

namespace tests::Merge
{

using Base = BaseTestStruct<std::vector<CopyableUIntPair>>;
using Parent = MergeTestStruct<CopyableUIntPair>;

struct PointsMergeArgs final : public Parent
{
    explicit PointsMergeArgs(
        CopyableUIntPair (*dataCreator1)(const unsigned int),
        CopyableUIntPair (*dataCreator2)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::MergePoints,
        [dataCreator1, dataCreator2, n]()
        {
            return initTestData3(dataCreator1, dataCreator2, n);
        })
    { }
};

class PointsMergeFixture : public MergeTestFixture<CopyableUIntPair>
{
public:
    static CopyableUIntPair fmod3i3_mod7i64(const unsigned int i)
    {
        return CopyableUIntPair(3*i + (i % 3), 7*i % 64);
    }

    static CopyableUIntPair f3i_mod9i64(const unsigned int i)
    {
        return CopyableUIntPair(3*i, 9*i % 64);
    }
};

} // namespace tests::Merge
