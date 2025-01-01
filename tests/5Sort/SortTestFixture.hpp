#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Sorter.hpp"

#include <random>

using namespace src::Algorithms;

namespace tests::Sort
{

template <typename DataType>
struct SortTestStruct : public BaseTestStruct<Sorter<DataType>>
{
public:
    SortTestStruct(
        const TestType testType,
        std::shared_ptr<Sorter<DataType>> f)
    : BaseTestStruct<Sorter<DataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna SortTestFixture, po ktorej dziedzicza klasy testowe metod sort
template <typename DataType>
class SortTestFixture : public BaseTestFixture<std::vector<DataType>, Sorter<DataType>>
{
public:
    static std::vector<DataType> initTestData(
        DataType (*f)(const unsigned int),
        const unsigned int n)
    {
        std::vector<DataType> v;
        v.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v.emplace_back(std::move(f(i)));
        }
        return v;
    }
};

} // namespace tests::Sort
