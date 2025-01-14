#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Sort
{

struct IntVectorSortArgs final : public SortTestStruct<CopyableIntVector>
{
    explicit IntVectorSortArgs(
        CopyableIntVector (*dataCreator)(const unsigned int),
        const unsigned int n)
    : SortTestStruct<CopyableIntVector>(
        TestType::SortIntVector,
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
    // wektory roznia sie juz na pierwszej pozycji
    static CopyableIntVector sortedFirstElementGenerator(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(i + n);
        }
        return CopyableIntVector(v);
    }

    // wektory roznia sie dopiero na ostatniej pozycji
    static CopyableIntVector sortedLastElementGenerator(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n-1; ++i)
        {
            v.emplace_back(i);
        }
        v.emplace_back(n);
        return CopyableIntVector(v);
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
        return CopyableIntVector(v);
    }
};

TEST_P(IntVectorSortFixture, IntVectorSortTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Sort
