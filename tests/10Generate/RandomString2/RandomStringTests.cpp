#include "RandomStringTests.hpp"

namespace tests::Generate::RandomString2tests
{

RandomStringArgs::RandomStringArgs(
    unsigned int l,
    unsigned int n)
: length{l}
, GenerateTestStruct<std::string>(
    std::make_shared<RandomString2::RandomStringFunctor>(RandomString2::RandomStringFunctor(l)), 
    n, {})
{ }

TEST_P(RandomStringFixture, RandomStringTest) 
{ 
    const RandomStringArgs args = GetParam();
    
    const std::vector<std::string>& stlResult = args.functorRef->call(args.number, src::MethodType::STL);
    const std::vector<std::string>& boostResult = args.functorRef->call(args.number, src::MethodType::Boost);
    const std::vector<std::string>& simpleResult = args.functorRef->call(args.number, src::MethodType::Simple);
    
    ASSERT_EQ(stlResult.size(), args.number);
    ASSERT_EQ(boostResult.size(), args.number);
    ASSERT_EQ(simpleResult.size(), args.number);

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
        RandomStringArgs(1u, 1000000u),
        RandomStringArgs(20u, 50000u),
        RandomStringArgs(200u, 5000u),
        RandomStringArgs(1000u, 1000u),
        RandomStringArgs(5000u, 200u),
        RandomStringArgs(50000u, 20u),
        RandomStringArgs(1000000u, 1u)
));

} // namespace tests::Generate::RandomString2tests
