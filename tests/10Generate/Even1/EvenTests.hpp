#pragma once

#include "../TestFixture.hpp"
#include "../../../src/10Generate/Even1/EvenFunctor.hpp"

namespace tests::Generate::Even1tests
{
class EvenTest : GenerateTestFixture<unsigned int>
{ 
public:
    void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<unsigned int>& args) override;
};
} // namespace tests::Generate::Even1tests
