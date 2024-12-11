#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/3Merge/Trees2/Tree.hpp"

#include <gtest/gtest.h>

namespace tests::Merge::Tree2tests
{

template <typename DataType>
requires std::is_arithmetic_v<DataType>
struct TreeArgs : public MergeTestStruct<Trees2::TreeNode<DataType>>
{
    TreeArgs(
        const std::string& path,
        VectorStruct<Trees2::TreeNode<DataType>> vectors);
};

template <typename DataType>
requires std::is_arithmetic_v<DataType>
class TreeFixture : public MergeTestFixture<Trees2::TreeNode<DataType>>
{
public:
    static Trees2::TreeNode<DataType> generateTree(
        const std::function<DataType(const unsigned int)>& nodeCreator,
        const unsigned int n)
    {
        Trees2::Tree<DataType> tree;
        for (unsigned int i = 1; i <= n; ++i)
        {
            tree.insert(nodeCreator(i));
        }
        return tree.getRoot();
    }

    static DataType fmod3i3nodeCreator(const unsigned int index)
    {
        return static_cast<DataType>(3 * index + (index % 3));
    }

    static Trees2::TreeNode<DataType> fmod3i3(const unsigned int n)
    {
        assert(n >= 1 && "drzewo musi miec co najmniej 1 element");
        return generateTree(fmod3i3nodeCreator, n);
    }

    static DataType fmod9i64nodeCreator(const unsigned int index)
    {
        return static_cast<DataType>(9 * index % 64);
    }

    static Trees2::TreeNode<DataType> fmod9i64(const unsigned int n)
    {
        assert(n >= 1 && "drzewo musi miec co najmniej 1 element");
        return generateTree(fmod9i64nodeCreator, n);
    }
};

class IntTreeFixture : public TreeFixture<int>
{
};

TEST_P(IntTreeFixture, intTreeTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Merge::Tree2tests
