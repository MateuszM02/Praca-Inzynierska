#pragma once

#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../MinMaxTestFixture.hpp"

using namespace src::Structures;

namespace tests::MinMax
{

struct VectorOfVectorsMinMaxArgs final : public MinMaxTestStruct<std::vector<IntVector>>
{
    explicit VectorOfVectorsMinMaxArgs(
        IntVector (*dataCreator)(const unsigned int),
        const unsigned int n)
    : MinMaxTestStruct<std::vector<IntVector>>(
        TestType::MinMaxVectorOfVectors,
        [dataCreator, n]()
        {
            std::vector<IntVector> data =
                BaseTestStruct::initTestData<std::vector<IntVector>>(dataCreator, n);
            return std::make_shared<MinMaxFinder<std::vector<IntVector>>>(std::move(data));
        })
    { }
};

class VectorOfVectorsMinMaxFixture : public MinMaxTestFixture<std::vector<IntVector>>
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

TEST_P(VectorOfVectorsMinMaxFixture, VectorOfVectorsMinMaxTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::MinMax
