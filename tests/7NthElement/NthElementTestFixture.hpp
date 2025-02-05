#pragma once

#define nth first
#define numberOfElements second

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/NthFinder.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace tests::NthElement
{

template <typename Container>
struct NthElementTestStruct : public BaseTestStruct<Container>
{
protected:
    using DataType = typename Container::value_type;

    explicit NthElementTestStruct(
        const TestType testType,
        Callback<NthFinder<Container>>&& callback)
    : BaseTestStruct<Container>(testType, std::move(callback))
    { }

    static std::shared_ptr<NthFinder<Container>> initTestData7(
        DataType(*generator)(const unsigned int),
        const TestPair& info)
    {
        assert(info.nth < info.numberOfElements && "n must be smaller than number of elements");

        Container elements;
        elements.reserve(info.numberOfElements);

        for (unsigned int i = 1; i <= info.numberOfElements; ++i)
        {
            elements.emplace_back(generator(i));
        }

        NthFinderData<Container> data(std::move(elements), info.nth);
        return std::make_shared<NthFinder<Container>>(std::move(data));
    }
};

// Klasa abstrakcyjna NthElementTestFixture, po ktorej dziedzicza klasy testowe metod NthElement
template <typename Container>
class NthElementTestFixture : public BaseTestFixture<Container>
{
protected:
    using DataType = typename Container::value_type;

    void VerifyTestCustomFor7(const std::shared_ptr<BaseTestStruct<Container>>& args)
    {
        using namespace std::placeholders;
        const std::size_t n = args->getField(&NthFinder<Container>::n_);
        auto checker = std::bind(&NthElementTestFixture::verifyCustomFor7, this, _1, _2, _3, _4, n);
        this->VerifyTest(args, checker);
    }

private:
    void verifyCustomFor7(
        const Container& stlResult,
        const Container& boostResult,
        const Container& simpleResult,
        std::ostringstream& os,
        const unsigned int n)
    requires EqualityComparable<DataType>
    {
        // Petla for do porownywania wynikow, jesli rozmiary sa rowne
        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        unsigned int i = 0;

        auto stlNthIter = stlResult.begin();
        auto boostNthIter = boostResult.begin();
        auto simpleNthIter = simpleResult.begin();
        std::advance(stlNthIter, n);
        std::advance(boostNthIter, n);
        std::advance(simpleNthIter, n);

        // n-ty element musi byc taki sam
        EXPECT_EQ_OS(*stlNthIter, *boostNthIter, os) << "Wynik STL rozni sie od Boost na n-tej pozycji";
        EXPECT_EQ_OS(*stlNthIter, *simpleNthIter, os) << "Wynik STL rozni sie od Simple na n-tej pozycji";
        EXPECT_EQ_OS(*boostNthIter, *simpleNthIter, os) << "Wynik Boost rozni sie od Simple na n-tej pozycji";

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

} // namespace tests::NthElement
