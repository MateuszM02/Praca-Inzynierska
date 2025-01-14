#pragma once

#include "../../../src/Structures/IntVectorImpl.hpp"
#include "../MinMaxTestFixture.hpp"

using namespace src::Structures;

namespace tests::MinMax
{

struct VectorSetMinMaxArgs final : public MinMaxTestStruct<
    std::set<CopyableIntVector>, CopyablePair<CopyableIntVector>>
{
    explicit VectorSetMinMaxArgs(
        CopyableIntVector (*dataCreator)(const unsigned int),
        const unsigned int n)
    : MinMaxTestStruct<std::set<CopyableIntVector>, CopyablePair<CopyableIntVector>>(
        TestType::MinMaxVectorSet,
        [dataCreator, n]()
        {
            std::set<CopyableIntVector> data =
                BaseTestStruct::initTestData<std::set<CopyableIntVector>>(dataCreator, n);
            return std::make_shared<MinMaxFinder<
                std::set<CopyableIntVector>>>(std::move(data));
        })
    { }
};

class VectorSetMinMaxFixture : public MinMaxTestFixture<CopyableIntVector>
{
public:
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

TEST_P(VectorSetMinMaxFixture, VectorSetMinMaxTest)
{
    VerifyTestCustomFor1(GetParam());
}

} // namespace tests::MinMax
