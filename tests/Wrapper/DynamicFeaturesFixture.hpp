#pragma once

#include "../../src/Structures/IntVectorImpl.hpp"
#include "../../src/Structures/MatrixImpl.hpp"
#include "../../src/Structures/PointsImpl.hpp"
#include "../../src/Structures/RandomStringImpl.hpp"

#include <iostream>

#include <gtest/gtest.h>

using namespace src::Structures;

namespace tests::Wrapper
{

class DynamicFeatureTestFixture : public ::testing::Test
{
protected:
    DynamicFeatureTestFixture() = default;

    // Sprawdzenie poprawnosci dynamicznych konstruktorow/operatorow kopiujacych/przenoszacych
    // z klas pochodnych po BaseWrapper
    template <typename Structure, bool SimpleType>
    void VerifyEverythingWorks(const Structure& inStructure)
    {
        // powinien poprawnie zainicjowac zmienna za pomoca konstruktora kopiujacego
        Structure structure1(inStructure);
        EXPECT_EQ(structure1, inStructure) << "Konstruktor kopiujacy nie dziala";

        // powinien poprawnie zainicjowac zmienna za pomoca konstruktora przenoszacego
        Structure structure2 = std::move(structure1);
        if (SimpleType)
        {
            EXPECT_EQ(structure1, structure2) << "Konstruktor przenoszacy nie dziala";
        }
        // w p.p. jesli typ jest skomplikowany to structure1 bedzie w nieokreslonym stanie tutaj
        EXPECT_EQ(structure2, inStructure) << "Konstruktor przenoszacy nie dziala";

        // powinien poprawnie przypisac wartosc zmiennej za pomoca operatora przenoszacego
        structure1 = std::move(structure2);
        if (SimpleType)
        {
            EXPECT_EQ(structure1, structure2) << "Operator przenoszacy nie dziala";
        }
        // w p.p. jesli typ jest skomplikowany to structure2 bedzie w nieokreslonym stanie tutaj
        EXPECT_EQ(structure1, inStructure) << "Operator przenoszacy nie dziala";

        // powinien poprawnie przypisac wartosc zmiennej za pomoca operatora kopiujacego
        structure2 = inStructure;
        EXPECT_EQ(structure1, inStructure) << "Operator kopiujacy nie dziala";
        EXPECT_EQ(structure2, inStructure) << "Operator kopiujacy nie dziala";
    }
};

} // namespace tests::Wrapper
