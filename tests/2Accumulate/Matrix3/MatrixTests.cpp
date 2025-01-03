#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

#define MATRIX_COUNT 150

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    MatrixAccumulateIntPrefix,
    MatrixAccumulateIntFixture,
    ::testing::Values(
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, AccType::SumOnly),
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, AccType::SumAndExtremes),
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, AccType::SumAndMean),
        MatrixAccumulateArgs<int>(Examples::randomIntMatrix, MATRIX_COUNT, AccType::DoItAll)
    ));

INSTANTIATE_TEST_SUITE_P(
    MatrixAccumulateDoublePrefix,
    MatrixAccumulateDoubleFixture,
    ::testing::Values(
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::SumOnly),
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::SumAndExtremes),
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::SumAndMean),
        MatrixAccumulateArgs<double>(Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::DoItAll)
    ));

} // namespace tests::Accumulate
