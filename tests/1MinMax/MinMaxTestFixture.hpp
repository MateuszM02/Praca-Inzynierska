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
        std::shared_ptr<MinMaxFinder<Container>>&& f)
    : BaseTestStruct<Container>(testType, std::move(f))
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
