#include "TreeTests.hpp"

namespace tests::Merge
{

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeArgs<DataType>::TreeArgs(
    const std::string& path,
    VectorStruct<TreeNode<DataType>> vectors)
: MergeTestStruct<TreeNode<DataType>>(
    path,
    std::make_shared<Tree<DataType>>(),
    std::move(vectors.v1),
    std::move(vectors.v2),
    std::move(vectors.expectedResult))
{ }

// TODO: Odkomentowac jak naprawie testy

// INSTANTIATE_TEST_SUITE_P(
//     IntTreePrefix,
//     IntTreeFixture,
//     ::testing::Values(
//         std::move(TreeArgs<int>(
//                     Path::Create(MergeTree, 1),
//                     std::move(IntTreeFixture::initTestData(
//                                 IntTreeFixture::fmod3i3,
//                                 IntTreeFixture::fmod9i64,
//                                 100,
//                                 100)))),
//         std::move(TreeArgs<int>(
//                     Path::Create(MergeTree, 2),
//                     std::move(IntTreeFixture::initTestData(
//                                 IntTreeFixture::fmod3i3,
//                                 IntTreeFixture::fmod9i64,
//                                 150,
//                                 50)))),
//         std::move(TreeArgs<int>(
//                     Path::Create(MergeTree, 3),
//                     std::move(IntTreeFixture::initTestData(
//                                 IntTreeFixture::fmod3i3,
//                                 IntTreeFixture::fmod9i64,
//                                 200,
//                                 200)))),
//         std::move(TreeArgs<int>(
//                     Path::Create(MergeTree, 4),
//                     std::move(IntTreeFixture::initTestData(
//                                 IntTreeFixture::fmod3i3,
//                                 IntTreeFixture::fmod9i64,
//                                 300,
//                                 100))))
//     ));

} // namespace tests::Merge
