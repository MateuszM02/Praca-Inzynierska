#pragma once

#include "../TransformTestFixture.hpp"

#include <map>
#include <random>

namespace tests::Transform
{

using InType2 = std::vector<unsigned int>;
using ReturnType2 = std::map<unsigned int, unsigned int>;
using Base2 = BaseTestStruct<std::vector<ReturnType2>>;
using Parent2 = TransformTestStruct<InType2, ReturnType2>;

struct VectorToMapTransformArgs final : public Parent2
{
    explicit VectorToMapTransformArgs(
        InType2 (*dataCreator)(const unsigned int),
        const TestPair& info)
    : Parent2(TestType::TransformVectorToMap,
        [dataCreator, info]()
        {
            std::vector<InType2> inData =
                initTestData<std::vector<InType2>>(dataCreator, info);
            return std::make_shared<Transformer<InType2, ReturnType2>>(
                std::move(inData),
                &transformer);
        })
    { }

    static ReturnType2 transformer(const InType2& vec)
    {
        ReturnType2 occurenceMap;
        for (const unsigned int value : vec)
        {
            occurenceMap[value]++;
        }
        return occurenceMap;
    }
};

class VectorToMapTransformFixture : public TransformTestFixture<ReturnType2>
{
public:
    static InType2 randomGeneratorOftenCopies(const unsigned int n)
    {
        InType2 vec;
        vec.reserve(n);
        static std::mt19937 gen(0);
        static std::uniform_int_distribution<> dis(1, std::sqrt(n));

        for (unsigned int i = 0; i < n; i++)
        {
            vec.emplace_back(dis(gen));
        }
        return vec;
    }

    static InType2 randomGeneratorRareCopies(const unsigned int n)
    {
        InType2 vec;
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

} // namespace tests::Transform
