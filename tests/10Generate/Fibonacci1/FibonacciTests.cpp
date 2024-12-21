#include "FibonacciTests.hpp"

namespace tests::Generate
{

template <Addable DataType>
FibonacciArgs<DataType>::FibonacciArgs(
    const std::string& path,
    const std::pair<DataType, DataType>& initialPair,
    const unsigned int n)
: GenerateTestStruct<DataType, std::pair<DataType, DataType>>(
    path,
    std::move(src::Algorithms::GeneratorImpl::createFibonacciGenerator(n, initialPair)))
{ }

INSTANTIATE_TEST_SUITE_P(
    FibonacciIntPrefix,
    FibonacciIntFixture,
    ::testing::Values(
        FibonacciArgs<int>(
            Path::Create(GenerateFibonacci, 1),
            std::make_pair(1, 1),
            45u),
        FibonacciArgs<int>(
            Path::Create(GenerateFibonacci, 2),
            std::make_pair(2, 2),
            40u)
    ));

INSTANTIATE_TEST_SUITE_P(
    FibonacciDoublePrefix, 
    FibonacciDoubleFixture,
    ::testing::Values(
        FibonacciArgs<double>(
            Path::Create(GenerateFibonacci, 3),
            std::make_pair(1.0, 1.0),
            80u),
        FibonacciArgs<double>(
            Path::Create(GenerateFibonacci, 4),
            std::make_pair(1.5, 2.5),
            60u)
    ));

} // namespace tests::Generate
