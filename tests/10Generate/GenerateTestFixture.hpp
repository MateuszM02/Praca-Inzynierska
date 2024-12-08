#pragma once
#include "../../src/10Generate/Functor.hpp"

#include <fstream>
#include <gtest/gtest.h>

using namespace src::Generate;

namespace tests::Generate
{

template <typename DataType>
struct GenerateTestStruct
{
public:
    const std::string filePath;
    std::shared_ptr<Functor<DataType>> functorRef;
    unsigned int number;
    std::vector<DataType> expectedResult;

    GenerateTestStruct(
        const std::string& path,
        std::shared_ptr<Functor<DataType>> f,
        const unsigned int n,
        const std::vector<DataType>& v)
    : filePath{path}
    , functorRef{f}
    , number{n}
    , expectedResult{v}
    { }
};

// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <class DataType> 
class GenerateTestFixture : public ::testing::TestWithParam<GenerateTestStruct<DataType>>
{ 
public:
    void SetUp() override
    {
        std::cout << "Inside SetUp\n";
    }

    void VerifyTest(const GenerateTestStruct<DataType>& args)
    {
        const std::shared_ptr<Functor<DataType>> boostFunctor = args.functorRef->clone();
        const std::shared_ptr<Functor<DataType>> simpleFunctor = args.functorRef->clone();

        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const std::vector<DataType>& stlResult = args.functorRef->callFunctor(args.number, src::MethodType::STL, os);
        const std::vector<DataType>& boostResult = boostFunctor->callFunctor(args.number, src::MethodType::Boost, os);
        const std::vector<DataType>& simpleResult = simpleFunctor->callFunctor(args.number, src::MethodType::Simple, os);

        EXPECT_EQ(stlResult.size(), args.expectedResult.size()) << "Rozmiar wyniku STL różni się od oczekiwanego."; 
        EXPECT_EQ(boostResult.size(), args.expectedResult.size()) << "Rozmiar wyniku Boost różni się od oczekiwanego."; 
        EXPECT_EQ(simpleResult.size(), args.expectedResult.size()) << "Rozmiar wyniku Simple różni się od oczekiwanego.";

        for (unsigned int i = 0; i < args.expectedResult.size(); ++i)
        {
            EXPECT_EQ(stlResult[i], args.expectedResult[i]) << "Wynik STL różni się na indeksie " << i;
            EXPECT_EQ(boostResult[i], args.expectedResult[i]) << "Wynik Boost różni się na indeksie " << i;
            EXPECT_EQ(simpleResult[i], args.expectedResult[i]) << "Wynik Simple różni się na indeksie " << i;
        }

        // Wypisz wynik testu do podanego pliku
        std::ofstream outFile(args.filePath, std::ios::out | std::ios::trunc);
        if (outFile.is_open())
        {
            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath << "\n";
        }
    }
};

} // namespace tests::Generate
