#pragma once

#include "../UniqueTestFixture.hpp"
#include "../../../src/Structures/CustomPairImpl.hpp"

#include <random>

namespace tests::Unique
{

using Base = BaseTestStruct<std::vector<CopyableUIntPair>>;
using Parent = UniqueTestStruct<CopyableUIntPair>;

struct UniquePointsArgs final : public Parent
{
    explicit UniquePointsArgs(
        CopyableUIntPair (*dataCreator)(const unsigned int),
        const unsigned int& n)
    : Parent(TestType::UniquePoints,
        [dataCreator, n]()
        {
            std::vector<CopyableUIntPair> inData =
                initTestData<std::vector<CopyableUIntPair>>(dataCreator, n);
            return std::make_shared<Uniquer<CopyableUIntPair>>(std::move(inData));
        })
    { }
};

class UniquePointsFixture : public UniqueTestFixture<CopyableUIntPair>
{
public:
    static CopyableUIntPair randomGeneratorOftenCopies(const unsigned int n)
    {
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, std::sqrt(n));

        const int value = dis(gen);
        const CopyableUIntPair p(value, value);
        return p;
    }

    static CopyableUIntPair randomGeneratorRareCopies(const unsigned int n)
    {
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, n);

        const int value = dis(gen);
        const CopyableUIntPair p(value, value);
        return p;
    }
};

} // namespace tests::Unique
