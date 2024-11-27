#include "RandomStringTests.hpp"

namespace tests::Generate::RandomString2tests
{

RandomStringArgs::RandomStringArgs(
    unsigned int length,
    unsigned int n, 
    std::vector<std::string> v)
: functor{RandomString2::RandomStringFunctor(length)}
, GenerateTestStruct<std::string>(std::ref(functor), n, std::move(v))
{ }

TEST_P(RandomStringFixture, RandomStringTest) 
{ 
    const auto& args = GetParam(); 
    
    const std::vector<std::string>& stlResult = args.functorRef.call(args.number, src::MethodType::STL);
    const std::vector<std::string>& boostResult = args.functorRef.call(args.number, src::MethodType::Boost);
    const std::vector<std::string>& simpleResult = args.functorRef.call(args.number, src::MethodType::Simple);
    
    ASSERT_EQ(stlResult.size(), args.expectedResult.size()); 
    for (size_t i = 0; i < args.expectedResult.size(); ++i) 
    { 
        EXPECT_EQ(stlResult[i].size(), args.expectedResult[i].size()) << "Wynik STL rozni sie na indeksie " << i;
        EXPECT_EQ(boostResult[i].size(), args.expectedResult[i].size()) << "Wynik Boost rozni sie na indeksie " << i;
        EXPECT_EQ(simpleResult[i].size(), args.expectedResult[i].size()) << "Wynik Simple rozni sie na indeksie " << i; 
    }
}

// TODO: Naprawic aby widzialo TEST_P
INSTANTIATE_TEST_SUITE_P(
    RandomStringFixturePrefix, 
    RandomStringFixture,
    ::testing::Values( 
        RandomStringArgs(10, 10u, 
                        std::vector<std::string>{ "1", "1", "2", "3", "5", "8", "13", "21", "34", "59" }),
        RandomStringArgs(8, 9u,  
                        std::vector<std::string>{ "2", "2", "4", "6", "10", "16", "26", "42", "68"})
));

} // namespace tests::Generate::RandomString2tests
