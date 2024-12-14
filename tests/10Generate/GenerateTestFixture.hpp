#pragma once
#include "../../src/Algorithms/Functor.hpp"
#include "../../src/Algorithms/FunctorImpl.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;

namespace tests::Generate
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
struct GenerateTestStruct
{
public:
    const std::string filePath;
    std::shared_ptr<Functor<GeneratedDataType, StateDataType>> functorRef;
    
    const unsigned int number;
    const std::vector<GeneratedDataType> expectedResult;

    GenerateTestStruct(
        const std::string& path,
        std::shared_ptr<Functor<GeneratedDataType, StateDataType>> f,
        const unsigned int n,
        const std::vector<GeneratedDataType>& v)
    : filePath{path}
    , functorRef{f}
    , number{n}
    , expectedResult{v}
    { }
};

// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType> 
class GenerateTestFixture : public ::testing::TestWithParam<GenerateTestStruct<GeneratedDataType, StateDataType>>
{ 
public:
    void VerifyTest(const GenerateTestStruct<GeneratedDataType, StateDataType>& args)
    {
        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const std::vector<GeneratedDataType>& stlResult =
            args.functorRef->callFunctor(args.number, src::MethodType::STL, os);
        const std::vector<GeneratedDataType>& boostResult =
            args.functorRef->callFunctor(args.number, src::MethodType::Boost, os);
        const std::vector<GeneratedDataType>& simpleResult =
            args.functorRef->callFunctor(args.number, src::MethodType::Simple, os);

        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();

        EXPECT_EQ(stlResult.size(), args.expectedResult.size()) << "Rozmiar wyniku STL różni się od oczekiwanego."; 
        EXPECT_EQ(boostResult.size(), args.expectedResult.size()) << "Rozmiar wyniku Boost różni się od oczekiwanego."; 
        EXPECT_EQ(simpleResult.size(), args.expectedResult.size()) << "Rozmiar wyniku Simple różni się od oczekiwanego.";

        for (unsigned int i = 0; i < args.expectedResult.size(); ++i)
        {
            EXPECT_EQ(stlResult[i], args.expectedResult[i]) << "Wynik STL różni się na indeksie " << i;
            EXPECT_EQ(boostResult[i], args.expectedResult[i]) << "Wynik Boost różni się na indeksie " << i;
            EXPECT_EQ(simpleResult[i], args.expectedResult[i]) << "Wynik Simple różni się na indeksie " << i;
        }

        // Zapisywanie wynikow testu do pliku
        std::ofstream outFile(args.filePath, std::ios::out | std::ios::trunc);
        if (outFile.is_open())
        {
            if (::testing::Test::HasFailure()) 
            {
                outFile << "Rozmiary wynikow nie zgadzaja sie z oczekiwanymi.\n";
                outFile << ::testing::internal::GetCapturedStdout();
                outFile << ::testing::internal::GetCapturedStderr();
                outFile.close();
                return;
            }
            
            // Petla for do porownywania wynikow, jesli rozmiary sa rowne
            for (unsigned int i = 0; i < args.expectedResult.size(); ++i)
            {
                EXPECT_EQ(stlResult[i], args.expectedResult[i]) << "Wynik STL rozni sie na indeksie " << i;
                EXPECT_EQ(boostResult[i], args.expectedResult[i]) << "Wynik Boost rozni sie na indeksie " << i;
                EXPECT_EQ(simpleResult[i], args.expectedResult[i]) << "Wynik Simple rozni sie na indeksie " << i;
            }
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
