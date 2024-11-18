#pragma once

#include "../../src/10RepeatFun/Functor.hpp"

using namespace src::RepeatFun;

namespace tests::RepeatFun
{
// Klasa abstrakcyjna FunctorTestFixture, po ktorej dziedzicza klasy testowe funktorow
template <class DataType> 
class FunctorTestFixture 
{ 
public:
    virtual ~FunctorTestFixture() = default;

    void runTest(
        Functor<DataType>& functor,
        const unsigned int n,
        const src::MethodType& methodType)
    {
        const std::vector<DataType>& result = functor.call(n, methodType);
        ;
    }
protected:
    virtual void createTest(
        const unsigned int n,
        const src::MethodType& methodType,
        const std::vector<DataType>& args) = 0;
};
} // namespace tests::RepeatFun