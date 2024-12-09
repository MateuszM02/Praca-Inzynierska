#include "TreeTests.hpp"

namespace tests::Merge::Tree2tests
{

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeArgs<DataType>::TreeArgs(
    const std::string& path,
    const VectorStruct<Trees2::TreeNode<DataType>>& vectors)
: MergeTestStruct<Trees2::TreeNode<DataType>>(
    path,
    std::make_shared<Trees2::Tree<DataType>>(),
    vectors)
{ }

// TODO: Odkomentowac jak naprawie testy

// INSTANTIATE_TEST_SUITE_P(
//     IntTreePrefix,
//     IntTreeFixture,
//     ::testing::Values(
//         TreeArgs<int>(
//             Path::Create(MergeTree, 1),
//             IntTreeFixture::initTrees(IntTreeFixture::fmod3i3, IntTreeFixture::fmod9i64, 30, 20)),
//         TreeArgs<int>(
//             Path::Create(MergeTree, 2),
//             IntTreeFixture::initTrees(IntTreeFixture::fmod3i3, IntTreeFixture::fmod9i64, 70, 30)),
//         TreeArgs<int>(
//             Path::Create(MergeTree, 3),
//             IntTreeFixture::initTrees(IntTreeFixture::fmod3i3, IntTreeFixture::fmod9i64, 400, 100))
//     ));

} // namespace tests::Merge::Tree2tests
