#pragma once
#include "../../src/Algorithms/RemoveEraseIf.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;

namespace tests::RemoveEraseIf
{

template <typename DataType, Removable Container = std::vector<DataType>>
struct RemoveEraseIfTestStruct
{
public:
    RemoveEraseIfTestStruct(
        const std::string& path,
        const std::shared_ptr<Remover<DataType, Container>>& f)
    : filePath_{std::move(path)}
    , removerRef_{std::move(f)}
    { }

    const std::string filePath_;
    const std::shared_ptr<Remover<DataType, Container>> removerRef_;
};

// Klasa abstrakcyjna RemoveEraseIfTestFixture, po ktorej dziedzicza klasy testowe metod RemoveEraseIf
template <typename DataType, Removable Container = std::vector<DataType>>
class RemoveEraseIfTestFixture : public ::testing::TestWithParam<RemoveEraseIfTestStruct<DataType>>
{
public:
    static RemoveEraseIfData<DataType, Container> initTestData(
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

        return RemoveEraseIfData<DataType, Container>(
            std::move(elements), std::move(expectedResult), predicate);
    }

    void VerifyTest(const RemoveEraseIfTestStruct<DataType, Container>& args)
    {
        std::ostringstream os; // Użycie ostringstream do wypisywania wyników testów

        const Container& stlResult = args.removerRef_->callRemover(
            src::MethodType::STL, os);
        const Container& boostResult = args.removerRef_->callRemover(
            src::MethodType::Boost, os);
        const Container& simpleResult = args.removerRef_->callRemover(
            src::MethodType::Simple, os);
        const Container& expectedResult = args.removerRef_.get()->expectedResult_;

        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();
        
        EXPECT_EQ(stlResult.size(), expectedResult.size()) << "Rozmiar wyniku STL rozni sie od oczekiwanego.";
        EXPECT_EQ(boostResult.size(), expectedResult.size()) << "Rozmiar wyniku Boost rozni sie od oczekiwanego.";
        EXPECT_EQ(simpleResult.size(), expectedResult.size()) << "Rozmiar wyniku Simple rozni sie od oczekiwanego.";

        // Zapisywanie wynikow testu do pliku
        std::ofstream outFile(args.filePath_, std::ios::out | std::ios::trunc);
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
            
            auto stlIter = stlResult.begin();
            auto boostIter = boostResult.begin();
            auto simpleIter = simpleResult.begin();
            auto expectedIter = expectedResult.begin();
            unsigned int i = 0;

            // Pętla for do porównywania wyników, jeśli rozmiary są równe
            while (expectedIter != expectedResult.end())
            {
                EXPECT_EQ(*stlIter, *expectedIter) << "Wynik STL rozni sie na indeksie " << i;
                EXPECT_EQ(*boostIter, *expectedIter) << "Wynik Boost rozni sie na indeksie " << i;
                EXPECT_EQ(*simpleIter, *expectedIter) << "Wynik Simple rozni sie na indeksie " << i;
            
                ++i;
                ++stlIter;
                ++boostIter;
                ++simpleIter;
                ++expectedIter;
            }
            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath_ << "\n";
        }
    }

};

} // namespace tests::RemoveEraseIf
