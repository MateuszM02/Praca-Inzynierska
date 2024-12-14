#pragma once
#include "../../src/Algorithms/Merger.hpp"
#include "../../src/Algorithms/MergerImpl.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;

namespace tests::Merge
{

template <typename DataType>
struct MergeTestStruct
{
public:
    MergeTestStruct(
        const std::string& path,
        const std::shared_ptr<Merger<DataType>>& f)
    : filePath{std::move(path)}
    , mergerRef{std::move(f)}
    { }

    const std::string filePath;
    const std::shared_ptr<Merger<DataType>> mergerRef;
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <typename DataType>
class MergeTestFixture : public ::testing::TestWithParam<MergeTestStruct<DataType>>
{
public:
    static VectorStruct<DataType> initTestData(
        Mergeable<DataType> (*fun1)(const unsigned int),
        Mergeable<DataType> (*fun2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    {
        std::vector<Mergeable<DataType>> v1;
        std::vector<Mergeable<DataType>> v2;
        std::vector<Mergeable<DataType>> expectedResult;
        v1.reserve(n1);
        v2.reserve(n2);
        expectedResult.reserve(n1 + n2);

        for (unsigned int i = 1; i <= n1; ++i)
        {
            v1.emplace_back(fun1(i));
        }
        for (unsigned int i = 1; i <= n2; ++i)
        {
            v2.emplace_back(fun2(i));
        }

        unsigned int x1 = 1;
        unsigned int x2 = 1;
        Mergeable<DataType> p1 = fun1(x1);
        Mergeable<DataType> p2 = fun2(x2);

        while (x1 <= n1 && x2 <= n2)
        {
            if (p1 < p2)
            {
                expectedResult.emplace_back(std::move(p1));
                p1 = fun1(++x1);
            }
            else
            {
                expectedResult.emplace_back(std::move(p2));
                p2 = fun2(++x2);
            }
        }
        while (x1 <= n1)
        {
            expectedResult.emplace_back(std::move(p1));
            p1 = fun1(++x1);
        }
        while (x2 <= n2)
        {
            expectedResult.emplace_back(std::move(p2));
            p2 = fun2(++x2);
        }

        return VectorStruct<DataType>(std::move(v1), std::move(v2), std::move(expectedResult));
    }

    void VerifyTest(const MergeTestStruct<DataType>& args)
    {
        std::ostringstream os; // Użycie ostringstream do wypisywania wyników testów

        const std::vector<Mergeable<DataType>>& stlResult = args.mergerRef->callMerger(
            src::MethodType::STL, os);
        const std::vector<Mergeable<DataType>>& boostResult = args.mergerRef->callMerger(
            src::MethodType::Boost, os);
        const std::vector<Mergeable<DataType>>& simpleResult = args.mergerRef->callMerger(
            src::MethodType::Simple, os);
        const std::vector<Mergeable<DataType>>& expectedResult = args.mergerRef.get()->expectedResult_;

        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();
        
        EXPECT_EQ(stlResult.size(), expectedResult.size()) << "Rozmiar wyniku STL rozni sie od oczekiwanego.";
        EXPECT_EQ(boostResult.size(), expectedResult.size()) << "Rozmiar wyniku Boost rozni sie od oczekiwanego.";
        EXPECT_EQ(simpleResult.size(), expectedResult.size()) << "Rozmiar wyniku Simple rozni sie od oczekiwanego.";

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
            
            // Pętla for do porównywania wyników, jeśli rozmiary są równe
            for (unsigned int i = 0; i < expectedResult.size(); ++i)
            {
                EXPECT_EQ(stlResult[i], expectedResult[i]) << "Wynik STL rozni sie na indeksie " << i;
                EXPECT_EQ(boostResult[i], expectedResult[i]) << "Wynik Boost rozni sie na indeksie " << i;
                EXPECT_EQ(simpleResult[i], expectedResult[i]) << "Wynik Simple rozni sie na indeksie " << i;
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

} // namespace tests::Merge
