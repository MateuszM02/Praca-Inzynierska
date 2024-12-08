#include "MatrixFunctor.hpp"

namespace src::Generate::Matrix3
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

template<template<typename> class MatrixType, typename InnerType>
requires IsSquareMatrix<InnerType>
std::shared_ptr<Functor<MatrixType<InnerType>>>
MatrixFunctor<MatrixType, InnerType>::clone() const
{
    return std::make_shared<MatrixFunctor>(*this);
}

} // namespace src::Generate::Matrix3
