#pragma once
#include "../GenerateTestFixture.hpp"
#include "../../Path.hpp"

using namespace src::Structures;

namespace tests::Generate
{

struct RandomStringArgs : public GenerateTestStruct<std::string, RandomString>
{
    RandomStringArgs(const std::string& path, const unsigned int l, const unsigned int n);
    
    const unsigned int length;
};

class RandomStringFixture : public ::testing::TestWithParam<RandomStringArgs>
{ 
};

} // namespace tests::Generate
