#pragma once

#include "../../src/Algorithms/MinMaxFinder.hpp"
#include "../BaseTestFixture.hpp"

#include <random>

using namespace src::Algorithms;

namespace tests::MinMax
{
template <typename Container>
struct MinMaxTestStruct : public BaseTestStruct<Container>
{
protected:
    explicit MinMaxTestStruct(const TestType testType,
        Callback<MinMaxFinder<Container>>&& callback)
    : BaseTestStruct<Container>(testType, std::move(callback))
    { }
};

// Klasa abstrakcyjna MinMaxTestFixture, po ktorej dziedzicza klasy testowe metod MinMax
template <typename Container>
class MinMaxTestFixture : public BaseTestFixture<Container>
{
protected:
    MinMaxTestFixture() = default;
};

} // namespace tests::MinMax
