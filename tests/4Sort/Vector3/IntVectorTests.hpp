#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Sort
{

using Base = BaseTestStruct<std::vector<CopyableIntVector>>;
using Parent = SortTestStruct<CopyableIntVector>;

struct IntVectorSortArgs final : public Parent
{
    explicit IntVectorSortArgs(
        CopyableIntVector (*dataCreator)(const unsigned int),
        const unsigned int n)
    : Parent(TestType::SortIntVector,
        [dataCreator, n]()
        {
            std::vector<CopyableIntVector> data =
                initTestData<std::vector<CopyableIntVector>>(dataCreator, n);
            return std::make_shared<Sorter<CopyableIntVector>>(std::move(data));
        })
    { }
};

class IntVectorSortFixture : public SortTestFixture<CopyableIntVector>
{
public:
    static CopyableIntVector sortedGenerator(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(i);
        }
        return CopyableIntVector(std::move(v));
    }

    static CopyableIntVector reverseSortedGenerator(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(UINT32_MAX - i);
        }
        return CopyableIntVector(std::move(v));
    }

    // wektory losowe moga sie roznic na dowolnej pozycji
    static CopyableIntVector randomGenerator(const unsigned int n)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<unsigned int> dis(0, UINT32_MAX);

        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(dis(gen));
        }
        return CopyableIntVector(std::move(v));
    }
};

} // namespace tests::Sort
