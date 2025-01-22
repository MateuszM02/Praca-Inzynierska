#pragma once

#include "../../src/Structures/IntVectorImpl.hpp"
#include "../../src/Structures/MatrixImpl.hpp"
#include "../../src/Structures/CustomPairImpl.hpp"
#include "../../src/Structures/RandomStringImpl.hpp"

#include "../../src/Algorithms/Accumulator.hpp"
#include "../../src/Algorithms/Generator.hpp"
#include "../../src/Algorithms/Merger.hpp"
#include "../../src/Algorithms/MinMaxFinder.hpp"
#include "../../src/Algorithms/NthFinder.hpp"
#include "../../src/Algorithms/Regex.hpp"
#include "../../src/Algorithms/Remover.hpp"
#include "../../src/Algorithms/Sorter.hpp"
#include "../../src/Algorithms/Transformer.hpp"
#include "../../src/Algorithms/Uniquer.hpp"

#include <iostream>

#include <gtest/gtest.h>

using namespace src::Algorithms;
using namespace src::Structures;

namespace tests::Static
{

class StaticTestFixture : public ::testing::Test
{
protected:
    StaticTestFixture() = default;

    // Sprawdzenie poprawnosci dynamicznych konstruktorow/operatorow kopiujacych/przenoszacych
    // z klas pochodnych po BaseWrapper
    template <typename Container, bool SimpleType>
    void VerifyMoveCopyWorks(const Container& inStructure) const
    {
        // powinien poprawnie zainicjowac zmienna za pomoca konstruktora kopiujacego
        Container structure1(inStructure);
        ASSERT_EQ(structure1, inStructure) << "Konstruktor kopiujacy nie dziala";

        // powinien poprawnie zainicjowac zmienna za pomoca konstruktora przenoszacego
        Container structure2 = std::move(structure1);
        if (SimpleType)
        {
            ASSERT_EQ(structure1, structure2) << "Konstruktor przenoszacy nie dziala";
        }
        // w p.p. jesli typ jest skomplikowany to structure1 bedzie w nieokreslonym stanie tutaj
        ASSERT_EQ(structure2, inStructure) << "Konstruktor przenoszacy nie dziala";

        // powinien poprawnie przypisac wartosc zmiennej za pomoca operatora przenoszacego
        structure1 = std::move(structure2);
        if (SimpleType)
        {
            ASSERT_EQ(structure1, structure2) << "Operator przenoszacy nie dziala";
        }
        // w p.p. jesli typ jest skomplikowany to structure2 bedzie w nieokreslonym stanie tutaj
        ASSERT_EQ(structure1, inStructure) << "Operator przenoszacy nie dziala";

        // powinien poprawnie przypisac wartosc zmiennej za pomoca operatora kopiujacego
        structure2 = inStructure;
        ASSERT_EQ(structure1, inStructure) << "Operator kopiujacy nie dziala";
        ASSERT_EQ(structure2, inStructure) << "Operator kopiujacy nie dziala";
    }

    // 1. MinMax
    template <typename Container, typename ResultType>
    void VerifyMinMaxWorks(Container&& elements,
        const ResultType& expectedResult) const
    {
        const MinMaxFinder<Container> finder(std::move(elements));
        auto [stlResult, boostResult, simpleResult] = finder.callEach();

        EXPECT_EQ(stlResult, expectedResult) << "STL zwrocil zly wynik!";
        EXPECT_EQ(boostResult, expectedResult) << "Boost zwrocil zly wynik!";
        EXPECT_EQ(simpleResult, expectedResult) << "Simple zwrocil zly wynik!";
    }

    // 2. Accumulate
    template <typename DataType>
    void VerifyAccumulateWorks(std::vector<DataType>&& elements,
        const AccResults<DataType>& expectedResult) const
    {
        const Accumulator<DataType> accumulator(std::move(elements), AccType::DoItAll);
        auto [stlResult, boostResult, simpleResult] = accumulator.callEach();

        EXPECT_EQ(stlResult.sum, expectedResult.sum) << "Suma STL jest niepoprawna";
        EXPECT_EQ(boostResult.sum, expectedResult.sum) << "Suma Boost jest niepoprawna";
        EXPECT_EQ(simpleResult.sum, expectedResult.sum) << "Suma Simple jest niepoprawna";

        EXPECT_EQ(stlResult.minimum, expectedResult.minimum) << "Minimum STL jest niepoprawne";
        EXPECT_EQ(boostResult.minimum, expectedResult.minimum) << "Minimum Boost jest niepoprawne";
        EXPECT_EQ(simpleResult.minimum, expectedResult.minimum) << "Minimum Simple jest niepoprawne";

        EXPECT_EQ(stlResult.maximum, expectedResult.maximum) << "Maximum STL jest niepoprawne";
        EXPECT_EQ(boostResult.maximum, expectedResult.maximum) << "Maximum Boost jest niepoprawne";
        EXPECT_EQ(simpleResult.maximum, expectedResult.maximum) << "Maximum Simple jest niepoprawne";

        EXPECT_EQ(stlResult.mean, expectedResult.mean) << "Srednia STL jest niepoprawna";
        EXPECT_EQ(boostResult.mean, expectedResult.mean) << "Srednia Boost jest niepoprawna";
        EXPECT_EQ(simpleResult.mean, expectedResult.mean) << "Srednia Simple jest niepoprawna";
    }

    // 3. Merge
    template <typename DataType>
    void VerifyMergeWorks(MergerData<DataType>&& elements,
        const std::vector<DataType>& expectedResult) const
    {
        const Merger<DataType> merger(std::move(elements));
        VerifyAlgorithmWorks(merger, expectedResult);
    }

