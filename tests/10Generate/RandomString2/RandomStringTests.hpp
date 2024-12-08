#pragma once
#include "../GenerateTestFixture.hpp"
#include "../Path.hpp"
#include "../../../src/10Generate/RandomString2/RandomStringFunctor.hpp"

namespace tests::Generate::RandomString2tests
{

struct RandomStringArgs : public GenerateTestStruct<std::string>
{
    RandomStringArgs(const std::string& path, unsigned int l, unsigned int n);
    
    const unsigned int length;
};

class RandomStringFixture : public ::testing::TestWithParam<RandomStringArgs>
{ 
};

} // namespace tests::Generate::RandomString2tests
