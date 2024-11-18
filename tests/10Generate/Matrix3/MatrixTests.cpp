#include "MatrixTests.hpp"

namespace tests::Generate::Matrix3tests
{
template<template<typename> class MatrixType, typename InnerType>
requires Matrix3::IsSquareMatrix<InnerType>
void MatrixTests<MatrixType, InnerType>::createTest(
    const unsigned int n,
    const src::MethodType& methodType,
    const std::vector<MatrixType<InnerType>>& args)
{
    auto functor = Matrix3::MatrixFunctor<MatrixType, InnerType>(args[0]);
    runTest(functor, n, methodType);
}
} // namespace tests::Generate::Matrix3tests
