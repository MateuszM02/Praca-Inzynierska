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
        const VectorStruct<Trees2::TreeNode<DataType>>& vectors);
};

template <typename DataType>
requires std::is_arithmetic_v<DataType>
class TreeFixture : public MergeTestFixture<Trees2::TreeNode<DataType>>
{
public:
    static VectorStruct<Trees2::TreeNode<DataType>> initTrees(
        std::function<Trees2::TreeNode<DataType>(const unsigned int)> fun1,
        std::function<Trees2::TreeNode<DataType>(const unsigned int)> fun2,
        const int n1,
        const int n2)
    {
        std::vector<Trees2::TreeNode<DataType>> v1;
        std::vector<Trees2::TreeNode<DataType>> v2;
        std::vector<Trees2::TreeNode<DataType>> expectedResult;
        v1.reserve(n1);
        v2.reserve(n2);
        expectedResult.reserve(n1 + n2);

        for (int i = 1; i <= n1; ++i)
        {
            v1.push_back(fun1(i));
        }
        for (int i = 1; i <= n2; ++i)
        {
            v2.push_back(fun2(i));
        }

        int x1 = 1;
        int x2 = 1;
        Trees2::TreeNode<DataType> p1 = fun1(x1);
        Trees2::TreeNode<DataType> p2 = fun2(x2);

        while (x1 <= n1 && x2 <= n2)
        {
            if (p1 < p2)
            {
                expectedResult.push_back(p1);
                ++x1;
                p1 = fun1(x1);
            }
            else
            {
                expectedResult.push_back(p2);
                ++x2;
                p2 = fun2(x2);
            }
        }
        while (x1 <= n1)
        {
            expectedResult.push_back(p1);
            ++x1;
            p1 = fun1(x1);
        }
        while (x2 <= n2)
        {
            expectedResult.push_back(p2);
            ++x2;
            p2 = fun2(x2);
        }

        return { v1, v2, expectedResult };
    }

    static Trees2::TreeNode<DataType> generateTree(
        std::function<DataType(const unsigned int)> nodeCreator,
        const unsigned int n)
    {
        // Korzen drzewa
        std::shared_ptr<Trees2::TreeNode<DataType>> root = 
            std::make_shared<Trees2::TreeNode<DataType>>(
                Trees2::TreeNode<DataType>(nodeCreator(0)));

        // Wektor wezlow do przetworzenia
        std::vector<std::shared_ptr<Trees2::TreeNode<DataType>>> nodes;
        nodes.push_back(root); 
        
        for (int i = 1; i < n; ++i)
        {
            std::shared_ptr<Trees2::TreeNode<DataType>> node = 
                std::make_shared<Trees2::TreeNode<DataType>>(
                    Trees2::TreeNode<DataType>(nodeCreator(i)));
            std::shared_ptr<Trees2::TreeNode<DataType>> parent = nodes[(i - 1) / 2];
            
            if (!parent->left)
            {
                parent->left = node;
            }
            else
            {
                parent->right = node;
            }
            nodes.push_back(node);
        }
        return *(root.get());
    }

    static Trees2::TreeNode<DataType> fmod3i3(const unsigned int n)
    {
        assert(n >= 1 && "drzewo musi miec co najmniej 1 element");

        auto nodeCreator = [](const unsigned int index) -> DataType
        {
            return static_cast<DataType>(3 * index + (index % 3));
        };

        return generateTree(nodeCreator, n);
    }

    static Trees2::TreeNode<DataType> fmod9i64(const unsigned int n)
    {
        assert(n >= 1 && "drzewo musi miec co najmniej 1 element");

        auto nodeCreator = [](const unsigned int index) -> DataType
        {
            return static_cast<DataType>(9 * index % 64);
        };

        return generateTree(nodeCreator, n);
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
