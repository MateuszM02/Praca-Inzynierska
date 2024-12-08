#pragma once
#include "Matrix.hpp"

// Przyklad 3. Podnoszenie kwadratowej macierzy do potegi n-tej ---------------------------------------------

namespace src::Generate::Matrix3
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
} // namespace src::Generate::Matrix3
