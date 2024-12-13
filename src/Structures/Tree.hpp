#pragma once
#include "../Algorithms/Merger.hpp"

#include <cassert>

using namespace src::Algorithms;

namespace src::Structures
{

template <typename DataType>
requires std::is_arithmetic_v<DataType>
struct TreeNode
{
    DataType value;
    int height;
    std::shared_ptr<TreeNode<DataType>> left;
    std::shared_ptr<TreeNode<DataType>> right;

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

    // konstruktor/operator przypisania przenoszacego
    TreeNode(TreeNode<DataType>&& other);
    TreeNode<DataType>& operator=(const TreeNode<DataType>&& other);

    // konstruktor/operator przypisania kopiujacego
    TreeNode(const TreeNode<DataType>& other);
    TreeNode<DataType>& operator=(const TreeNode<DataType>& other);
    
    // operatory potrzebne do scalania/sortowania
    bool operator==(const TreeNode<DataType>& other) const;
    bool operator<(const TreeNode<DataType>& other) const;
    DataType getSum(const TreeNode<DataType>* node) const;
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

    TreeNode<DataType> getRoot() const;

private:
    TreeNodePtr<DataType> root;

    int getHeight(const TreeNodePtr<DataType> node) const;
    int getBalance(const TreeNodePtr<DataType> node) const;

    TreeNodePtr<DataType> rightRotate(TreeNodePtr<DataType> y);
    TreeNodePtr<DataType> leftRotate(TreeNodePtr<DataType> x);

    TreeNodePtr<DataType> insertRec(TreeNodePtr<DataType> node, const DataType& value);
    TreeNodePtr<DataType> removeRec(TreeNodePtr<DataType> node, const DataType& value);
    
    bool findRec(const TreeNode<DataType>* node, const DataType& value) const;
    DataType getMinValue(const TreeNode<DataType>* node) const;
};

} // namespace src::Structures
