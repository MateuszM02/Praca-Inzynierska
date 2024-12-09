#pragma once
#include "../../src/3Merge/Merger.hpp"

#include <fstream>
#include <gtest/gtest.h>

using namespace src::Merge;

namespace tests::Merge
{

template <Comparable DataType>
struct MergeTestStruct
{
public:
    const std::string filePath;
    std::shared_ptr<Merger<DataType>> mergerRef;
    const std::vector<DataType> expectedResult;

    MergeTestStruct(
        const std::string& path,
        std::shared_ptr<Merger<DataType>> f,
        const std::vector<DataType>& result)
    : filePath{path}
    , mergerRef{f}
    , expectedResult{result}
    { }
};

// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <Comparable DataType>
class MergeTestFixture : public ::testing::TestWithParam<MergeTestStruct<DataType>>
{
public:
    void VerifyTest(const MergeTestStruct<DataType>& args)
    {
        std::ostringstream os; // Użycie ostringstream do wypisywania wyników testów

        const std::vector<DataType>& stlResult = args.mergerRef->callMerger(src::MethodType::STL, os);
        const std::vector<DataType>& boostResult = args.mergerRef->callMerger(src::MethodType::Boost, os);
        const std::vector<DataType> simpleResult = args.mergerRef->callMerger(src::MethodType::Simple, os);

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
