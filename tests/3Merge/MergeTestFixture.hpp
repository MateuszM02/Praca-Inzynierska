#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Merger.hpp"

using namespace src::Algorithms;

namespace tests::Merge
{

template <typename DataType>
struct MergeTestStruct : public BaseTestStruct<std::vector<DataWrapper<DataType>>, Merger<DataType>>
{
public:
    MergeTestStruct(
        const TestType testType,
        std::shared_ptr<Merger<DataType>> f)
    : BaseTestStruct<std::vector<DataWrapper<DataType>>, Merger<DataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <typename DataType>
class MergeTestFixture : public BaseTestFixture<std::vector<DataWrapper<DataType>>, Merger<DataType>>
{
public:
    static MergerData<DataType> initTestData(
        DataWrapper<DataType> (*fun1)(const unsigned int),
        DataWrapper<DataType> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    {
        std::vector<DataWrapper<DataType>> v1;
        std::vector<DataWrapper<DataType>> v2;
        v1.reserve(n1);
        v2.reserve(n2);

        for (unsigned int i = 1; i <= n1; ++i)
        {
            v1.emplace_back(std::move(fun1(i)));
        }
        for (unsigned int i = 1; i <= n2; ++i)
        {
            v2.emplace_back(std::move(fun2(i)));
        }
        return MergerData<DataType>(std::move(v1), std::move(v2));
    }
};

} // namespace tests::Merge
