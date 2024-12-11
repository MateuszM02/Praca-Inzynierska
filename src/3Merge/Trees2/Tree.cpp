#include "Tree.hpp"

namespace src::Merge::Trees2
{

// TreeNode

// Konstruktor przenoszacy
template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNode<DataType>::TreeNode(TreeNode<DataType>&& other)
: value{std::move(other.value)}
, height{other.height}
, left{std::move(other.left)}
, right{std::move(other.right)}
{ }

// konstruktor kopiujacy
template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNode<DataType>::TreeNode(const TreeNode<DataType>& other)
: value{other.value}
, height{other.height}
, left{other.left}
, right{other.right}
{ }

// Operator przenoszacy
template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNode<DataType>& TreeNode<DataType>::operator=(const TreeNode<DataType>&& other)
{
    if (this != &other)
    {
        this->value = other.value;
        this->height = other.height;
        this->left = std::move(other.left);
        this->right = std::move(other.right);
    }
    return *this;
}

// Operator kopiujacy
template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNode<DataType>& TreeNode<DataType>::operator=(const TreeNode<DataType>& other)
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

template <typename DataType>
requires std::is_arithmetic_v<DataType>
bool TreeNode<DataType>::operator==(const TreeNode<DataType>& other) const
{
    if (!this->left && other.left) return false; 
    if (!this->right && other.right) return false; 
    if (this->left && !other.left) return false; 
    if (this->right && !other.right) return false;

    if (this->value != other.value || this->height != other.height)
        return false;
        
    auto leftPtr = this->left.get();
    auto rightPtr = this->right.get();

    return  (!leftPtr || *leftPtr == *(other.left.get())) &&
            (!rightPtr || *rightPtr == *(other.right.get()));
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
bool TreeNode<DataType>::operator<(const TreeNode<DataType>& other) const
{
    return this->getSum(this) < other.getSum(&other);
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
DataType TreeNode<DataType>::getSum(const TreeNode<DataType>* node) const 
{
    DataType sum = node->value;

    if (node->left)
       sum += getSum(node->left.get());
    if (node->right)
        sum = getSum(node->right.get());
    return sum;
}

// public Tree

template <typename DataType>
requires std::is_arithmetic_v<DataType>
void Tree<DataType>::insert(const DataType& value) 
{
    root = insertRec(std::move(root), value);
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
bool Tree<DataType>::find(const DataType& value) const 
{
    return findRec(root.get(), value);
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
void Tree<DataType>::remove(const DataType& value) 
{
    root = removeRec(std::move(root), value);
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNode<DataType> Tree<DataType>::getRoot() const 
{
    assert(this->root && "drzewo musi miec co najmniej 1 element");
    TreeNode<DataType> temp;
    temp = std::move(*this->root);
    return temp;
}

// private Tree

template <typename DataType>
requires std::is_arithmetic_v<DataType>
int Tree<DataType>::getHeight(const TreeNodePtr<DataType> node) const 
{
    return node ? node->height : 0;
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
int Tree<DataType>::getBalance(const TreeNodePtr<DataType> node) const 
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// rotacje

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNodePtr<DataType> Tree<DataType>::rightRotate(TreeNodePtr<DataType> y) 
{
    auto x = std::move(y->left);
    auto T2 = std::move(x->right);

    x->right = std::move(y);
    x->right->left = std::move(T2);

    x->right->height = std::max(getHeight(x->right->left), getHeight(x->right->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNodePtr<DataType> Tree<DataType>::leftRotate(TreeNodePtr<DataType> x) 
{
    auto y = std::move(x->right);
    auto T2 = std::move(y->left);

    y->left = std::move(x);
    y->left->right = std::move(T2);

    y->left->height = std::max(getHeight(y->left->left), getHeight(y->left->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// insert, find, delete

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNodePtr<DataType> Tree<DataType>::insertRec(TreeNodePtr<DataType> node, const DataType& value) 
{
    if (!node) 
    {
        return std::make_unique<TreeNode<DataType>>(value);
    }

    if (value < node->value) 
    {
        node->left = insertRec(std::move(node->left), value);
    } 
    else if (value > node->value) 
    {
        node->right = insertRec(std::move(node->right), value);
    } 
    else 
    {
        return node;
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->value) 
    {
        return rightRotate(std::move(node));
    }
    if (balance < -1 && value > node->right->value) 
    {
        return leftRotate(std::move(node));
    }
    if (balance > 1 && value > node->left->value) 
    {
        node->left = leftRotate(std::move(node->left));
        return rightRotate(std::move(node));
    }
    if (balance < -1 && value < node->right->value) 
    {
        node->right = rightRotate(std::move(node->right));
        return leftRotate(std::move(node));
    }

    return node;
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
TreeNodePtr<DataType> Tree<DataType>::removeRec(TreeNodePtr<DataType> node, const DataType& value) 
{
    if (!node) 
    {
        return nullptr;
    }

    if (value < node->value) 
    {
        node->left = removeRec(std::move(node->left), value);
    } 
    else if (value > node->value) 
    {
        node->right = removeRec(std::move(node->right), value);
    } 
    else 
    {
        if (!node->left) 
        {
            return std::move(node->right);
        } 
        else if (!node->right) 
        {
            return std::move(node->left);
        } 
        else 
        {
            const DataType& minValue = getMinValue(node->right.get());
            node->value = minValue;
            node->right = removeRec(std::move(node->right), minValue);
        }
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) 
    {
        return rightRotate(std::move(node));
    }
    if (balance > 1 && getBalance(node->left) < 0) 
    {
        node->left = leftRotate(std::move(node->left));
        return rightRotate(std::move(node));
    }
    if (balance < -1 && getBalance(node->right) <= 0) 
    {
        return leftRotate(std::move(node));
    }
    if (balance < -1 && getBalance(node->right) > 0) 
    {
        node->right = rightRotate(std::move(node->right));
        return leftRotate(std::move(node));
    }

    return node;
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
bool Tree<DataType>::findRec(const TreeNode<DataType>* node, const DataType& value) const 
{
    if (!node) 
    {
        return false;
    }
    else if (value == node->value) 
    {
        return true;
    } 
    else if (value < node->value) 
    {
        return findRec(node->left.get(), value);
    } 
    else 
    {
        return findRec(node->right.get(), value);
    }
}

template <typename DataType>
requires std::is_arithmetic_v<DataType>
DataType Tree<DataType>::getMinValue(const TreeNode<DataType>* node) const 
{
    assert(node && "nie mozna okreslic minimalnego elementu pustego drzewa");
    while (node->left)
    {
        node = node->left.get();
    }
    return node->value;
}

template class TreeNode<int>;
template class Tree<int>;

} // namespace src::Merge::Trees2
