#pragma once
#include "../MergeTestFixture.hpp"
#include "../../../src/3Merge/Trees2/Tree.hpp"

namespace tests::Merge::Tree2tests
{
template <class DataType>
class TreeTest : MergeTestFixture<DataType>
{ 
public:
    void createTest(
        const std::vector<Trees2::TreeNode<DataType>>& v1,
        const std::vector<Trees2::TreeNode<DataType>>& v2,
        const src::MethodType& methodType) override;
};
} // namespace tests::Merge::Tree2tests
