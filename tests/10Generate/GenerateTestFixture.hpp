#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Generator.hpp"
#include "../../src/Algorithms/GeneratorImpl.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;

namespace tests::Generate
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
struct GenerateTestStruct : public BaseTestStruct<Generator<GeneratedDataType, StateDataType>>
{
public:
    GenerateTestStruct(
        const std::string& path,
        const std::shared_ptr<Generator<GeneratedDataType, StateDataType>> f)
    : BaseTestStruct<Generator<GeneratedDataType, StateDataType>>(path, std::move(f))
    { }
};

// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType> 
class GenerateTestFixture : public BaseTestFixture<Generator<GeneratedDataType, StateDataType>>
{
};

} // namespace tests::Generate
