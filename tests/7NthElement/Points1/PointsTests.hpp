#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/CustomPairImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

using Container = std::vector<CopyableUIntPair>;
using Base = BaseTestStruct<Container>;
using Parent = NthElementTestStruct<Container>;

struct PointsNthElementArgs final : public Parent
{
    explicit PointsNthElementArgs(
        CopyableUIntPair (*dataCreator)(const unsigned int),
        const TestPair& info)
    : Parent(TestType::NthElementPoints,
        [dataCreator, info]()
        {
            return initTestData7(dataCreator, info);
        })
    { }
};

class PointsNthElementFixture : public NthElementTestFixture<Container>
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

} // namespace tests::NthElement
