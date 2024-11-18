#pragma once
#include "Matrix.hpp"

namespace src::Generate::Matrix3
{
// funktor do podnoszenia macierzy do danej potegi
template<template<typename> class MatrixType, typename InnerType>
requires IsSquareMatrix<InnerType>
class MatrixFunctor : public Functor<MatrixType<InnerType>>
{
public:
    MatrixFunctor(const MatrixType<InnerType>& m);
    MatrixType<InnerType> operator()() override;
private:
    const MatrixType<InnerType> originalMatrix;
    MatrixType<InnerType> currentMatrix;
};
} // namespace src::Generate::Matrix3
