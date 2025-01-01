#pragma once

#include "../Algorithms/Generator.hpp"
#include "Matrix.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie Matrix
class MatrixImpl final
{
public:
    MatrixImpl() = delete;

    template <Multiplicable Number>
    static Matrix<Number> creator(const Matrix<Number>& initialState, Matrix<Number>& currentState)
    {
        currentState *= initialState;
        return currentState;
    }

    template <Multiplicable Number>
    static std::shared_ptr<Generator<Matrix<Number>>>
    createGenerator(const unsigned int n, const Matrix<Number>& initialMatrix) 
    {
        const Generator<Matrix<Number>> generator(n, initialMatrix, creator);
        return std::make_shared<Generator<Matrix<Number>>>(std::move(generator));
    }
};

} // namespace src::Structures
