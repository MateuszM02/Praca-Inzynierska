#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/3Merge/Vector3/IntVector.hpp"

namespace tests::Merge::Vector3tests
{
class VectorTest : MergeTestFixture<std::vector<int>>
{ 
public:
    void createTest(
        const std::vector<std::vector<int>>& v1,
        const std::vector<std::vector<int>>& v2,
        const src::MethodType& methodType) override;
};
} // namespace tests::Merge::Vector3tests
