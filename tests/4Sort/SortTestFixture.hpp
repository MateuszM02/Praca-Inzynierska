#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Sorter.hpp"

#include <random>

using namespace src::Algorithms;

namespace tests::Sort
{

template <typename DataType>
struct SortTestStruct : public BaseTestStruct<std::vector<DataType>>
{
protected:
    explicit SortTestStruct(const TestType testType,
        Callback<Sorter<DataType>>&& callback)
    : BaseTestStruct<std::vector<DataType>>(testType, std::move(callback))
    { }
};

// Klasa abstrakcyjna SortTestFixture, po ktorej dziedzicza klasy testowe metod sort
template <typename DataType>
class SortTestFixture : public BaseTestFixture<std::vector<DataType>>
{
protected:
    SortTestFixture() = default;
};

} // namespace tests::Sort