    // 4. Sort
    template <typename DataType>
    void VerifySortWorks(std::vector<DataType>&& elements,
        const std::vector<DataType>& expectedResult) const
    {
        const Sorter<DataType> sorter(std::move(elements));
        VerifyAlgorithmWorks(sorter, expectedResult);
    }

    // 5. Transform
    template <typename InDataType, typename ReturnDataType>
    void VerifyTransformWorks(std::vector<InDataType>&& elements,
        ReturnDataType (*const converter)(const InDataType&),
        const std::vector<ReturnDataType>& expectedResult) const
    {
        const Transformer<InDataType, ReturnDataType> transformer(std::move(elements), converter);
        VerifyAlgorithmWorks(transformer, expectedResult);
    }

    // 6. Unique
    template <typename DataType>
    void VerifyUniqueWorks(std::vector<DataType>&& elements,
        const std::vector<DataType>& expectedResult) const
    {
        const Uniquer<DataType> uniquer(std::move(elements));
        VerifyAlgorithmWorks(uniquer, expectedResult);
    }

    // 7. Nth element
    template <typename Container>
    void VerifyNthFinderWorks(Container&& elements,
        const std::size_t n,
        const Container& expectedResult) const
    {
        NthFinderData<Container> data(std::move(elements), n);
        NthFinder<Container> finder(std::move(data));

        auto [stlResult, boostResult, simpleResult] = finder.callEach();

        ASSERT_EQ(stlResult.size(), expectedResult.size()) << "STL zwrocil zly wynik!";
        ASSERT_EQ(boostResult.size(), expectedResult.size()) << "Boost zwrocil zly wynik!";
        ASSERT_EQ(simpleResult.size(), expectedResult.size()) << "Simple zwrocil zly wynik!";

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

    // 8. Regex
    void VerifyRegexWorks(const std::string& text,
        const std::string& pattern,
        const std::vector<std::string>& expectedResult) const
    {
        const RegexData data(text, pattern);
        const RegexEvaluator evaluator(data);
        VerifyAlgorithmWorks(evaluator, expectedResult);
    }

    // 9. Remove erase if
    template <typename Container>
    void VerifyRemoveEraseIfWorks(const Container& elements,
        bool (*const predicate)(const typename Container::value_type&),
        const Container& expectedResult) const
    {
        const RemoverData data(elements, predicate);
        const Remover remover(data);
        VerifyAlgorithmWorks(remover, expectedResult);
    }

    // 10. Generate
    template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
    void VerifyGenerateWorks(const std::size_t n,
        StateDataType&& initialState,
        std::function<GeneratedDataType(StateDataType&)>&& stateCreator,
        const std::vector<GeneratedDataType>& expectedResult) const
    {
        const Generator<GeneratedDataType, StateDataType> generator(n,
            std::move(initialState),
            std::move(stateCreator));
        VerifyAlgorithmWorks(generator, expectedResult);
    }

    void VerifyGenerateRandomStringWorks(const std::size_t n,
        CopyableRandomString&& initialState,
        std::function<std::string(CopyableRandomString&)>&& stateCreator,
        const std::vector<std::string>& expectedResult) const
    {
        const Generator<std::string, CopyableRandomString> generator(n,
            std::move(initialState),
            std::move(stateCreator));
        auto [stlResult, boostResult, simpleResult] = generator.callEach();

        ASSERT_EQ(stlResult.size(), expectedResult.size()) << "STL zwrocil zly wynik!";
        ASSERT_EQ(boostResult.size(), expectedResult.size()) << "Boost zwrocil zly wynik!";
        ASSERT_EQ(simpleResult.size(), expectedResult.size()) << "Simple zwrocil zly wynik!";

        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        auto expectedIter = expectedResult.begin();
        unsigned int i = 0;

        while (expectedIter != expectedResult.end())
        {
            EXPECT_EQ(stlIter->size(), expectedIter->size()) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_EQ(boostIter->size(), expectedIter->size()) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_EQ(simpleIter->size(), expectedIter->size()) << "Wynik STL rozni sie na indeksie " << i;

            ++stlIter;
            ++boostIter;
            ++simpleIter;
            ++expectedIter;
            ++i;
        }
    }

private:
    // beda wywolywac ta funkcje zgodne z zasada DRY
    template <typename Container, typename ResultType>
    void VerifyAlgorithmWorks(const BaseClass<Container>& algorithm,
        const ResultType& expectedResult) const
    {
        auto [stlResult, boostResult, simpleResult] = algorithm.callEach();

        ASSERT_EQ(stlResult.size(), expectedResult.size()) << "STL zwrocil zly wynik!";
        // ASSERT_EQ(boostResult.size(), expectedResult.size()) << "Boost zwrocil zly wynik!";
        ASSERT_EQ(simpleResult.size(), expectedResult.size()) << "Simple zwrocil zly wynik!";
        ASSERT_EQ(boostResult.size(), expectedResult.size()) << "Boost zwrocil zly wynik!";

        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        auto expectedIter = expectedResult.begin();
        unsigned int i = 0;

        while (expectedIter != expectedResult.end())
        {
            EXPECT_EQ(*stlIter, *expectedIter) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_EQ(*boostIter, *expectedIter) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_EQ(*simpleIter, *expectedIter) << "Wynik STL rozni sie na indeksie " << i;

            ++stlIter;
            ++boostIter;
            ++simpleIter;
            ++expectedIter;
            ++i;
        }
    }

};

} // namespace tests::Static
