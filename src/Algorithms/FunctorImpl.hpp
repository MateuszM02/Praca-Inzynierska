#pragma once

#include "../Structures/Matrix.hpp"
#include "../Structures/RandomString.hpp"

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
using FunctorPtr = std::shared_ptr<Functor<GeneratedDataType, StateDataType>>;

using namespace src::Structures;

namespace src::Algorithms
{

class FunctorImpl
{
public:
    FunctorImpl() = delete;

    template <Addable Number>
    using NumberPair = std::pair<Number, Number>;

    template <Addable Number>
    static FunctorPtr<Number, NumberPair<Number>>
    createFibonacciFunctor(const NumberPair<Number>& initialPair) 
    {
        Callable<Number, NumberPair<Number>> callable(initialPair,
            [](const NumberPair<Number>& initialState, NumberPair<Number>& currentState)
            {
                currentState = std::make_pair(currentState.second, currentState.first + currentState.second);
                return currentState.first;
            });
        return std::make_shared<Functor<Number, NumberPair<Number>>>(callable);
    }

    static FunctorPtr<std::string, RandomString>
    createRandomStringFunctor(const unsigned int length) 
    {
        RandomString rs(length);
        Callable<std::string, RandomString> callable(rs, 
            [](const RandomString& initialState, RandomString& currentState)
            {
                std::string randomString;
                randomString.reserve(currentState.length);
                for (unsigned int i = 0; i < currentState.length; ++i)
                {
                    randomString += currentState.distribution(currentState.randomGenerator); 
                }
                return randomString;
            });
        return std::make_shared<Functor<std::string, RandomString>>(callable);
    }

    template <Multiplicable Number>
    static FunctorPtr<Matrix<Number>> createMatrixFunctor(const Matrix<Number>& initialMatrix) 
    {
        Callable<Matrix<Number>> callable(initialMatrix, 
            [](const Matrix<Number>& initialState, Matrix<Number>& currentState) 
            {
                currentState *= initialState;
                return currentState;
            });
        return std::make_shared<Functor<Matrix<Number>>>(callable);
    }
};

} // namespace src::Algorithms
