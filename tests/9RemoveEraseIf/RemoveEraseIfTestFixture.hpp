#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Remover.hpp"

using namespace src::Algorithms;

namespace tests::RemoveEraseIf
{

template <typename DataType, Removable Container = std::vector<DataType>>
struct RemoveEraseIfTestStruct : public BaseTestStruct<Remover<DataType, Container>>
{
public:
    RemoveEraseIfTestStruct(
        const std::string& path,
        std::shared_ptr<Remover<DataType, Container>> f)
    : BaseTestStruct<Remover<DataType, Container>>(path, std::move(f))
    { }
};

// Klasa abstrakcyjna RemoveEraseIfTestFixture, po ktorej dziedzicza klasy testowe metod RemoveEraseIf
template <typename DataType, Removable Container = std::vector<DataType>>
class RemoveEraseIfTestFixture : public BaseTestFixture<Remover<DataType, Container>>
{
public:
    static RemoverData<DataType, Container> initTestData(
        DataType(*generator)(const unsigned int),
        bool (*predicate)(const DataType&),
        const unsigned int n)
    {
        Container elements;
        Container expectedResult;
        elements.reserve(n);
        expectedResult.reserve(n);

        DataType value;
        for (unsigned int i = 1; i <= n; ++i)
        {
            value = generator(i);

            if (predicate(value))
                elements.emplace_back(std::move(value));
            else
            {
                elements.emplace_back(value);
                expectedResult.emplace_back(std::move(value));
            }
        }

        return RemoverData<DataType, Container>(
            std::move(elements), std::move(expectedResult), predicate);
    }
};

} // namespace tests::RemoveEraseIf
