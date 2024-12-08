#pragma once
#include "Matrix.hpp"

// Przyklad 3. Podnoszenie kwadratowej macierzy do potegi n-tej ---------------------------------------------

namespace src::Generate::Matrix3
{
template<template<typename> class MatrixType, typename InnerType>
requires IsSquareMatrix<InnerType>
class MatrixFunctor : public Functor<MatrixType<InnerType>>
{
public:
    MatrixFunctor(const MatrixType<InnerType>& m);
    MatrixType<InnerType> operator()() override;
    std::shared_ptr<Functor<MatrixType<InnerType>>> clone() const override;
private:
    const MatrixType<InnerType> originalMatrix;
    MatrixType<InnerType> currentMatrix;
};
} // namespace src::Generate::Matrix3
