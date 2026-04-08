#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
template<typename TKey, typename TValue>
struct Node
{
    std::pair<TKey, TValue> data;
    Node* left;
    Node* right;

    Node(TKey k, TValue v) : data({ k, v }), left(nullptr), right(nullptr) {}
};

template<typename TKey, typename TValue>
class BSTree
{
private:
    Node<TKey, TValue>* _root;
    int _size;

    void clear_recursive(Node<TKey, TValue>* node);
    Node<TKey, TValue>* find_min(Node<TKey, TValue>* node);
    Node<TKey, TValue>* find_max(Node<TKey, TValue>* node);
    Node<TKey, TValue>* erase_recursive(Node<TKey, TValue>* node, const TKey& key);
    Node<TKey, TValue>* find_node(const TKey& key) const;

public:
    BSTree() : _root(nullptr), _size(0) {}
    ~BSTree() 
    {
        clear_recursive(_root);
    }
    void insert(const TKey& key, const TValue& value);
    TValue& find(const TKey& key);
    void erase(const TKey& key);
    bool is_empty() const noexcept 
    {
        return _root == nullptr; 
    }
    int size() const noexcept 
    {
        return _size;
    }
    bool contains(const TKey& key) const noexcept;

    std::string to_string(bool sorted = false) const noexcept;
};

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::clear_recursive(Node<TKey, TValue>* node)
{
    if (node == nullptr) return;
    clear_recursive(node->left);
    clear_recursive(node->right);
    delete node;
}
template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_node(const TKey& key) const
{
    if (is_empty()) return nullptr;

    Node<TKey, TValue>* cur = _root;
    while (cur != nullptr)
    {
        if (cur->data.first == key)
            return cur;
        else if (key < cur->data.first)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return nullptr;
}
template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_min(Node<TKey, TValue>* node)
{
    if (node == nullptr) return nullptr;
    while (node->left != nullptr)
        node = node->left;
    return node;
}
template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_max(Node<TKey, TValue>* node)
{
    if (node == nullptr) return nullptr;
    while (node->right != nullptr)
        node = node->right;
    return node;
}
template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::erase_recursive(Node<TKey, TValue>* node, const TKey& key)
{
    if (node == nullptr)
        throw std::logic_error("Key not found");

    if (key < node->data.first)
    {
        node->left = erase_recursive(node->left, key);
    }
    else if (key > node->data.first)
    {
        node->right = erase_recursive(node->right, key);
    }
    else
    {
        
        if (node->left == nullptr && node->right == nullptr)
        {
            
            delete node;
            _size--;
            return nullptr;
        }
        else if (node->left == nullptr)
        {
            Node<TKey, TValue>* temp = node->right;
            delete node;
            _size--;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node<TKey, TValue>* temp = node->left;
            delete node;
            _size--;
            return temp;
        }
        else
        {
            Node<TKey, TValue>* max_left = find_max(node->left);
            node->data = max_left->data;
            node->left = erase_recursive(node->left, max_left->data.first);
        }
    }
    return node;
}
template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value)
{
    if (is_empty())
    {
        _root = new Node<TKey, TValue>(key, value);
        _size++;
        return;
    }

    Node<TKey, TValue>* cur = _root;
    Node<TKey, TValue>* parent = nullptr;

    while (cur != nullptr)
    {
        if (cur->data.first == key)
        {
            cur->data.second = value;
            return;
        }

        parent = cur;
        if (key < cur->data.first)
            cur = cur->left;
        else
            cur = cur->right;
    }

    Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key, value);
    if (key < parent->data.first)
        parent->left = new_node;
    else
        parent->right = new_node;
    _size++;
}
template<typename TKey, typename TValue>
TValue& BSTree<TKey, TValue>::find(const TKey& key)
{
    Node<TKey, TValue>* node = find_node(key);
    if (node == nullptr)
        throw std::logic_error("Key not found");
    return node->data.second;
}

template<typename TKey, typename TValue>
bool BSTree<TKey, TValue>::contains(const TKey& key) const noexcept
{
    return find_node(key) != nullptr;
}
template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key)
{
    if (is_empty())
        throw std::logic_error("Tree is empty");

    _root = erase_recursive(_root, key);
}
template<typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string(bool sorted) const noexcept
{
    if (is_empty())
        return "empty";

    std::string result;
    std::ostringstream oss;

    if (sorted)
    {
        std::vector<Node<TKey, TValue>*> stack;
        Node<TKey, TValue>* cur = _root;

        while (cur != nullptr || !stack.empty())
        {
            while (cur != nullptr)
            {
                stack.push_back(cur);
                cur = cur->left;
            }

            cur = stack.back();
            stack.pop_back();

            if (!result.empty()) result += " ";

            oss.str("");
            oss.clear();
            oss << cur->data.first << ":" << cur->data.second;
            result += oss.str();

            cur = cur->right;
        }
    }
    else
    {
        std::vector<Node<TKey, TValue>*> queue;
        queue.push_back(_root);

        while (!queue.empty())
        {
            Node<TKey, TValue>* node = queue.front();
            queue.erase(queue.begin());

            if (!result.empty()) result += " ";

            oss.str("");
            oss.clear();
            oss << "(" << node->data.first << ":" << node->data.second << ")";
            result += oss.str();

            if (node->left != nullptr)
                queue.push_back(node->left);
            if (node->right != nullptr)
                queue.push_back(node->right);
        }
    }

    return result;
}