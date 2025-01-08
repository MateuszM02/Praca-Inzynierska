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
        std::shared_ptr<Merger<DataType>>&& f)
    : BaseTestStruct<std::vector<DataType>>(testType, std::move(f))
    { }

    static MergerData<DataType> initTestData3(
        DataType (*fun1)(const unsigned int),
        DataType (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    {
        std::vector<DataType> v1;
        std::vector<DataType> v2;
        v1.reserve(n1);
        v2.reserve(n2);

        for (unsigned int i = 1; i <= n1; ++i)
        {
            v1.emplace_back(fun1(i));
        }
        for (unsigned int i = 1; i <= n2; ++i)
        {
            v2.emplace_back(fun2(i));
        }
        return MergerData<DataType>(v1, v2);
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
