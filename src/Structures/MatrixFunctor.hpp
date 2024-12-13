#pragma once
#include "Matrix.hpp"

using namespace src::Algorithms;

namespace src::Structures
{
template <class Number>
requires std::is_arithmetic_v<Number>
class MatrixFunctor : public Functor<Matrix<Number>>
{
public:
    MatrixFunctor(const Matrix<Number>& m);
    Matrix<Number> operator()() override;
    std::shared_ptr<Functor<Matrix<Number>>> clone() const override;
private:
    const Matrix<Number> originalMatrix;
    Matrix<Number> currentMatrix;
};
} // namespace src::Structures
