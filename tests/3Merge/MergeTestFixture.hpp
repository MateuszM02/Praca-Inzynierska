#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Merger.hpp"
#include "../../src/Algorithms/MergerImpl.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;

namespace tests::Merge
{

template <typename DataType>
struct MergeTestStruct : public BaseTestStruct<Merger<DataType>>
{
public:
    MergeTestStruct(
        const std::string& path,
        std::shared_ptr<Merger<DataType>> f)
    : BaseTestStruct<Merger<DataType>>(path, std::move(f))
    { }
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <typename DataType>
class MergeTestFixture : public BaseTestFixture<Merger<DataType>>
{
public:
    static MergerData<DataType> initTestData(
        Mergeable<DataType> (*fun1)(const unsigned int),
        Mergeable<DataType> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    {
        std::vector<Mergeable<DataType>> v1;
        std::vector<Mergeable<DataType>> v2;
        std::vector<Mergeable<DataType>> expectedResult;
        v1.reserve(n1);
        v2.reserve(n2);
        expectedResult.reserve(n1 + n2);

        for (unsigned int i = 1; i <= n1; ++i)
        {
            v1.emplace_back(fun1(i));
        }
        for (unsigned int i = 1; i <= n2; ++i)
        {
            v2.emplace_back(fun2(i));
        }

        unsigned int x1 = 1;
        unsigned int x2 = 1;
        Mergeable<DataType> p1 = fun1(x1);
        Mergeable<DataType> p2 = fun2(x2);

        while (x1 <= n1 && x2 <= n2)
        {
            if (p1 < p2)
            {
                expectedResult.emplace_back(std::move(p1));
                p1 = fun1(++x1);
            }
            else
            {
                expectedResult.emplace_back(std::move(p2));
                p2 = fun2(++x2);
            }
        }
        while (x1 <= n1)
        {
            expectedResult.emplace_back(std::move(p1));
            p1 = fun1(++x1);
        }
        while (x2 <= n2)
        {
            expectedResult.emplace_back(std::move(p2));
            p2 = fun2(++x2);
        }

        return MergerData<DataType>(std::move(v1), std::move(v2), std::move(expectedResult));
    }
};

} // namespace tests::Merge
