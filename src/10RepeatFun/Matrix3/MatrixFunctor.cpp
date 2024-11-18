#include "MatrixFunctor.hpp"

namespace src::RepeatFun::Matrix3
{
template<template<typename> class MatrixType, typename InnerType>
requires IsSquareMatrix<InnerType>
MatrixFunctor<MatrixType, InnerType>::MatrixFunctor(const MatrixType<InnerType>& m) 
: originalMatrix(m) 
, currentMatrix(m)
{ }

template<template<typename> class MatrixType, typename InnerType>
requires IsSquareMatrix<InnerType>
MatrixType<InnerType> 
MatrixFunctor<MatrixType, InnerType>::operator()()
{
    currentMatrix *= originalMatrix;
    return currentMatrix;
}
} // namespace src::RepeatFun::Matrix3
