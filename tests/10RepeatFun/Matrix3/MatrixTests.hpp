#pragma once

#include "../TestFixture.hpp"
#include "../../../src/10RepeatFun/Matrix3/MatrixFunctor.hpp"

namespace tests::RepeatFun::Matrix3tests
{
template<template<typename> class MatrixType, typename InnerType>
requires Matrix3::IsSquareMatrix<InnerType>
class MatrixTests : FunctorTestFixture<MatrixType<InnerType>>
{
public:
    void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<MatrixType<InnerType>>& args) override;
};
} // namespace tests::RepeatFun::Matrix3tests
