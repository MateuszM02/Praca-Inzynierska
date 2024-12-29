#pragma once

#include "../src/Algorithms/Base.hpp"
#include "Path.hpp"

#include <fstream>
#include <unordered_map>

#include <gtest/gtest.h>

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
    BaseTestStruct(const TestType testType, std::shared_ptr<PtrType> f)
    : filePath_{createPath(testType)}
    , ref_{std::move(f)}
    { }

    const std::string filePath_;
    const std::shared_ptr<PtrType> ref_;

protected:
    std::string createPath(const TestType testType) const
    {
        static std::unordered_map<TestType, unsigned int> testIdMap;
        return Path::Create(testType, ++testIdMap[testType]);
    }
};

// Klasa abstrakcyjna BaseTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename Container, typename PtrType> 
class BaseTestFixture : public ::testing::TestWithParam<BaseTestStruct<PtrType>>
{ 
public:
    void VerifyTest(const BaseTestStruct<PtrType>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&BaseTestFixture::verifyElementEqualities, this, _1, _2, _3, _4);
        VerifyTest(args, checker);
    }

    void VerifyTest(const BaseTestStruct<PtrType>& args,
        std::function<void(const Container&, const Container&,
            const Container&, std::ostringstream&)> checker)
    {
        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const Container& stlResult =
            args.ref_->call(src::MethodType::STL, os);
        const Container& boostResult =
            args.ref_->call(src::MethodType::Boost, os);
        const Container& simpleResult =
            args.ref_->call(src::MethodType::Simple, os); 
        
        // Zapisywanie wynikow testu do pliku
        std::ofstream outFile(args.filePath_, std::ios::out | std::ios::trunc);
        if (outFile.is_open())
        {
            checker(stlResult, boostResult, simpleResult, os);
            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath_ << "\n";
        }
    }

private:
    void verifyElementEqualities(
        const Container& stlResult,
        const Container& boostResult,
        const Container& simpleResult,
        std::ostringstream& os)
    {
        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();

        EXPECT_EQ_OS(stlResult.size(), simpleResult.size(), os) << "Rozmiar wyniku STL rozni sie od oczekiwanego.";
        EXPECT_EQ_OS(boostResult.size(), simpleResult.size(), os) << "Rozmiar wyniku Boost rozni sie od oczekiwanego.";

        if (::testing::Test::HasFailure())  return;

        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        unsigned int i = 0;

        while (simpleIter != simpleResult.end())
        {
            EXPECT_EQ_OS(*stlIter, *simpleIter, os) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_EQ_OS(*boostIter, *simpleIter, os) << "Wynik Boost rozni sie na indeksie " << i;
            
            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
        }
    }
};

} // namespace tests
