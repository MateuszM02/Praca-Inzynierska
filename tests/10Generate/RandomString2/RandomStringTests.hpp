#pragma once

#include "../TestFixture.hpp"
#include "../../../src/10Generate/RandomString2/RandomStringFunctor.hpp"

namespace tests::Generate::RandomString2tests
{
class RandomStringTest : GenerateTestFixture<std::string>
{ 
public:
    void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<std::string>& args) override;
};
} // namespace tests::Generate::RandomString2tests
