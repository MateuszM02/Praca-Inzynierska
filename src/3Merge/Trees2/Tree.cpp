#include "Tree.hpp"

namespace src::Merge::Trees2
{

// public

template <typename DataType>
void Tree<DataType>::insert(const DataType& value) 
{
    root = insertRec(std::move(root), value);
}

template <typename DataType>
bool Tree<DataType>::find(const DataType& value) const 
{
    return findRec(root.get(), value);
}

template <typename DataType>
void Tree<DataType>::remove(const DataType& value) 
{
    root = removeRec(std::move(root), value);
}

// private

template <typename DataType>
int Tree<DataType>::getHeight(TreeNode<DataType>* node) const 
{
    return node ? node->height : 0;
}

template <typename DataType>
int Tree<DataType>::getBalance(TreeNode<DataType>* node) const 
{
    return node ? getHeight(node->left.get()) - getHeight(node->right.get()) : 0;
}

// rotacje

template <typename DataType>
TreeNodePtr<DataType> Tree<DataType>::rightRotate(TreeNodePtr<DataType> y) 
{
    auto x = std::move(y->left);
    auto T2 = std::move(x->right);

    x->right = std::move(y);
    x->right->left = std::move(T2);

    x->right->height = std::max(getHeight(x->right->left.get()), getHeight(x->right->right.get())) + 1;
    x->height = std::max(getHeight(x->left.get()), getHeight(x->right.get())) + 1;

    return x;
}

template <typename DataType>
TreeNodePtr<DataType> Tree<DataType>::leftRotate(TreeNodePtr<DataType> x) 
{
    auto y = std::move(x->right);
    auto T2 = std::move(y->left);

    y->left = std::move(x);
    y->left->right = std::move(T2);

    y->left->height = std::max(getHeight(y->left->left.get()), getHeight(y->left->right.get())) + 1;
    y->height = std::max(getHeight(y->left.get()), getHeight(y->right.get())) + 1;

    return y;
}

// insert, find, delete

template <typename DataType>
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

    node->height = std::max(getHeight(node->left.get()), getHeight(node->right.get())) + 1;

    int balance = getBalance(node.get());

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
            TreeNode<DataType>* minNode = getMinNode(node->right.get());
            node->value = minNode->value;
            node->right = removeRec(std::move(node->right), minNode->value);
        }
    }

    node->height = std::max(getHeight(node->left.get()), getHeight(node->right.get())) + 1;

    int balance = getBalance(node.get());

    if (balance > 1 && getBalance(node->left.get()) >= 0) 
    {
        return rightRotate(std::move(node));
    }
    if (balance > 1 && getBalance(node->left.get()) < 0) 
    {
        node->left = leftRotate(std::move(node->left));
        return rightRotate(std::move(node));
    }
    if (balance < -1 && getBalance(node->right.get()) <= 0) 
    {
        return leftRotate(std::move(node));
    }
    if (balance < -1 && getBalance(node->right.get()) > 0) 
    {
        node->right = rightRotate(std::move(node->right));
        return leftRotate(std::move(node));
    }

    return node;
}

template <typename DataType>
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
TreeNode<DataType>* Tree<DataType>::getMinNode(TreeNode<DataType>* node) const 
{
    if (!node) return node;
    while (node->left) 
    {
        node = node->left.get();
    }
    return node;
}

template class TreeNode<int>;
template class Tree<int>;

} // namespace src::Merge::Trees2
