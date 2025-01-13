#pragma once

#include "../../../src/Concepts/DataTypeConcepts.hpp"
#include "../../../src/Structures/PointsImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Concepts;

namespace tests::Generate
{

template <Addable DataType>
struct FibonacciGenerateArgs final : public GenerateTestStruct<DataType, Point2D<DataType>>
{
    explicit FibonacciGenerateArgs(
        const Point2D<DataType>& initialPair,
        unsigned int n)
    : GenerateTestStruct<DataType, Point2D<DataType>>(
        TestType::GenerateFibonacci,
        [initialPair, n]()
        {
            auto stateCreator = [](Point2D<DataType>& currentState)
            {
                currentState = Point2D(currentState.second_, currentState.first_ + currentState.second_);
                return currentState.first_;
            };

            return std::make_shared<Generator<DataType, Point2D<DataType>>>(
                n, initialPair, stateCreator);
        })
    { }
};

class FibonacciGenerateIntFixture : public GenerateTestFixture<int, Point2D<int>>
{ };

class FibonacciGenerateDoubleFixture : public GenerateTestFixture<double, Point2D<double>>
{ };

TEST_P(FibonacciGenerateIntFixture, intTest)
{
    VerifyTest(GetParam());
}

TEST_P(FibonacciGenerateDoubleFixture, doubleTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Generate
