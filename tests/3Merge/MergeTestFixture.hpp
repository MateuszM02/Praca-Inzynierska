#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Merger.hpp"

using namespace src::Algorithms;

namespace tests::Merge
{

template <typename DataType>
struct MergeTestStruct : public BaseTestStruct<Merger<DataType>>
{
public:
    MergeTestStruct(
        const TestType testType,
        const std::shared_ptr<Merger<DataType>>& f)
    : BaseTestStruct<Merger<DataType>>(testType, f)
    { }
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <typename DataType>
class MergeTestFixture : public BaseTestFixture<std::vector<DataType>, Merger<DataType>>
{
public:
    static MergerData<DataType> initTestData(
        DataType (*fun1)(const unsigned int)&,
        DataType (*fun2)(const unsigned int)&,
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

} // namespace tests::Merge
