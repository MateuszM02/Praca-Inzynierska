#pragma once
#include "../../src/Algorithms/Merger.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;

namespace tests::Merge
{

template <Comparable DataType>
struct VectorStruct
{
    VectorStruct(
        std::vector<DataType> vec1,
        std::vector<DataType> vec2,
        std::vector<DataType> result)
    : v1{std::move(vec1)}
    , v2{std::move(vec2)}
    , expectedResult{std::move(result)}
    { }

    VectorStruct(VectorStruct&& other)
    : v1{std::move(other.v1)}
    , v2{std::move(other.v2)}
    , expectedResult{std::move(other.expectedResult)}
    { }

    std::vector<DataType> v1;
    std::vector<DataType> v2;
    std::vector<DataType> expectedResult;
};

template <Comparable DataType>
struct MergeTestStruct
{
public:
    MergeTestStruct(
        const std::string& path,
        const std::shared_ptr<Merger<DataType>>& f,
        std::vector<DataType> vec1,
        std::vector<DataType> vec2,
        std::vector<DataType> result)
    : filePath{std::move(path)}
    , mergerRef{std::move(f)}
    , v1{std::move(vec1)}
    , v2{std::move(vec2)}
    , expectedResult{std::move(result)}
    { }

    MergeTestStruct(const MergeTestStruct& other)
    : filePath{other.filePath}
    , mergerRef{other.mergerRef}
    , v1{other.v1}
    , v2{other.v2}
    , expectedResult{other.expectedResult}
    { }
    
    MergeTestStruct(MergeTestStruct&& other)
    : filePath{std::move(other.filePath)}
    , mergerRef{std::move(other.mergerRef)}
    , v1{std::move(other.v1)}
    , v2{std::move(other.v2)}
    , expectedResult{std::move(other.expectedResult)}
    { }

    const std::string filePath;
    const std::shared_ptr<Merger<DataType>> mergerRef;

    const std::vector<DataType> v1;
    const std::vector<DataType> v2;
    const std::vector<DataType> expectedResult;
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <Comparable DataType>
class MergeTestFixture : public ::testing::TestWithParam<MergeTestStruct<DataType>>
{
public:
    static VectorStruct<DataType> initTestData(
        const std::function<DataType(const unsigned int)>& fun1,
        const std::function<DataType(const unsigned int)>& fun2, 
        const unsigned int n1,
        const unsigned int n2)
    {
        std::vector<DataType> v1;
        std::vector<DataType> v2;
        std::vector<DataType> expectedResult;
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
        DataType p1 = fun1(x1);
        DataType p2 = fun2(x2);

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

        const std::vector<DataType>& stlResult = args.mergerRef->callMerger(
            src::MethodType::STL, args.v1, args.v2, os);
        const std::vector<DataType>& boostResult = args.mergerRef->callMerger(
            src::MethodType::Boost, args.v1, args.v2, os);
        const std::vector<DataType>& simpleResult = args.mergerRef->callMerger(
            src::MethodType::Simple, args.v1, args.v2, os);

        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();
        
        EXPECT_EQ(stlResult.size(), args.expectedResult.size()) << "Rozmiar wyniku STL rozni sie od oczekiwanego.";
        EXPECT_EQ(boostResult.size(), args.expectedResult.size()) << "Rozmiar wyniku Boost rozni sie od oczekiwanego.";
        EXPECT_EQ(simpleResult.size(), args.expectedResult.size()) << "Rozmiar wyniku Simple rozni sie od oczekiwanego.";

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

} // namespace tests::Merge
