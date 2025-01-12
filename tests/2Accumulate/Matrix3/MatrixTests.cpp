#include "MatrixTests.hpp"
#include "../../ExampleMatrixes.hpp"

#define MATRIX_COUNT 150

namespace tests::Accumulate
{

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    MatrixAccumulateIntFixture,
    ::testing::Values(
        std::make_shared<MatrixAccumulateArgs<int>>(
            Examples::randomIntMatrix, MATRIX_COUNT, AccType::SumOnly),
        std::make_shared<MatrixAccumulateArgs<int>>(
            Examples::randomIntMatrix, MATRIX_COUNT, AccType::SumAndExtremes),
        std::make_shared<MatrixAccumulateArgs<int>>(
            Examples::randomIntMatrix, MATRIX_COUNT, AccType::SumAndMean),
        std::make_shared<MatrixAccumulateArgs<int>>(
            Examples::randomIntMatrix, MATRIX_COUNT, AccType::DoItAll)
    ));

INSTANTIATE_TEST_SUITE_P(
    AccumulatePrefix,
    MatrixAccumulateDoubleFixture,
    ::testing::Values(
        std::make_shared<MatrixAccumulateArgs<double>>(
            Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::SumOnly),
        std::make_shared<MatrixAccumulateArgs<double>>(
            Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::SumAndExtremes),
        std::make_shared<MatrixAccumulateArgs<double>>(
            Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::SumAndMean),
        std::make_shared<MatrixAccumulateArgs<double>>(
            Examples::randomDoubleMatrix, MATRIX_COUNT, AccType::DoItAll)
    ));

} // namespace tests::Accumulate
