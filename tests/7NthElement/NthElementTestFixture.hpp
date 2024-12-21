#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/7NthElement/NthFinder.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace tests::NthElement
{

template <typename DataType, NthElementCompatible Container = std::vector<Findable<DataType>>>
struct NthElementTestStruct : public BaseTestStruct<NthFinder<DataType, Container>>
{
public:
    NthElementTestStruct(
        const TestType testType,
        std::shared_ptr<NthFinder<DataType, Container>> f)
    : BaseTestStruct<NthFinder<DataType, Container>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna NthElementTestFixture, po ktorej dziedzicza klasy testowe metod NthElement
template <typename DataType, NthElementCompatible Container = std::vector<Findable<DataType>>>
class NthElementTestFixture : public BaseTestFixture<NthFinder<DataType, Container>>
{
public:
    static NthFinderData<DataType, Container> initTestData(
        Findable<DataType>(*generator)(const unsigned int),
        const unsigned int n,
        const unsigned int vectorSize)
    {
        assert(n < vectorSize && "n must be less than vectorSize");

        Container elements;
        elements.reserve(vectorSize);

        for (unsigned int i = 1; i <= vectorSize; ++i)
        {
            elements.emplace_back(generator(i));
        }

        return NthFinderData<DataType, Container>(std::move(elements), n);
    }
};

} // namespace tests::NthElement
