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
protected:
    explicit SortTestStruct(const TestType testType,
        std::shared_ptr<Sorter<DataType>>&& f)
    : BaseTestStruct<Sorter<DataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna SortTestFixture, po ktorej dziedzicza klasy testowe metod sort
template <typename DataType>
class SortTestFixture : public BaseTestFixture<std::vector<DataType>, Sorter<DataType>>
{
protected:
    SortTestFixture() = default;
};

} // namespace tests::Sort
