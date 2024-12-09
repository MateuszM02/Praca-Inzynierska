#include "RandomStringTests.hpp"

namespace tests::Generate::RandomString2tests
{

RandomStringArgs::RandomStringArgs(
    const std::string& path,
    unsigned int l,
    unsigned int n)
: length{l}
, GenerateTestStruct<std::string>(
    path,
    std::make_shared<RandomString2::RandomStringFunctor>(RandomString2::RandomStringFunctor(l)), 
    n, {})
{ }

TEST_P(RandomStringFixture, RandomStringTest) 
{ 
    const RandomStringArgs args = GetParam();
    std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

    const std::vector<std::string>& stlResult = args.functorRef->callFunctor(args.number, src::MethodType::STL, os);
    const std::vector<std::string>& boostResult = args.functorRef->callFunctor(args.number, src::MethodType::Boost, os);
    const std::vector<std::string>& simpleResult = args.functorRef->callFunctor(args.number, src::MethodType::Simple, os);
    
    EXPECT_EQ(stlResult.size(), args.number) << "Rozmiar wyniku STL rozni sie od oczekiwanego."; 
    EXPECT_EQ(boostResult.size(), args.number) << "Rozmiar wyniku Boost rozni sie od oczekiwanego."; 
    EXPECT_EQ(simpleResult.size(), args.number) << "Rozmiar wyniku Simple rozni sie od oczekiwanego.";

    for (unsigned int i = 0; i < args.number; ++i) 
    { 
        EXPECT_EQ(stlResult[i].size(), args.length) << "Wynik STL rozni sie na indeksie " << i; 
        EXPECT_EQ(boostResult[i].size(), args.length) << "Wynik Boost rozni sie na indeksie " << i; 
        EXPECT_EQ(simpleResult[i].size(), args.length) << "Wynik Simple rozni sie na indeksie " << i; 
    }
}

INSTANTIATE_TEST_SUITE_P(
    RandomStringPrefix, 
    RandomStringFixture,
    ::testing::Values( // dlugosc slowa, ilosc slow
        RandomStringArgs(Path::Create(GenerateRandomString, 1), 1u, 1000000u),
        RandomStringArgs(Path::Create(GenerateRandomString, 2), 20u, 50000u),
        RandomStringArgs(Path::Create(GenerateRandomString, 3), 200u, 5000u),
        RandomStringArgs(Path::Create(GenerateRandomString, 4), 1000u, 1000u),
        RandomStringArgs(Path::Create(GenerateRandomString, 5), 5000u, 200u),
        RandomStringArgs(Path::Create(GenerateRandomString, 6), 50000u, 20u),
        RandomStringArgs(Path::Create(GenerateRandomString, 7), 1000000u, 1u)
));

} // namespace tests::Generate::RandomString2tests
