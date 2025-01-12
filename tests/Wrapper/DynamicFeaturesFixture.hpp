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
    void VerifyMoveCopyWorks(const Structure& inStructure) const
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

    template <typename InStructure>
    void VerifyNthFinderWorks(const InStructure& inStructure,
        const std::size_t n,
        const InStructure& expectedResult) const
    {
        const NthFinderData<InStructure> data(inStructure, n);
        NthFinder<InStructure> finder(std::move(data));

        auto [stlResult, boostResult, simpleResult] = finder.callEach();

        EXPECT_EQ(stlResult.size(), expectedResult.size()) << "STL zwrocil zly wynik!";
        EXPECT_EQ(boostResult.size(), expectedResult.size()) << "Boost zwrocil zly wynik!";
        EXPECT_EQ(simpleResult.size(), expectedResult.size()) << "Simple zwrocil zly wynik!";

        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        unsigned int i = 0;

        auto stlNthIter = stlResult.begin();
        auto boostNthIter = boostResult.begin();
        auto simpleNthIter = simpleResult.begin();
        auto expectedNthIter = expectedResult.begin();
        std::advance(stlNthIter, n);
        std::advance(boostNthIter, n);
        std::advance(simpleNthIter, n);
        std::advance(expectedNthIter, n);

        // n-ty element musi byc taki sam
        EXPECT_EQ(*stlNthIter, *expectedNthIter) << "Wynik STL jest zly na n-tej pozycji";
        EXPECT_EQ(*boostNthIter, *expectedNthIter) << "Wynik Boost jest zly na n-tej pozycji";
        EXPECT_EQ(*simpleNthIter, *expectedNthIter) << "Wynik Simple jest zly na n-tej pozycji";

        // wszystkie elementy przed n-tym musza byc mniejsze od niego
        while (simpleIter != simpleNthIter)
        {
            EXPECT_LT(*stlIter, *stlNthIter) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_LT(*boostIter, *boostNthIter) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_LT(*simpleIter, *simpleNthIter) << "Wynik Boost rozni sie na indeksie " << i;

            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
        }

        ++i;
        ++stlIter;
        ++boostIter;
        ++simpleIter;

        // wszystkie elementy po n-tym musza byc wieksze od niego
        while (simpleIter != simpleResult.end())
        {
            EXPECT_LT(*stlNthIter, *stlIter) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_LT(*boostNthIter, *boostIter) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_LT(*simpleNthIter, *simpleIter) << "Wynik Boost rozni sie na indeksie " << i;

            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
        }
    }
};

} // namespace tests::Wrapper
