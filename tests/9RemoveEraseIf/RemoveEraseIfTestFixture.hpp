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
        Callback<Remover<Container>>&& callback)
    : BaseTestStruct<Container>(testType, std::move(callback))
    { }

    static std::shared_ptr<Remover<Container>> initTestData9(
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

        RemoverData<Container> data(std::move(elements), predicate);
        return std::make_shared<Remover<Container>>(std::move(data));
    }

    static std::shared_ptr<Remover<Container>> initTestData9(
        DataType(*generator)(const unsigned int),
        bool (*predicate)(const DataType&),
        const TestPair& info)
    {
        Container elements;
        elements.reserve(info.first);

        for (unsigned int i = 1; i <= info.first; ++i)
        {
            elements.emplace_back(generator(info.second));
        }

        RemoverData<Container> data(std::move(elements), predicate);
        return std::make_shared<Remover<Container>>(std::move(data));
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
