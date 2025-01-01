#pragma once

#include "../Algorithms/Generator.hpp"
#include "../Concepts/DataTypeConcepts.hpp"

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
    using State = std::pair<Number, Number>;

    template <Addable Number>
    using FibonacciGenerator = Generator<Number, State<Number>>;

    template <Addable Number>
    static Number creator(const State<Number>& initialState, State<Number>& currentState)
    {
        currentState = std::make_pair(currentState.second, currentState.first + currentState.second);
        return currentState.first;
    }

    template <Addable Number>
    static std::shared_ptr<FibonacciGenerator<Number>>
    createGenerator(const unsigned int n, const State<Number>& initialPair) 
    {
        const FibonacciGenerator<Number> generator(n, initialPair, creator);
        return std::make_shared<FibonacciGenerator<Number>>(std::move(generator));
    }
};

} // namespace src::Structures
