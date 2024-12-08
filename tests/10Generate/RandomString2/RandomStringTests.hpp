#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../../src/10Generate/RandomString2/RandomStringFunctor.hpp"

namespace tests::Generate::RandomString2tests
{

struct RandomStringArgs : public GenerateTestStruct<std::string>
{
    RandomStringArgs(unsigned int l, unsigned int n);
    
    unsigned int length;
};

class RandomStringFixture : public ::testing::TestWithParam<RandomStringArgs>
{ 
};

} // namespace tests::Generate::RandomString2tests
