#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Remover.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace tests::RemoveEraseIf
{

template <typename DataType, Removable Container = std::vector<DataType>>
struct RemoveEraseIfTestStruct : public BaseTestStruct<Container, Remover<DataType, Container>>
{
public:
    RemoveEraseIfTestStruct(
        const TestType testType,
        std::shared_ptr<Remover<DataType, Container>> f)
    : BaseTestStruct<Container, Remover<DataType, Container>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna RemoveEraseIfTestFixture, po ktorej dziedzicza klasy testowe metod RemoveEraseIf
template <typename DataType, Removable Container = std::vector<DataType>>
class RemoveEraseIfTestFixture : public BaseTestFixture<Container, Remover<DataType, Container>>
{
public:
    static RemoverData<DataType, Container> initTestData(
        DataType(*generator)(const unsigned int),
        bool (*predicate)(const DataType&),
        const unsigned int n)
    {
        Container elements;
        elements.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            elements.emplace_back(generator(i));
        }

        return RemoverData<DataType, Container>(std::move(elements), predicate);
    }
};

} // namespace tests::RemoveEraseIf
