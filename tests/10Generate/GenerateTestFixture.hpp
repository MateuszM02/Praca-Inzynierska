#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Generator.hpp"

using namespace src::Algorithms;

namespace tests::Generate
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
struct GenerateTestStruct : public BaseTestStruct<std::vector<GeneratedDataType>>
{
protected:
    explicit GenerateTestStruct(const TestType testType,
        std::shared_ptr<Generator<GeneratedDataType, StateDataType>>&& f)
    : BaseTestStruct<std::vector<GeneratedDataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType> 
class GenerateTestFixture : public BaseTestFixture<std::vector<GeneratedDataType>>
{
protected:
    GenerateTestFixture() = default;
};

} // namespace tests::Generate
