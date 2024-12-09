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

    // konstruktor kopiujacy potrzebny do testowania
    TreeNode(const TreeNode<DataType>& other)
    {
        value = other.value;
        height = other.height;
        left = std::make_unique<TreeNode<DataType>>(*other.left.get());
        right = std::make_unique<TreeNode<DataType>>(*other.right.get());
    }

    bool operator==(const TreeNode<DataType>& other) const
    {
        return  this->value == other.value &&
                this->height == other.height &&
                *(this->left.get()) == *(other.left.get()) &&
                *(this->left.get()) == *(other.left.get());
    }

    // operator porownania - wysokosc drzewa
    bool operator<(const TreeNode<DataType>& other) const
    {
        return this->height < other.height;
    }

    DataType value;
    int height;
    std::unique_ptr<TreeNode<DataType>> left;
    std::unique_ptr<TreeNode<DataType>> right;
};

template <typename DataType>
using TreeNodePtr = std::unique_ptr<TreeNode<DataType>>;

template <typename DataType>
class Tree : public Merger<TreeNode<DataType>> 
{
public:
    void insert(const DataType& value);
    bool find(const DataType& value) const;
    void remove(const DataType& value);

private:
    TreeNodePtr<DataType> root;

    int getHeight(TreeNode<DataType>* node) const;
    int getBalance(TreeNode<DataType>* node) const;

    TreeNodePtr<DataType> rightRotate(TreeNodePtr<DataType> y);
    TreeNodePtr<DataType> leftRotate(TreeNodePtr<DataType> x);

    TreeNodePtr<DataType> insertRec(TreeNodePtr<DataType> node, const DataType& value);
    TreeNodePtr<DataType> removeRec(TreeNodePtr<DataType> node, const DataType& value);
    
    bool findRec(const TreeNode<DataType>* node, const DataType& value) const;
    TreeNode<DataType>* getMinNode(TreeNode<DataType>* node) const;
};

} // namespace src::Merge::Trees2
