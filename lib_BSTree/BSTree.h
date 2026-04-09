#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Tree.h"

template<typename TKey, typename TValue>
class BSTree : public Tree<TKey, TValue>
{
private:
    // Вспомогательные методы для BST
    Node<TKey, TValue>* find_min(Node<TKey, TValue>* node);
    Node<TKey, TValue>* find_max(Node<TKey, TValue>* node);
    Node<TKey, TValue>* erase_recursive(Node<TKey, TValue>* node, const TKey& key);
    Node<TKey, TValue>* insert_recursive(Node<TKey, TValue>* node, const TKey& key, const TValue& value);
    Node<TKey, TValue>* find_node_bst(const TKey& key) const;
    void inorder_collect(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const;
    void levelorder_collect(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const;

public:
    BSTree() : Tree<TKey, TValue>() {}
    ~BSTree() = default;  // Деструктор родителя вызывается автоматически

    // Переопределяем методы родителя для BST-логики
    void insert(const TKey& key, const TValue& value);
    TValue& find(const TKey& key);
    void erase(const TKey& key);
    bool contains(const TKey& key) const noexcept;

    // Новые методы специфичные для BST
    std::string to_string(bool sorted = false) const noexcept;
};

// Реализация методов BSTree

template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_node_bst(const TKey& key) const
{
    if (this->is_empty()) return nullptr;

    Node<TKey, TValue>* cur = this->_root;
    while (cur != nullptr)
    {
        if (cur->value.first == key)
            return cur;
        else if (key < cur->value.first)
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
Node<TKey, TValue>* BSTree<TKey, TValue>::insert_recursive(Node<TKey, TValue>* node, const TKey& key, const TValue& value)
{
    if (node == nullptr)
    {
        this->_size++;
        return new Node<TKey, TValue>(key, value);
    }

    if (key < node->value.first)
    {
        node->left = insert_recursive(node->left, key, value);
    }
    else if (key > node->value.first)
    {
        node->right = insert_recursive(node->right, key, value);
    }
    else
    {
        // Ключ существует - обновляем значение
        node->value.second = value;
    }
    return node;
}

template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::erase_recursive(Node<TKey, TValue>* node, const TKey& key)
{
    if (node == nullptr)
        throw std::logic_error("Key not found");

    if (key < node->value.first)
    {
        node->left = erase_recursive(node->left, key);
    }
    else if (key > node->value.first)
    {
        node->right = erase_recursive(node->right, key);
    }
    else
    {
        // Нашли узел для удаления
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            this->_size--;
            return nullptr;
        }
        else if (node->left == nullptr)
        {
            Node<TKey, TValue>* temp = node->right;
            delete node;
            this->_size--;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node<TKey, TValue>* temp = node->left;
            delete node;
            this->_size--;
            return temp;
        }
        else
        {
            // Узел с двумя детьми - находим максимальный в левом поддереве
            Node<TKey, TValue>* max_left = find_max(node->left);
            node->value = max_left->value;
            node->left = erase_recursive(node->left, max_left->value.first);
        }
    }
    return node;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value)
{
    this->_root = insert_recursive(this->_root, key, value);
}

template<typename TKey, typename TValue>
TValue& BSTree<TKey, TValue>::find(const TKey& key)
{
    Node<TKey, TValue>* node = find_node_bst(key);
    if (node == nullptr)
        throw std::logic_error("Key not found");
    return node->value.second;
}

template<typename TKey, typename TValue>
bool BSTree<TKey, TValue>::contains(const TKey& key) const noexcept
{
    return find_node_bst(key) != nullptr;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key)
{
    if (this->is_empty())
        throw std::logic_error("Tree is empty");

    this->_root = erase_recursive(this->_root, key);
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::inorder_collect(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const
{
    if (node == nullptr) return;
    inorder_collect(node->left, result);
    result.push_back(node->value);
    inorder_collect(node->right, result);
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::levelorder_collect(Node<TKey, TValue>* node, std::vector<std::pair<TKey, TValue>>& result) const
{
    if (node == nullptr) return;

    std::vector<Node<TKey, TValue>*> queue;
    queue.push_back(node);

    while (!queue.empty())
    {
        Node<TKey, TValue>* current = queue.front();
        queue.erase(queue.begin());
        result.push_back(current->value);

        if (current->left) queue.push_back(current->left);
        if (current->right) queue.push_back(current->right);
    }
}

template<typename TKey, typename TValue>
std::string BSTree<TKey, TValue>::to_string(bool sorted) const noexcept
{
    if (this->is_empty())
        return "empty";

    std::vector<std::pair<TKey, TValue>> elements;

    if (sorted)
    {
        inorder_collect(this->_root, elements);
    }
    else
    {
        levelorder_collect(this->_root, elements);
    }

    std::string result;
    for (size_t i = 0; i < elements.size(); i++)
    {
        if (i > 0) result += " ";
        if (!sorted) result += "(";

        // Преобразуем через stringstream (работает с ЛЮБЫМИ типами, у которых есть operator<<)
        std::stringstream ss;
        ss << elements[i].first << ":" << elements[i].second;
        result += ss.str();

        if (!sorted) result += ")";
    }

    return result;
}