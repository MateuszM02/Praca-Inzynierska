#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/CustomPairImpl.hpp"

using namespace src::Structures;

namespace tests::Sort
{

using Base = BaseTestStruct<std::vector<CopyableUIntPair>>;
using Parent = SortTestStruct<CopyableUIntPair>;

struct PointsSortArgs final : public Parent
{
    explicit PointsSortArgs(
        CopyableUIntPair (*dataCreator)(),
        const unsigned int n)
    : Parent(TestType::SortPoints,
        [dataCreator, n]()
        {
            std::vector<CopyableUIntPair> data =
                initTestData<std::vector<CopyableUIntPair>>(dataCreator, n);
            return std::make_shared<Sorter<CopyableUIntPair>>(std::move(data));
        })
    { }

    explicit PointsSortArgs(
        CopyableUIntPair (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::SortPoints,
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
        unsigned int arg1 = i;
        unsigned int arg2 = i;
        return CopyableUIntPair(std::move(arg1), std::move(arg2));
    }

    static CopyableUIntPair reverseSortedGenerator(const unsigned int i)
    {
        unsigned int arg1 = UINT32_MAX - i;
        unsigned int arg2 = UINT32_MAX - i;
        return CopyableUIntPair(std::move(arg1), std::move(arg2));
    }

    static CopyableUIntPair randomGenerator(const unsigned int seed)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<unsigned int> dis(seed, UINT32_MAX);

        unsigned int x = dis(gen);
        unsigned int y = dis(gen);
        return CopyableUIntPair(std::move(x), std::move(y));
    }
};

} // namespace tests::Sort
