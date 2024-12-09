#pragma once
#include "../Merger.hpp"

// Przyklad 2. Glebokosc drzewa -----------------------------------------------------------------------------

namespace src::Merge::Trees2
{

template <typename DataType>
requires std::is_arithmetic_v<DataType>
class TreeNode
{
public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    TreeNode()
    : value{DataType()}
    , height{0}
    , left{nullptr}
    , right{nullptr}
    { }

    TreeNode(const DataType& v) 
    : value{v}
    , height{1}
    , left{nullptr}
    , right{nullptr}
    { }

    // Operator przypisania potrzebny do scalania
    TreeNode& operator=(const TreeNode& other)
    {
        if (this != &other)
        {
            this->value = other.value;
            this->height = other.height;
            this->left = other.left;
            this->right = other.right;
        }
        return *this;
    }

    bool operator==(const TreeNode<DataType>& other) const
    {
        if (!this->left && other.left) return false; 
        if (!this->right && other.right) return false; 
        if (this->left && !other.left) return false; 
        if (this->right && !other.right) return false;

        return  this->value == other.value &&
                this->height == other.height &&
                (!this->left || *(this->left.get()) == *(other.left.get())) &&
                (!this->right || *(this->right.get()) == *(other.right.get()));
    }

    // operator porownania - wysokosc drzewa
    bool operator<(const TreeNode<DataType>& other) const
    {
        return this->value < other.value; //this->height < other.height;
    }

    DataType value;
    int height;
    std::shared_ptr<TreeNode<DataType>> left;
    std::shared_ptr<TreeNode<DataType>> right;
};

template <typename DataType>
requires std::is_arithmetic_v<DataType>
using TreeNodePtr = std::shared_ptr<TreeNode<DataType>>;

template <typename DataType>
requires std::is_arithmetic_v<DataType>
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
