#pragma once
#include "../Merger.hpp"

#include <memory> // std::unique_ptr

// Przyklad 2. Glebokosc drzewa -----------------------------------------------------------------------------

namespace src::Merge::Trees2 
{

template <typename DataType>
class TreeNode 
{
public:
    TreeNode(const DataType& v) 
    : value{v}
    , height{1}
    , left{nullptr}
    , right{nullptr}
    { }

    DataType value;
    int height;
    std::unique_ptr<TreeNode<DataType>> left;
    std::unique_ptr<TreeNode<DataType>> right;
};

template <typename DataType>
class Tree : public Merger<TreeNode<DataType>> 
{
public:
    Tree() : root{nullptr} { }

    bool operator()(const TreeNode<DataType>& tree1, const TreeNode<DataType>& tree2) override;

    void insert(const DataType& value);
    bool find(const DataType& value) const;
    void remove(const DataType& value);

private:
    #define TreeNodePtr std::unique_ptr<TreeNode<DataType>>

    TreeNodePtr root;

    int getHeight(TreeNode<DataType>* node) const;
    int getBalance(TreeNode<DataType>* node) const;

    TreeNodePtr rightRotate(TreeNodePtr y);
    TreeNodePtr leftRotate(TreeNodePtr x);

    TreeNodePtr insertRec(TreeNodePtr node, const DataType& value);
    bool findRec(const TreeNode<DataType>* node, const DataType& value) const;
    TreeNodePtr removeRec(TreeNodePtr node, const DataType& value);
    TreeNode<DataType>* getMinNode(TreeNode<DataType>* node) const;
};

} // namespace src::Merge::Trees2
