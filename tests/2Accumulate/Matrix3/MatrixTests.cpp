#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

#define MATRIX_COUNT 150

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    MatrixAccumulateIntPrefix,
    MatrixAccumulateIntFixture,
    ::testing::Values(
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, SumOnly),
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, SumAndExtremes),
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, SumAndMean),
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, DoItAll)
    ));

INSTANTIATE_TEST_SUITE_P(
    MatrixAccumulateDoublePrefix,
    MatrixAccumulateDoubleFixture,
    ::testing::Values(
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, SumOnly),
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, SumAndExtremes),
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, SumAndMean),
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, DoItAll)
    ));

} // namespace tests::Accumulate
