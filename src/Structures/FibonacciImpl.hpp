#pragma once

#include "../Algorithms/10Generate/Generator.hpp"
#include "../Concepts/DataTypeConcepts.hpp"

#include <memory>

using namespace src::Algorithms;
using namespace src::Concepts;

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie std::pair<Number, Number>
class FibonacciImpl final
{
public:
    FibonacciImpl() = delete;

    template <Addable Number>
    using NumberPair = std::pair<Number, Number>;

    template <Addable Number>
    using GeneratorPtr = std::shared_ptr<Generator<Number, NumberPair<Number>>>;

    template <Addable Number>
    static GeneratorPtr<Number>
    createGenerator(
        const unsigned int n,
        const NumberPair<Number>& initialPair) 
    {
        GeneratorData<Number, NumberPair<Number>> data(n, initialPair,
            [](const NumberPair<Number>& initialState, NumberPair<Number>& currentState)
            {
                currentState = std::make_pair(currentState.second, currentState.first + currentState.second);
                return currentState.first;
            });
        return std::make_shared<Generator<Number, NumberPair<Number>>>(std::move(data));
    }
};

} // namespace src::Structures
