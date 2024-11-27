#include "TreeTests.hpp"

namespace tests::Merge::Tree2tests
{
template <typename DataType>
void TreeTest<DataType>::createTest(
    const std::vector<Trees2::TreeNode<DataType>>& v1,
    const std::vector<Trees2::TreeNode<DataType>>& v2,
    const src::MethodType& methodType)
{
    auto merger = Trees2::Tree<DataType>();
    runTest(merger, v1, v2, methodType);
}
} // namespace tests::Merge::Tree2tests
