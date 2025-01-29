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
    static CopyableUIntPair sortedGenerator(const unsigned int i)
    {
        unsigned int arg1 = i;
        unsigned int arg2 = i;
        return CopyableUIntPair(std::move(arg1), std::move(arg2));
    }
};

} // namespace tests::NthElement
