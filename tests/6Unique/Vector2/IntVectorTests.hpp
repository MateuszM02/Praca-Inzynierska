#pragma once

#include "../UniqueTestFixture.hpp"
#include "../../../src/Structures/IntVectorImpl.hpp"

using namespace src::Structures;

namespace tests::Unique
{

using Base = BaseTestStruct<std::vector<std::vector<int>>>;
using Parent = UniqueTestStruct<std::vector<int>>;

struct UniqueIntVectorArgs final : public Parent
{
    explicit UniqueIntVectorArgs(
        std::vector<int> (*dataCreator)(const unsigned int),
        const TestPair& info)
    : Parent(TestType::UniqueIntVector,
        [dataCreator, info]()
        {
            std::vector<std::vector<int>> inData =
                initTestData<std::vector<std::vector<int>>>(dataCreator, info);
            return std::make_shared<Uniquer<std::vector<int>>>(std::move(inData));
        })
    { }
};

class UniqueIntVectorFixture : public UniqueTestFixture<std::vector<int>>
{
public:
    static std::vector<int> noCopiesGenerator(const unsigned int vectorSize)
    {
        static unsigned int instance = 0;
        std::vector<int> vec;
        vec.reserve(vectorSize);
        for (unsigned int i = 0; i < vectorSize; i++)
        {
            vec.emplace_back(i + instance);
        }
        ++instance;
        return vec;
    }

    static std::vector<int> onlyCopiesGenerator(const unsigned int vectorSize)
    {
        std::vector<int> vec;
        vec.reserve(vectorSize);
        for (unsigned int i = 0; i < vectorSize; i++)
        {
            vec.emplace_back(i);
        }
        return vec;
    }
};

} // namespace tests::Unique
