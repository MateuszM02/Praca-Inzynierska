#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Merger.hpp"

using namespace src::Algorithms;

namespace tests::Merge
{

template <typename DataType>
struct MergeTestStruct : public BaseTestStruct<std::vector<DataType>>
{
protected:
    explicit MergeTestStruct(const TestType testType,
        Callback<Merger<DataType>>&& callback)
    : BaseTestStruct<std::vector<DataType>>(testType, std::move(callback))
    { }

    static std::shared_ptr<Merger<DataType>> initTestData3(
        DataType (*dataCreator1)(const unsigned int),
        DataType (*dataCreator2)(const unsigned int),
        const unsigned int n)
    {
        std::vector<DataType> v1;
        std::vector<DataType> v2;
        v1.reserve(n);
        v2.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v1.emplace_back(dataCreator1(i));
        }
        for (unsigned int i = 1; i <= n; ++i)
        {
            v2.emplace_back(dataCreator2(i));
        }
        MergerData<DataType> data(std::move(v1), std::move(v2));
        return std::make_shared<Merger<DataType>>(std::move(data));
    }
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <typename DataType>
class MergeTestFixture : public BaseTestFixture<std::vector<DataType>>
{
protected:
    MergeTestFixture() = default;
};

} // namespace tests::Merge
