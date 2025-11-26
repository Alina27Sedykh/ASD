#pragma once
#include <stdexcept>


template <class T>
struct Node
{
    T value;
    Node<T>* next;
    Node<T>* prev;
    Node(T value_, Node<T>* prev_ = nullptr, Node<T>* next_ = nullptr) : value(value_), prev(prev_), next(next_) {}
};

template <class T>
class DoubleLinkedList
{
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    DoubleLinkedList() : _head(nullptr), _tail(nullptr), _count(0) {}

    DoubleLinkedList(const DoubleLinkedList& other) : _head(nullptr), _tail(nullptr), _count(0)
    {
        Node<T>* current = other._head;
        while (current != nullptr)
        {
            push_back(current->value);
            current = current->next;
        }
    }

    ~DoubleLinkedList()
    {
        clear();
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            Node<T>* current = other._head;
            while (current != nullptr)
            {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    void push_front(const T& val) noexcept;
    void pop_front();
    void push_back(const T& val) noexcept;
    void pop_back();
    void insert(int pos, const T& val);
    void erase(int pos);
    void insert(Node<T>* node, const T& val);
    void erase(Node<T>* node);
    bool is_empty() const;
    Node<T>* find(const T& val);
    void clear();
    int size() const { return _count; }
    T& front() { return _head->value; }
    T& back() { return _tail->value; }

    class Iterator
    {
        Node<T>* current;
    public:
        Iterator(Node<T>* pos = nullptr) : current(pos) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator=(const Iterator& other);
        T& operator*();
        const T& operator*() const;

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        Iterator operator++(int);
        Iterator& operator++();
        Iterator operator--(int);
        Iterator& operator--();
        Iterator& operator-=(int n);
    };

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator rbegin() { return Iterator(_tail); }
    Iterator rend() { return Iterator(nullptr); }
};


template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator=(const Iterator& other)
{
    if (this != &other)
    {
        current = other.current;
    }
    return *this;
}

template <class T>
T& DoubleLinkedList<T>::Iterator::operator*()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing null iterator");
    }
    return current->value;
}

template <class T>
const T& DoubleLinkedList<T>::Iterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing null iterator");
    }
    return current->value;
}

template <class T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& other) const
{
    return current == other.current;
}

template <class T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}

template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Incrementing null iterator");
    }
    current = current->next;
    return *this;
}

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator--()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Decrementing null iterator");
    }
    current = current->prev;
    return *this;
}

template <class T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator--(int)
{
    Iterator temp = *this;
    --(*this);
    return temp;
}

template <class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator-=(int n)
{
    for (int i = 0; i < n && current != nullptr; ++i)
    {
        current = current->prev;
    }
    return *this;
}

// List2 implementation
template <class T>
bool DoubleLinkedList<T>::is_empty() const
{
    return _head == nullptr;
}

template <class T>
void DoubleLinkedList<T>::push_front(const T& val) noexcept
{
    Node<T>* node = new Node<T>(val, nullptr, _head);
    if (is_empty())
    {
        _tail = node;
    }
    else
    {
        _head->prev = node;
    }
    _head = node;
    _count++;
}

template <class T>
void DoubleLinkedList<T>::pop_front()
{
    if (is_empty())
    {
        throw std::runtime_error("Cannot pop from empty list");
    }
    Node<T>* temp = _head;
    _head = _head->next;
    if (_head != nullptr)
    {
        _head->prev = nullptr;
    }
    else
    {
        _tail = nullptr;
    }
    delete temp;
    _count--;
}

template <class T>
void DoubleLinkedList<T>::push_back(const T& val) noexcept
{
    Node<T>* node = new Node<T>(val, _tail, nullptr);
    if (is_empty())
    {
        _head = node;
    }
    else
    {
        _tail->next = node;
    }
    _tail = node;
    _count++;
}

template <class T>
void DoubleLinkedList<T>::pop_back()
{
    if (is_empty())
    {
        throw std::runtime_error("Cannot pop from empty list");
    }
    Node<T>* temp = _tail;
    _tail = _tail->prev;
    if (_tail != nullptr)
    {
        _tail->next = nullptr;
    }
    else
    {
        _head = nullptr;
    }
    delete temp;
    _count--;
}

template <class T>
void DoubleLinkedList<T>::insert(Node<T>* node, const T& val)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("Node cannot be null");
    }

    Node<T>* new_node = new Node<T>(val, node->prev, node);

    if (node->prev != nullptr)
    {
        node->prev->next = new_node;
    }
    else
    {
        _head = new_node;
    }

    node->prev = new_node;
    _count++;
}

template <class T>
void DoubleLinkedList<T>::insert(int pos, const T& val)
{
    if (pos < 0 || pos > _count)
    {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0)
    {
        push_front(val);
    }
    else if (pos == _count)
    {
        push_back(val);
    }
    else
    {
        if (pos <= _count / 2)
        {
            Node<T>* current = _head;
            for (int i = 0; i < pos; ++i)
            {
                current = current->next;
            }
            insert(current, val);
        }
        else
        {
            Node<T>* current = _tail;
            for (int i = _count - 1; i > pos; --i)
            {
                current = current->prev;
            }
            insert(current, val);
        }
    }
}

template <class T>
void DoubleLinkedList<T>::erase(Node<T>* node)
{
    if (node == nullptr || is_empty())
    {
        throw std::invalid_argument("Node cannot be null or list is empty");
    }

    if (node->prev != nullptr)
    {
        node->prev->next = node->next;
    }
    else
    {
        _head = node->next;
    }

    if (node->next != nullptr)
    {
        node->next->prev = node->prev;
    }
    else
    {
        _tail = node->prev;
    }

    delete node;
    _count--;
}

template <class T>
void DoubleLinkedList<T>::erase(int pos)
{
    if (pos < 0 || pos >= _count)
    {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0)
    {
        pop_front();
    }
    else if (pos == _count - 1)
    {
        pop_back();
    }
    else
    {
        if (pos <= _count / 2)
        {
            Node<T>* current = _head;
            for (int i = 0; i < pos; ++i)
            {
                current = current->next;
            }
            erase(current);
        }
        else
        {
            Node<T>* current = _tail;
            for (int i = _count - 1; i > pos; --i)
            {
                current = current->prev;
            }
            erase(current);
        }
    }
}

template <class T>
Node<T>* DoubleLinkedList<T>::find(const T& val)
{
    Node<T>* current = _head;
    while (current != nullptr)
    {
        if (current->value == val)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
void DoubleLinkedList<T>::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
}