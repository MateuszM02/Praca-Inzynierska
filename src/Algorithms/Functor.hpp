#pragma once
#include "Concepts.hpp"
#include "../MethodType.hpp"

#include <algorithm> // std::generate
#include <chrono> // mierzenie czasu wykonania testu
#include <iostream>
#include <functional>
#include <vector>

#include <boost/range/algorithm/generate.hpp> // boost::range::generate

namespace src::Algorithms
{

// klasa przechowujaca stan obiektu modyfikowany operatorem()
// podczas wywolywania std::generate/boost::range::generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
requires std::is_copy_assignable_v<GeneratedDataType> &&
         std::is_copy_assignable_v<StateDataType>
struct Callable final
{
    Callable(const StateDataType& state,
        std::function<GeneratedDataType(const StateDataType&, StateDataType&)> g)
    : initialState{state}
    , currentState{state}
    , generator{std::move(g)}
    { }

    GeneratedDataType operator()()
    {
        return generator(initialState, currentState);
    }

    void reset()
    {
        currentState = initialState;
    }

    const StateDataType initialState;
    StateDataType currentState;

private:
    std::function<GeneratedDataType(const StateDataType&, StateDataType&)> generator;
};

// Klasa abstrakcyjna Functor, po ktorej dziedzicza klasy funktorowe
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
class Functor final
{
public:
    Functor(const Callable<GeneratedDataType, StateDataType>& callable)
    : state{callable}
    { }

    std::vector<GeneratedDataType> callFunctor(
        const unsigned int n,
        const MethodType& methodType,
        std::ostream& os)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime(&generateSTL, "STL", n, os);
            case MethodType::Boost:
                return measureExecutionTime(&generateBoost, "Boost", n, os);
            case MethodType::Simple:
                return measureExecutionTime(&generateSimple, "Simple", n, os);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<GeneratedDataType> measureExecutionTime(
        std::vector<GeneratedDataType>(Functor::*memberFunction)(const unsigned int),
        const std::string& methodName,
        const unsigned int n,
        std::ostream& os)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<GeneratedDataType> result = (this->*memberFunction)(n);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        state.reset();
        return result;
    }

    std::vector<GeneratedDataType> generateSTL(const unsigned int n)
    {
        std::vector<GeneratedDataType> sequence(n);
        std::generate(sequence.begin(), sequence.end(), [this]() { return this->state(); });
        return sequence;
    }

    std::vector<GeneratedDataType> generateBoost(const unsigned int n)
    {
        std::vector<GeneratedDataType> sequence(n);
        boost::range::generate(sequence, [this]() { return this->state(); });
        return sequence;
    }

    std::vector<GeneratedDataType> generateSimple(const unsigned int n)
    {
        std::vector<GeneratedDataType> sequence(n);
        for (GeneratedDataType& element : sequence)
        {
            element = this->state();
        }
        return sequence;
    }

    Callable<GeneratedDataType, StateDataType> state;
};

} // namespace src::Algorithms
