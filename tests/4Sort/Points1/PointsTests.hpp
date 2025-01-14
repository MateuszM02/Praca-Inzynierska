#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/CustomPairImpl.hpp"

using namespace src::Structures;

namespace tests::Sort
{

struct PointsSortArgs final : public SortTestStruct<CopyableUIntPair>
{
    explicit PointsSortArgs(CopyableUIntPair (*dataCreator)(), const unsigned int n)
    : SortTestStruct<CopyableUIntPair>(
        TestType::SortPoints,
        [dataCreator, n]()
        {
            std::vector<CopyableUIntPair> data =
                initTestData<std::vector<CopyableUIntPair>>(dataCreator, n);
            return std::make_shared<Sorter<CopyableUIntPair>>(std::move(data));
        })
    { }

    PointsSortArgs(CopyableUIntPair (*dataCreator)(const unsigned int), const unsigned int n)
    : SortTestStruct<CopyableUIntPair>(
        TestType::SortPoints,
        [dataCreator, n]()
        {
            std::vector<CopyableUIntPair> data =
                initTestData<std::vector<CopyableUIntPair>>(dataCreator, n);
            return std::make_shared<Sorter<CopyableUIntPair>>(std::move(data));
        })
    { }
};

class PointsSortFixture : public SortTestFixture<CopyableUIntPair>
{
public:
    static CopyableUIntPair sortedGenerator(const unsigned int i)
    {
        return CopyableUIntPair(i, i);
    }

    static CopyableUIntPair reverseSortedGenerator(const unsigned int i)
    {
        return CopyableUIntPair(UINT32_MAX - i, UINT32_MAX - i);
    }

    static CopyableUIntPair randomGenerator()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<unsigned int> dis(0, UINT32_MAX);

        unsigned int x = dis(gen);
        unsigned int y = dis(gen);
        return CopyableUIntPair(x, y);
    }
};

TEST_P(PointsSortFixture, pointsSortTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Sort
