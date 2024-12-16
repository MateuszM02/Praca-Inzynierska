#pragma once

#include "../Structures/Matrix.hpp"
#include "../Structures/RandomString.hpp"

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
using GeneratorPtr = std::shared_ptr<Generator<GeneratedDataType, StateDataType>>;

using namespace src::Structures;

namespace src::Algorithms
{

class GeneratorImpl final
{
public:
    GeneratorImpl() = delete;

    template <Addable Number>
    using NumberPair = std::pair<Number, Number>;

    template <Addable Number>
    static GeneratorPtr<Number, NumberPair<Number>>
    createFibonacciGenerator(
        const unsigned int n,
        const NumberPair<Number>& initialPair,
        std::vector<Number> expectedResult) 
    {
        GeneratorData<Number, NumberPair<Number>> data(n, initialPair, std::move(expectedResult),
            [](const NumberPair<Number>& initialState, NumberPair<Number>& currentState)
            {
                currentState = std::make_pair(currentState.second, currentState.first + currentState.second);
                return currentState.first;
            });
        return std::make_shared<Generator<Number, NumberPair<Number>>>(std::move(data));
    }

    static GeneratorPtr<std::string, RandomString>
    createRandomStringGenerator(
        const unsigned int n,
        const unsigned int length) 
    {
        RandomString rs(length);
        GeneratorData<std::string, RandomString> data(n, rs, {},
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
        return std::make_shared<Generator<std::string, RandomString>>(std::move(data));
    }

    template <Multiplicable Number>
    static GeneratorPtr<Matrix<Number>> createMatrixGenerator(
        const unsigned int n,
        const Matrix<Number>& initialMatrix,
        std::vector<Matrix<Number>> expectedResult) 
    {
        GeneratorData<Matrix<Number>> data(n, initialMatrix, std::move(expectedResult),
            [](const Matrix<Number>& initialState, Matrix<Number>& currentState) 
            {
                currentState *= initialState;
                return currentState;
            });
        return std::make_shared<Generator<Matrix<Number>>>(std::move(data));
    }
};

} // namespace src::Algorithms
