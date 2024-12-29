#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Generator.hpp"

using namespace src::Algorithms;

namespace tests::Generate
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
struct GenerateTestStruct : public BaseTestStruct<Generator<GeneratedDataType, StateDataType>>
{
public:
    GenerateTestStruct(
        const TestType testType,
        const std::shared_ptr<Generator<GeneratedDataType, StateDataType>> f)
    : BaseTestStruct<Generator<GeneratedDataType, StateDataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType> 
class GenerateTestFixture : public BaseTestFixture<
    std::vector<GeneratedDataType>,
    Generator<GeneratedDataType, StateDataType>>
{
};

} // namespace tests::Generate
