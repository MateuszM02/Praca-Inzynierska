#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Remover.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace tests::RemoveEraseIf
{

template <typename DataType, Removable Container = std::vector<DataType>>
struct RemoveEraseIfTestStruct : public BaseTestStruct<Container>
{
protected:
    explicit RemoveEraseIfTestStruct(const TestType testType,
        std::shared_ptr<Remover<DataType, Container>>&& f)
    : BaseTestStruct<Container>(testType, std::move(f))
    { }

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

        return RemoverData<DataType, Container>(elements, predicate);
    }
};

// Klasa abstrakcyjna RemoveEraseIfTestFixture, po ktorej dziedzicza klasy testowe metod RemoveEraseIf
template <typename DataType, Removable Container = std::vector<DataType>>
class RemoveEraseIfTestFixture : public BaseTestFixture<Container>
{
protected:
    RemoveEraseIfTestFixture() = default;
};

} // namespace tests::RemoveEraseIf
