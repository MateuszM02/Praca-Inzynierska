#pragma once

#include "../TransformTestFixture.hpp"

#include <map>
#include <random>

namespace tests::Transform
{

using InType = std::vector<unsigned int>;
using ReturnType = std::map<unsigned int, unsigned int>;
using Base = BaseTestStruct<std::vector<ReturnType>>;
using Parent = TransformTestStruct<InType, ReturnType>;

struct VectorToMapTransformArgs final : public Parent
{
    explicit VectorToMapTransformArgs(
        InType (*dataCreator)(const unsigned int),
        const TestPair& info)
    : Parent(TestType::TransformVectorToMap,
        [dataCreator, info]()
        {
            std::vector<InType> inData =
                initTestData<std::vector<InType>>(dataCreator, info);
            return std::make_shared<Transformer<InType, ReturnType>>(
                std::move(inData),
                &transformer);
        })
    { }

    static ReturnType transformer(const InType& vec)
    {
        ReturnType occurenceMap;
        for (const unsigned int value : vec)
        {
            occurenceMap[value]++;
        }
        return occurenceMap;
    }
};

class VectorToMapTransformFixture : public TransformTestFixture<ReturnType>
{
public:
    static InType randomGeneratorOftenCopies(const unsigned int n)
    {
        InType vec;
        vec.reserve(n);
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, std::sqrt(n));

        for (unsigned int i = 0; i < n; i++)
        {
            vec.emplace_back(dis(gen));
        }
        return vec;
    }

    static InType randomGeneratorRareCopies(const unsigned int n)
    {
        InType vec;
        vec.reserve(n);
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, n);

        for (unsigned int i = 0; i < n; i++)
        {
            vec.emplace_back(dis(gen));
        }
        return vec;
    }
};

TEST_P(VectorToMapTransformFixture, VectorToMapTransformTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Transform
