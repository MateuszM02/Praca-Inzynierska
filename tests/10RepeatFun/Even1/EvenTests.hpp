#pragma once

#include "../TestFixture.hpp"
#include "../../../src/10RepeatFun/Even1/EvenFunctor.hpp"

namespace tests::RepeatFun::Even1tests
{
class EvenTest : FunctorTestFixture<unsigned int>
{ 
public:
    void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<unsigned int>& args) override;
};
} // namespace tests::RepeatFun::Even1tests
