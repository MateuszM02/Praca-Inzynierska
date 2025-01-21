#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Uniquer.hpp"

using namespace src::Algorithms;

namespace tests::Unique
{

template <typename DataType>
struct UniqueTestStruct : public BaseTestStruct<std::vector<DataType>>
{
protected:
    explicit UniqueTestStruct(const TestType testType,
        Callback<Uniquer<DataType>>&& callback)
    : BaseTestStruct<std::vector<DataType>>(testType, std::move(callback))
    { }
};

// Klasa abstrakcyjna UniqueTestFixture, po ktorej dziedzicza klasy testowe metod Uniquer
template <typename DataType>
class UniqueTestFixture : public BaseTestFixture<std::vector<DataType>>
{
protected:
    UniqueTestFixture() = default;
};

} // namespace tests::Unique
