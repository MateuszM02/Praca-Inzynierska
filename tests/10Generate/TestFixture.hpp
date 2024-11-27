#pragma once

#include "../../src/10Generate/Functor.hpp"
#include <gtest/gtest.h>

using namespace src::Generate;

namespace tests::Generate
{

template <typename DataType>
struct GenerateTestStruct
{
public:
    Functor<DataType>& functorRef;
    unsigned int number;
    std::vector<DataType> expectedResult;

    GenerateTestStruct(Functor<DataType>& f, unsigned int n, std::vector<DataType> v) 
    : functorRef{f} 
    , number{n} 
    , expectedResult{std::move(v)} 
    { }
};

// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <class DataType> 
class GenerateTestFixture : public ::testing::TestWithParam<GenerateTestStruct<DataType>>
{ 
public:
    void SetUp() override
    {
        std::cout << "Inside SetUp\n";
    }

    void VerifyTest(const GenerateTestStruct<DataType>& args)
    {
        const std::vector<DataType> stlResult = args.functorRef.call(args.number, src::MethodType::STL);
        const std::vector<DataType> boostResult = args.functorRef.call(args.number, src::MethodType::Boost);
        const std::vector<DataType> simpleResult = args.functorRef.call(args.number, src::MethodType::Simple);
        
        ASSERT_EQ(stlResult, args.expectedResult); 
        ASSERT_EQ(boostResult, args.expectedResult); 
        ASSERT_EQ(simpleResult, args.expectedResult);

        ASSERT_EQ(stlResult.size(), args.expectedResult.size()); 
        ASSERT_EQ(boostResult.size(), args.expectedResult.size()); 
        ASSERT_EQ(simpleResult.size(), args.expectedResult.size()); 
        
        for (unsigned int i = 0; i < args.expectedResult.size(); ++i) 
        { 
            EXPECT_EQ(stlResult[i], args.expectedResult[i]) << "Wynik STL rozni sie na indeksie " << i; 
            EXPECT_EQ(boostResult[i], args.expectedResult[i]) << "Wynik Boost rozni sie na indeksie " << i; 
            EXPECT_EQ(simpleResult[i], args.expectedResult[i]) << "Wynik Simple rozni sie na indeksie " << i; 
        }
    }
};
} // namespace tests::Generate
