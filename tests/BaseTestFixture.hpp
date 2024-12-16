#pragma once

#include "../src/Algorithms/Base.hpp"

#include <fstream>

#include <gtest/gtest.h>

// os << "Wartosc " #val1 " (" << (val1) << ") rozni sie od wartosci " #val2 " (" << (val2) << ").\n"; \

#define EXPECT_EQ_OS(val1, val2, os) \
    if ((val1) != (val2)) \
    { \
        os << "Wartosc " #val1 " rozni sie od wartosci " #val2 ".\n"; \
    } \
    EXPECT_EQ(val1, val2)

namespace tests
{

// PtrType musi byc postaci Doer<DataType, Container>
template <typename PtrType>
struct BaseTestStruct
{
public:
    BaseTestStruct(const std::string& path, std::shared_ptr<PtrType> f)
    : filePath_{std::move(path)}
    , ref_{std::move(f)}
    { }

    const std::string filePath_;
    const std::shared_ptr<PtrType> ref_;
};

// Klasa abstrakcyjna BaseTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename PtrType> 
class BaseTestFixture : public ::testing::TestWithParam<BaseTestStruct<PtrType>>
{ 
public:
    void VerifyTest(const BaseTestStruct<PtrType>& args)
    {
        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const auto& stlResult =
            args.ref_->call(src::MethodType::STL, os);
        const auto& boostResult =
            args.ref_->call(src::MethodType::Boost, os);
        const auto& simpleResult =
            args.ref_->call(src::MethodType::Simple, os);
        const auto& expectedResult =
            args.ref_.get()->expectedResult_;

        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();

        EXPECT_EQ_OS(stlResult.size(), expectedResult.size(), os) << "Rozmiar wyniku STL różni się od oczekiwanego."; 
        EXPECT_EQ_OS(boostResult.size(), expectedResult.size(), os) << "Rozmiar wyniku Boost różni się od oczekiwanego."; 
        EXPECT_EQ_OS(simpleResult.size(), expectedResult.size(), os) << "Rozmiar wyniku Simple różni się od oczekiwanego.";

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
            
            verifyElementEqualities(stlResult, boostResult, simpleResult, expectedResult, os);
            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath_ << "\n";
        }
    }

protected:
    void verifyElementEqualities(
        const auto& stlResult,
        const auto& boostResult,
        const auto& simpleResult,
        const auto& expectedResult,
        std::ostringstream& os)
    {
        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        auto expectedIter = expectedResult.begin();
        unsigned int i = 0;

        while (expectedIter != expectedResult.end())
        {
            EXPECT_EQ_OS(*stlIter, *expectedIter, os) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_EQ_OS(*boostIter, *expectedIter, os) << "Wynik Boost rozni sie na indeksie " << i;
            EXPECT_EQ_OS(*simpleIter, *expectedIter, os) << "Wynik Simple rozni sie na indeksie " << i;
        
            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
            ++expectedIter;
        }
    }
};

} // namespace tests
