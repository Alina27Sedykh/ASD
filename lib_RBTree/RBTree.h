#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
enum class Color { RED, BLACK };

template<typename TKey, typename TVal>
struct RBNode
{
    RBNode<TKey, TVal>* _left;
    RBNode<TKey, TVal>* _right;
    RBNode<TKey, TVal>* _parent;
    Color _color;
    std::pair<TKey, TVal> _data;

    RBNode(const TKey& key, const TVal& val, Color color = Color::RED, RBNode<TKey, TVal>* parent = nullptr): _left(nullptr), _right(nullptr), _parent(parent), _color(color), _data(key, val) {}
};

template<typename TKey, typename TVal>
class RBTree
{
private:
    using Node = RBNode<TKey, TVal>;

    Node* _root;
    size_t _size;
    Node* _NIL;

    Node* createNIL()
    {
        Node* nil = new Node(TKey(), TVal(), Color::BLACK);
        nil->_left = nil->_right = nil->_parent = nil;
        return nil;
    }

    Node* findNode(const TKey& key) const
    {
        Node* cur = _root;
        while (cur != _NIL)
        {
            if (key == cur->_data.first)
            {
                return cur;
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
        return nullptr;
    }

    void leftRotate(Node* x)
    {
        Node* y = x->_right;
        x->_right = y->_left;
        if (y->_left != _NIL)
        {
            y->_left->_parent = x;
        }
        y->_parent = x->_parent;
        if (x->_parent == _NIL)
        {
            _root = y;
        }
        else if (x == x->_parent->_left)
        {
            x->_parent->_left = y;
        }
        else
        {
            x->_parent->_right = y;
        }
        y->_left = x;
        x->_parent = y;
    }

    void rightRotate(Node* x)
    {
        Node* y = x->_left;
        x->_left = y->_right;
        if (y->_right != _NIL)
        {
            y->_right->_parent = x;
        }
        y->_parent = x->_parent;
        if (x->_parent == _NIL)
        {
            _root = y;
        }
        else if (x == x->_parent->_right)
        {
            x->_parent->_right = y;
        }
        else
        {
            x->_parent->_left = y;
        }
        y->_right = x;
        x->_parent = y;
    }

    void fixInsert(Node* z)
    {
        while (z->_parent != _NIL && z->_parent->_color == Color::RED)
        {
            if (z->_parent == z->_parent->_parent->_left)
            {
                Node* y = z->_parent->_parent->_right;
                if (y->_color == Color::RED)
                {
                    z->_parent->_color = Color::BLACK;
                    y->_color = Color::BLACK;
                    z->_parent->_parent->_color = Color::RED;
                    z = z->_parent->_parent;
                }
                else
                {
                    if (z == z->_parent->_right)
                    {
                        z = z->_parent;
                        leftRotate(z);
                    }
                    z->_parent->_color = Color::BLACK;
                    z->_parent->_parent->_color = Color::RED;
                    rightRotate(z->_parent->_parent);
                }
            }
            else
            {
                Node* y = z->_parent->_parent->_left;
                if (y->_color == Color::RED)
                {
                    z->_parent->_color = Color::BLACK;
                    y->_color = Color::BLACK;
                    z->_parent->_parent->_color = Color::RED;
                    z = z->_parent->_parent;
                }
                else
                {
                    if (z == z->_parent->_left)
                    {
                        z = z->_parent;
                        rightRotate(z);
                    }
                    z->_parent->_color = Color::BLACK;
                    z->_parent->_parent->_color = Color::RED;
                    leftRotate(z->_parent->_parent);
                }
            }
        }
        _root->_color = Color::BLACK;
    }

    void printNode(std::ostream& out, Node* node, int level) const
    {
        if (node == _NIL) return;
        printNode(out, node->_right, level + 1);
        for (int i = 0; i < level; i++) out << "    ";
        const char* colorStr = (node->_color == Color::RED) ? "(R)" : "(B)";
        out << node->_data.first << " : " << node->_data.second << colorStr << std::endl;
        printNode(out, node->_left, level + 1);
    }

    void inorderCollect(Node* node, std::vector<std::pair<TKey, TVal>>& result) const
    {
        if (node == _NIL) return;
        inorderCollect(node->_left, result);
        result.push_back(node->_data);
        inorderCollect(node->_right, result);
    }

    void destroySubtree(Node* node)
    {
        if (node == _NIL || node == nullptr) return;
        destroySubtree(node->_left);
        destroySubtree(node->_right);
        delete node;
    }

public:
    RBTree() : _size(0)
    {
        _NIL = createNIL();
        _root = _NIL;
    }

    ~RBTree()
    {
        destroySubtree(_root);
        delete _NIL;
    }

    void insert(const TKey& key, const TVal& val)
    {
       
        Node* existing = findNode(key);
        if (existing != nullptr && existing != _NIL)
        {
            existing->_data.second = val;
            return;
        }
        Node* z = new Node(key, val, Color::RED);
        z->_left = _NIL;
        z->_right = _NIL;
        Node* y = _NIL;
        Node* x = _root;

        while (x != _NIL)
        {
            y = x;
            if (z->_data.first < x->_data.first)
            {
                x = x->_left;
            }
            else
            {
                x = x->_right;
            }
        }

        z->_parent = y;
        if (y == _NIL)
        {
            _root = z;
        }
        else if (z->_data.first < y->_data.first)
        {
            y->_left = z;
        }
        else
        {
            y->_right = z;
        }
        if (z->_parent == _NIL)
        {
            z->_color = Color::BLACK;
        }
        else
        {
            fixInsert(z);
        }

        _size++;
    }

    void erase(const TKey& key)
    {
        Node* node = findNode(key);
        if (node == nullptr || node == _NIL) return;

        if (node->_left == _NIL && node->_right == _NIL)
        {
            if (node->_parent == _NIL)
            {
                _root = _NIL;
            }
            else if (node == node->_parent->_left)
            {
                node->_parent->_left = _NIL;
            }
            else
            {
                node->_parent->_right = _NIL;
            }
            delete node;
        }
        else if (node->_left == _NIL)
        {
            if (node->_parent == _NIL)
            {
                _root = node->_right;
                _root->_parent = _NIL;
            }
            else if (node == node->_parent->_left)
            {
                node->_parent->_left = node->_right;
                node->_right->_parent = node->_parent;
            }
            else
            {
                node->_parent->_right = node->_right;
                node->_right->_parent = node->_parent;
            }
            delete node;
        }
        else if (node->_right == _NIL)
        {
            if (node->_parent == _NIL)
            {
                _root = node->_left;
                _root->_parent = _NIL;
            }
            else if (node == node->_parent->_left)
            {
                node->_parent->_left = node->_left;
                node->_left->_parent = node->_parent;
            }
            else
            {
                node->_parent->_right = node->_left;
                node->_left->_parent = node->_parent;
            }
            delete node;
        }
        else
        {
            
            Node* min = node->_right;
            while (min->_left != _NIL)
            {
                min = min->_left;
            }
            TKey minKey = min->_data.first;
            TVal minVal = min->_data.second;
            erase(minKey);
            node->_data = std::make_pair(minKey, minVal);
            return;
        }

        _size--;
    }

    TVal find(const TKey& key) const
    {
        Node* node = findNode(key);
        if (node == nullptr || node == _NIL)
        {
            throw std::out_of_range("Key not found");
        }
        return node->_data.second;
    }

    bool contains(const TKey& key) const
    {
        return findNode(key) != nullptr;
    }

    size_t size() const
    {
        return _size;
    }

    bool empty() const
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
};