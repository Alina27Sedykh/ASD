#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Queue.h"

template<typename TKey, typename TValue>
struct Node
{
    std::pair<TKey, TValue> value;
    Node* left;
    Node* right;

    Node(const TKey& key, const TValue& val) : value({ key, val }), left(nullptr), right(nullptr) {}
};

template<typename TKey, typename TValue>
class Tree
{
private:
    Node<TKey, TValue>* _root;
    int _size;

    void clear_recursive(Node<TKey, TValue>* node);
    Node<TKey, TValue>* find_node(const TKey& key);
    void find_last_node(Node<TKey, TValue>*& last_node, Node<TKey, TValue>*& parent_of_last);

    void preorder_recursive(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const;
    void inorder_recursive(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const;
    void postorder_recursive(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const;
public:
    Tree() : _root(nullptr), _size(0) {}
    ~Tree() 
    {
        clear_recursive(_root);
    }

    void insert(const TKey& key, const TValue& value);
    TValue& find(const TKey& key);
    void erase(const TKey& key);
    bool is_empty() const 
    {
        return _root == nullptr;
    }
    int size() const
    {
        return _size; 
    }

    bool contains(const TKey& key) 
    {
        return find_node(key) != nullptr;
    }

    std::vector<std::pair<TKey, TValue>> get_elements();

    void print_preorder() const;
    void print_inorder() const;
    void print_postorder() const;
    void print_levelorder() const;
};

template<typename TKey, typename TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::find_node(const TKey& key)
{
    if (is_empty()) return nullptr;

    Queue<Node<TKey, TValue>*> q(_size + 10);
    q.push(_root);

    while (!q.is_empty())
    {
        Node<TKey, TValue>* current = q.front();
        q.pop();

        if (current->value.first == key)
        {
            return current;
        }
        if (current->left)
        {
            q.push(current->left);
        }
        if (current->right)
        {
            q.push(current->right);
        }
    }

    return nullptr;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::find_last_node(Node<TKey, TValue>*& last_node, Node<TKey, TValue>*& parent_of_last)
{
    if (is_empty()) return;

    Queue<Node<TKey, TValue>*> q(_size + 10);
    Queue<Node<TKey, TValue>*> parent_q(_size + 10);

    q.push(_root);
    parent_q.push(nullptr);

    last_node = nullptr;
    parent_of_last = nullptr;

    while (!q.is_empty())
    {
        Node<TKey, TValue>* current = q.front();
        Node<TKey, TValue>* parent = parent_q.front();
        q.pop();
        parent_q.pop();

        last_node = current;
        parent_of_last = parent;

        if (current->left)
        {
            q.push(current->left);
            parent_q.push(current);
        }
        if (current->right)
        {
            q.push(current->right);
            parent_q.push(current);
        }
    }
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value)
{
    Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key, value);

    if (is_empty())
    {
        _root = new_node;
        _size++;
        return;
    }

    Node<TKey, TValue>* existing = find_node(key);
    if (existing)
    {
        existing->value.second = value;
        delete new_node;
        return;
    }

    Queue<Node<TKey, TValue>*> q(_size + 10);
    q.push(_root);

    while (!q.is_empty())
    {
        Node<TKey, TValue>* current = q.front();
        q.pop();

        if (current->left == nullptr)
        {
            current->left = new_node;
            _size++;
            return;
        }
        else
        {
            q.push(current->left);
        }

        if (current->right == nullptr)
        {
            current->right = new_node;
            _size++;
            return;
        }
        else
        {
            q.push(current->right);
        }
    }
}

template<typename TKey, typename TValue>
TValue& Tree<TKey, TValue>::find(const TKey& key)
{
    Node<TKey, TValue>* node = find_node(key);
    if (node == nullptr)
    {
        throw std::logic_error("Key not found");
    }
    return node->value.second;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::erase(const TKey& key)
{
    if (is_empty())
    {
        throw std::logic_error("Tree is empty");
    }
     
    Node<TKey, TValue>* to_delete = find_node(key);
    if (to_delete == nullptr)
    {
        throw std::logic_error("Key not found");
    }
    Node<TKey, TValue>* last_node = nullptr;
    Node<TKey, TValue>* parent_of_last = nullptr;
    find_last_node(last_node, parent_of_last);

    if (to_delete == last_node)
    {
        if (parent_of_last)
        {
            if (parent_of_last->left == to_delete)
            {
                parent_of_last->left = nullptr;
            }
            else
            {
                parent_of_last->right = nullptr;
            }
        }
        else
        {
            _root = nullptr;
        }
        delete to_delete;
        _size--;
        return;
    }

    to_delete->value = last_node->value;

    if (parent_of_last)
    {
        if (parent_of_last->left == last_node)
        {
            parent_of_last->left = nullptr;
        }
        else
        {
            parent_of_last->right = nullptr;
        }
    }
    delete last_node;
    _size--;
}

template<typename TKey, typename TValue>
std::vector<std::pair<TKey, TValue>> Tree<TKey, TValue>::get_elements()
{
    std::vector<std::pair<TKey, TValue>> result;
    if (is_empty())
    {
        return result;
    }
    Queue<Node<TKey, TValue>*> q(_size + 10);
    q.push(_root);

    while (!q.is_empty())
    {
        Node<TKey, TValue>* current = q.front();
        q.pop();
        result.push_back(current->value);

        if (current->left)
        {
            q.push(current->left);
        }
        if (current->right)
        {
            q.push(current->right);
        }
    }

    return result;
}
template<typename TKey, typename TValue>
void Tree<TKey, TValue>::clear_recursive(Node<TKey, TValue>* node)
{
    if (node == nullptr) return;
    clear_recursive(node->left);
    clear_recursive(node->right);
    delete node;
}
template<typename TKey, typename TValue>
void Tree<TKey, TValue>::preorder_recursive(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const
{
    if (node == nullptr) return;
    result.push_back(node->value);
    preorder_recursive(node->left, result);
    preorder_recursive(node->right, result);
}
template<typename TKey, typename TValue>
void Tree<TKey, TValue>::inorder_recursive(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const
{
    if (node == nullptr) return;
    inorder_recursive(node->left, result);
    result.push_back(node->value);
    inorder_recursive(node->right, result);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::postorder_recursive(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const
{
    if (node == nullptr) return;
    postorder_recursive(node->left, result);
    postorder_recursive(node->right, result);
    result.push_back(node->value);
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_preorder() const
{
    std::vector<std::pair<TKey, TValue>> result;
    preorder_recursive(_root, result);

    for (size_t i = 0; i < result.size(); i++)
    {
        if (i > 0) std::cout << " ";
        std::cout << "(" << result[i].first << ":" << result[i].second << ")";
    }
    std::cout << std::endl;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_inorder() const
{
    std::vector<std::pair<TKey, TValue>> result;
    inorder_recursive(_root, result);

    for (size_t i = 0; i < result.size(); i++)
    {
        if (i > 0) std::cout << " ";
        std::cout << "(" << result[i].first << ":" << result[i].second << ")";
    }
    std::cout << std::endl;
}
template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_postorder() const
{
    std::vector<std::pair<TKey, TValue>> result;
    postorder_recursive(_root, result);

    for (size_t i = 0; i < result.size(); i++)
    {
        if (i > 0) std::cout << " ";
        std::cout << "(" << result[i].first << ":" << result[i].second << ")";
    }
    std::cout << std::endl;
}

template<typename TKey, typename TValue>
void Tree<TKey, TValue>::print_levelorder() const
{
    if (is_empty())
    {
        std::cout << "empty" << std::endl;
        return;
    }

    Queue<Node<TKey, TValue>*> q(_size + 10);
    q.push(_root);

    bool first = true;
    while (!q.is_empty())
    {
        Node<TKey, TValue>* current = q.front();
        q.pop();

        if (!first) std::cout << " ";
        std::cout << "(" << current->value.first << ":" << current->value.second << ")";
        first = false;

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    std::cout << std::endl;
}