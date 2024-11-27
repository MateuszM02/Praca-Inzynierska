#pragma once

#include "../../src/3Merge/Merger.hpp"

using namespace src::Merge;

namespace tests::Merge
{
// Klasa abstrakcyjna MergeTestFixture, po ktorej dziedzicza klasy testowe metod merge
template <class DataType> 
class MergeTestFixture 
{ 
public:
    virtual ~MergeTestFixture() = default;

    void runTest(
        Merger<DataType>& merger,
        const std::vector<DataType>& v1,
        const std::vector<DataType>& v2,
        const src::MethodType& methodType)
    {
        const std::vector<DataType>& result = merger.call(v1, v2, methodType);
        ;
    }
protected:
    virtual void createTest(
        const std::vector<DataType>& v1,
        const std::vector<DataType>& v2,
        const src::MethodType& methodType) = 0;
};
} // namespace tests::Merge
