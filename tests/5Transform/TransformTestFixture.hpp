#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Transformer.hpp"

using namespace src::Algorithms;

namespace tests::Transform
{

template <typename InDataType, typename ReturnDataType>
struct TransformTestStruct : public BaseTestStruct<std::vector<ReturnDataType>>
{
protected:
    explicit TransformTestStruct(const TestType testType,
        std::shared_ptr<Transformer<InDataType, ReturnDataType>>&& f)
    : BaseTestStruct<std::vector<ReturnDataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna TransformTestFixture, po ktorej dziedzicza klasy testowe metod Transform
template <typename ReturnDataType>
class TransformTestFixture : public BaseTestFixture<std::vector<ReturnDataType>>
{
protected:
    TransformTestFixture() = default;
};

} // namespace tests::Transform
