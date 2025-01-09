#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Remover.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace tests::RemoveEraseIf
{

template <typename Container>
struct RemoveEraseIfTestStruct : public BaseTestStruct<Container>
{
protected:
    using DataType = typename Container::value_type;

    explicit RemoveEraseIfTestStruct(const TestType testType,
        std::shared_ptr<Remover<Container>>&& f)
    : BaseTestStruct<Container>(testType, std::move(f))
    { }

    static RemoverData<Container> initTestData(
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

        return RemoverData<Container>(elements, predicate);
    }
};

// Klasa abstrakcyjna RemoveEraseIfTestFixture, po ktorej dziedzicza klasy testowe metod RemoveEraseIf
template <typename Container>
class RemoveEraseIfTestFixture : public BaseTestFixture<Container>
{
protected:
    RemoveEraseIfTestFixture() = default;
};

} // namespace tests::RemoveEraseIf
