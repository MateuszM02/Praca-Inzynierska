#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"

using namespace src::Structures;

namespace tests::Generate
{

struct RandomStringArgs : public GenerateTestStruct<std::string, RandomString>
{
    RandomStringArgs(const unsigned int l, const unsigned int n)
    : length{l}
    , GenerateTestStruct<std::string, RandomString>(
        this->createPath(GenerateRandomString),
        std::move(src::Algorithms::GeneratorImpl::createRandomStringGenerator(n, l)))
    { }
    
    const unsigned int length;
};

class RandomStringFixture : public ::testing::TestWithParam<RandomStringArgs>
{ 
};

TEST_P(RandomStringFixture, RandomStringTest) 
{
    const RandomStringArgs args = GetParam();
    std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

    const std::vector<std::string>& stlResult = args.ref_->call(src::MethodType::STL, os);
    const std::vector<std::string>& boostResult = args.ref_->call(src::MethodType::Boost, os);
    const std::vector<std::string>& simpleResult = args.ref_->call(src::MethodType::Simple, os);
    
    const unsigned int size = args.ref_->size();

    EXPECT_EQ(stlResult.size(), size) << "Rozmiar wyniku STL rozni sie od oczekiwanego."; 
    EXPECT_EQ(boostResult.size(), size) << "Rozmiar wyniku Boost rozni sie od oczekiwanego."; 
    EXPECT_EQ(simpleResult.size(), size) << "Rozmiar wyniku Simple rozni sie od oczekiwanego.";

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
        
        // Petla for do porownywania wynikow, jesli rozmiary sa rowne
        for (unsigned int i = 0; i < size; ++i)
        {
            EXPECT_EQ(stlResult[i].size(), args.length) << "Wynik STL rozni sie na indeksie " << i; 
            EXPECT_EQ(boostResult[i].size(), args.length) << "Wynik Boost rozni sie na indeksie " << i; 
            EXPECT_EQ(simpleResult[i].size(), args.length) << "Wynik Simple rozni sie na indeksie " << i; 
        }
        outFile << os.str();
        outFile.close();
    }
    else
    {
        std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath_ << "\n";
    }
}

} // namespace tests::Generate
