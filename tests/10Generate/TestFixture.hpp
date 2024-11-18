#pragma once

#include "../../src/10Generate/Functor.hpp"

using namespace src::Generate;

namespace tests::Generate
{
// Klasa abstrakcyjna GenerateTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <class DataType> 
class GenerateTestFixture 
{ 
public:
    virtual ~GenerateTestFixture() = default;

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
} // namespace tests::Generate
