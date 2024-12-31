#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/NthFinder.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;
using namespace src::Wrappers;

namespace tests::NthElement
{

template <typename DataType, NthElementCompatible Container = std::vector<ComparableWrapper<DataType>>>
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
template <typename DataType, NthElementCompatible Container = std::vector<ComparableWrapper<DataType>>>
class NthElementTestFixture : public BaseTestFixture<Container, NthFinder<DataType, Container>>
{
public:
    static NthFinderData<DataType, Container> initTestData(
        ComparableWrapper<DataType>(*generator)(const unsigned int),
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

    void VerifyTestCustomFor7(const BaseTestStruct<NthFinder<DataType, Container>>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&NthElementTestFixture::verifyCustomFor7, this, _1, _2, _3, _4, args.ref_->n_);
        this->VerifyTest(args, checker);
    }

private:
    void verifyCustomFor7(
        const Container& stlResult,
        const Container& boostResult,
        const Container& simpleResult,
        std::ostringstream& os,
        const unsigned int n)
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
