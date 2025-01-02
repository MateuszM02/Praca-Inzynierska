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
        const std::shared_ptr<Sorter<DataType>>& f)
    : BaseTestStruct<Sorter<DataType>>(testType, f)
    { }
};

// Klasa abstrakcyjna SortTestFixture, po ktorej dziedzicza klasy testowe metod sort
template <typename DataType>
class SortTestFixture : public BaseTestFixture<std::vector<DataType>, Sorter<DataType>>
{
};

} // namespace tests::Sort
