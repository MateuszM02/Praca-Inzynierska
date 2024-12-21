#pragma once

#include "../Algorithms/10Generate/Generator.hpp"
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
    using GeneratorPtr = std::shared_ptr<Generator<Matrix<Number>, Matrix<Number>>>;

    template <Multiplicable Number>
    static GeneratorPtr<Number> createGenerator(
        const unsigned int n,
        const Matrix<Number>& initialMatrix) 
    {
        GeneratorData<Matrix<Number>> data(n, initialMatrix,
            [](const Matrix<Number>& initialState, Matrix<Number>& currentState) 
            {
                currentState *= initialState;
                return currentState;
            });
        return std::make_shared<Generator<Matrix<Number>>>(std::move(data));
    }
};

} // namespace src::Structures
