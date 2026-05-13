#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename TKey, typename TVal>
struct AVLNode 
{
    AVLNode* _left;
    AVLNode* _right;
    AVLNode* _parent;
    size_t _height;
    std::pair<TKey, TVal> _data;

    AVLNode(const TKey& key, const TVal& val, AVLNode* parent = nullptr): _left(nullptr), _right(nullptr), _parent(parent), _height(1), _data(key, val) {}
};

template<typename TKey, typename TVal>
class AVLTree 
{
private:
    AVLNode<TKey, TVal>* _root;
    size_t _size;

    int getHeight(AVLNode<TKey, TVal>* node) const
    {
        if (node == nullptr) 
        {
            return 0;
        }
        return static_cast<int>(node->_height);
    }

    void updateHeight(AVLNode<TKey, TVal>* node)
    {
        if (node == nullptr) 
        {
            return;
        }
        int leftH = getHeight(node->_left);
        int rightH = getHeight(node->_right);
        if (leftH > rightH) 
        {
            node->_height = 1 + leftH;
        }
        else 
        {
            node->_height = 1 + rightH;
        }
    }

    int balanceFactor(AVLNode<TKey, TVal>* node) const 
    {
        if (node == nullptr) 
        {
            return 0;
        }
        return getHeight(node->_left) - getHeight(node->_right);
    }

    AVLNode<TKey, TVal>* rightRotate(AVLNode<TKey, TVal>* P) 
    {
        AVLNode<TKey, TVal>* C = P->_left;
        AVLNode<TKey, TVal>* rightOfC = C->_right;

        C->_right = P;
        P->_left = rightOfC;

        if (rightOfC != nullptr) 
        {
            rightOfC->_parent = P;
        }
        C->_parent = P->_parent;
        P->_parent = C;

        updateHeight(P);
        updateHeight(C);

        return C;
    }

    AVLNode<TKey, TVal>* leftRotate(AVLNode<TKey, TVal>* P)
    {
        AVLNode<TKey, TVal>* C = P->_right;
        AVLNode<TKey, TVal>* leftOfC = C->_left;

        C->_left = P;
        P->_right = leftOfC;

        if (leftOfC != nullptr)
        {
            leftOfC->_parent = P;
        }
        C->_parent = P->_parent;
        P->_parent = C;

        updateHeight(P);
        updateHeight(C);

        return C;
    }
    AVLNode<TKey, TVal>* leftRightRotate(AVLNode<TKey, TVal>* G)
    {
        G->_left = leftRotate(G->_left);
        return rightRotate(G);
    }

    AVLNode<TKey, TVal>* rightLeftRotate(AVLNode<TKey, TVal>* G)
    {
        G->_right = rightRotate(G->_right);
        return leftRotate(G);
    }
    AVLNode<TKey, TVal>* balance(AVLNode<TKey, TVal>* node) 
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) 
        {
            if (balanceFactor(node->_left) < 0) 
            {
                return leftRightRotate(node);
            }
            return rightRotate(node);
        }
        if (bf < -1)
        {
            
            if (balanceFactor(node->_right) > 0) 
            {
                return rightLeftRotate(node);
            }
            return leftRotate(node);
        }

        return node;
    }

    AVLNode<TKey, TVal>* insertNode(AVLNode<TKey, TVal>* node, const TKey& key, const TVal& val, AVLNode<TKey, TVal>* parent) 
    {
        if (node == nullptr) 
        {
            return new AVLNode<TKey, TVal>(key, val, parent);
        }

        if (key < node->_data.first)
        {
            node->_left = insertNode(node->_left, key, val, node);
        }
        else if (key > node->_data.first) 
        {
            node->_right = insertNode(node->_right, key, val, node);
        }
        else 
        {
            return node;
        }

        return balance(node);
    }

    AVLNode<TKey, TVal>* findMin(AVLNode<TKey, TVal>* node) const 
    {
        if (node == nullptr) 
        {
            return nullptr;
        }
        while (node->_left != nullptr) 
        {
            node = node->_left;
        }
        return node;
    }

    AVLNode<TKey, TVal>* eraseNode(AVLNode<TKey, TVal>* node, const TKey& key) 
    {
        if (node == nullptr) 
        
        {
            return nullptr;
        }

        if (key < node->_data.first)
        {
            node->_left = eraseNode(node->_left, key);
        }
        else if (key > node->_data.first) 
        {
            node->_right = eraseNode(node->_right, key);
        }
        else 
        {
            
            if (node->_left == nullptr || node->_right == nullptr) 
            {
                AVLNode<TKey, TVal>* temp = nullptr;
                if (node->_left != nullptr) {
                    temp = node->_left;
                }
                else 
                {
                    temp = node->_right;
                }

                if (temp == nullptr) 
                {
                    
                    delete node;
                    return nullptr;
                }
                else 
                {
                    
                    temp->_parent = node->_parent;
                    delete node;
                    return temp;
                }
            }
            
            else 
            {
                AVLNode<TKey, TVal>* minNode = findMin(node->_right);
                node->_data = minNode->_data;
                node->_right = eraseNode(node->_right, minNode->_data.first);
            }
        }

        return balance(node);
    }

    void inorderCollect(AVLNode<TKey, TVal>* node, std::vector<std::pair<TKey, TVal>>& result) const {
        if (node == nullptr)
        {
            return;
        }
        inorderCollect(node->_left, result);
        result.push_back(node->_data);
        inorderCollect(node->_right, result);
    }

    void destroySubtree(AVLNode<TKey, TVal>* node)
    {
        if (node == nullptr) 
        {
            return;
        }
        destroySubtree(node->_left);
        destroySubtree(node->_right);
        delete node;
    }

public:
    AVLTree() : _root(nullptr), _size(0) {}

    ~AVLTree() 
    {
        destroySubtree(_root);
    }

    void insert(const TKey& key, const TVal& val) 
    {
        if (!contains(key)) 
        {
            _root = insertNode(_root, key, val, nullptr);
            _size++;
        }
    }

    TVal find(const TKey& key) const 
    {
        AVLNode<TKey, TVal>* cur = _root;
        while (cur != nullptr) 
        {
            if (key == cur->_data.first)
            {
                return cur->_data.second;
            }
            else if (key < cur->_data.first) 
            {
                cur = cur->_left;
            }
            else 
            {
                cur = cur->_right;
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool contains(const TKey& key) const
    {
        AVLNode<TKey, TVal>* cur = _root;
        while (cur != nullptr) 
        {
            if (key == cur->_data.first)
            {
                return true;
            }
            else if (key < cur->_data.first)
            {
                cur = cur->_left;
            }
            else 
            {
                cur = cur->_right;
            }
        }
        return false;
    }

    void erase(const TKey& key) 
    {
        if (contains(key)) 
        {
            _root = eraseNode(_root, key);
            _size--;
        }
    }

    size_t size() const
    {
        return _size;
    }

    bool isEmpty() const
    {
        return _size == 0;
    }

    std::vector<std::pair<TKey, TVal>> inorder() const 
    {
        std::vector<std::pair<TKey, TVal>> result;
        inorderCollect(_root, result);
        return result;
    }

    void print(std::ostream& out) const 
    {
        printNode(out, _root, 0);
    }

private:
    void printNode(std::ostream& out, AVLNode<TKey, TVal>* node, int level) const 
    {
        if (node == nullptr) 
        {
            return;
        }
        printNode(out, node->_right, level + 1);
        for (int i = 0; i < level; i++)
        {
            out << "    ";
        }
        out << node->_data.first << " : " << node->_data.second << std::endl;
        printNode(out, node->_left, level + 1);
    }
};
