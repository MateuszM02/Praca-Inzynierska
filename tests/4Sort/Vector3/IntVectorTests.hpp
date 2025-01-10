#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Sort
{

struct IntVectorSortArgs final : public SortTestStruct<IntVector>
{
    explicit IntVectorSortArgs(
        IntVector (*f)(const unsigned int),
        const unsigned int n)
    : SortTestStruct<IntVector>(
        TestType::SortIntVector,
        std::make_shared<Sorter<IntVector>>(initTestData<std::vector<IntVector>>(f, n)))
    { }
};

class IntVectorSortFixture : public SortTestFixture<IntVector>
{
public:
    // wektory roznia sie juz na pierwszej pozycji
    static IntVector sortedFirstElementGenerator(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(i + n);
        }
        return IntVector(v);
    }

    // wektory roznia sie dopiero na ostatniej pozycji
    static IntVector sortedLastElementGenerator(const unsigned int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n-1; ++i)
        {
            v.emplace_back(i);
        }
        v.emplace_back(n);
        return IntVector(v);
    }

    // wektory losowe moga sie roznic na dowolnej pozycji
    static IntVector randomGenerator(const unsigned int n)
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
        return IntVector(v);
    }
};

TEST_P(IntVectorSortFixture, IntVectorSortTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Sort
