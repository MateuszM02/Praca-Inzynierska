#pragma once

#include "../TestFixture.hpp"
#include "../../../src/10Generate/Matrix3/MatrixFunctor.hpp"

namespace tests::Generate::Matrix3tests
{
template<template<typename> class MatrixType, typename InnerType>
requires Matrix3::IsSquareMatrix<InnerType>
class MatrixTests : GenerateTestFixture<MatrixType<InnerType>>
{
public:
    void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<MatrixType<InnerType>>& args) override;
};
} // namespace tests::Generate::Matrix3tests
