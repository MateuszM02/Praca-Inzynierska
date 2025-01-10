#pragma once

#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../MinMaxTestFixture.hpp"

using namespace src::Structures;

namespace tests::MinMax
{

struct VectorSetMinMaxArgs final : public MinMaxTestStruct<std::set<IntVector>>
{
    explicit VectorSetMinMaxArgs(
        IntVector (*f)(const unsigned int),
        const unsigned int n)
    : MinMaxTestStruct<std::set<IntVector>>(
        TestType::MinMaxVectorSet,
        std::make_shared<MinMaxFinder<std::set<IntVector>>>(
            initTestData<std::set<IntVector>>(f, n)))
    { }
};

class VectorSetMinMaxFixture : public MinMaxTestFixture<std::set<IntVector>>
{
public:
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

TEST_P(VectorSetMinMaxFixture, VectorSetMinMaxTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::MinMax
