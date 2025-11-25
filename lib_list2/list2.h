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
class List2
{
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    List2() : _head(nullptr), _tail(nullptr), _count(0) {}

    List2(const List2& other) : _head(nullptr), _tail(nullptr), _count(0)
    {
        Node<T>* current = other._head;
        while (current != nullptr)
        {
            push_back(current->value);
            current = current->next;
        }
    }

    ~List2()
    {
        clear();
    }

    List2& operator=(const List2& other)
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

    class Iterator2
    {
        Node<T>* current;
    public:
        Iterator2(Node<T>* pos = nullptr) : current(pos) {}
        Iterator2(const Iterator2& other) : current(other.current) {}

        Iterator2& operator=(const Iterator2& other);
        T& operator*();
        const T& operator*() const;

        bool operator==(const Iterator2& other) const;
        bool operator!=(const Iterator2& other) const;
        Iterator2 operator++(int);
        Iterator2& operator++();
        Iterator2 operator--(int);
        Iterator2& operator--();
        Iterator2& operator-=(int n);
    };

    Iterator2 begin() { return Iterator2(_head); }
    Iterator2 end() { return Iterator2(nullptr); }
    Iterator2 rbegin() { return Iterator2(_tail); }
    Iterator2 rend() { return Iterator2(nullptr); }
};


template <class T>
typename List2<T>::Iterator2& List2<T>::Iterator2::operator=(const Iterator2& other)
{
    if (this != &other)
    {
        current = other.current;
    }
    return *this;
}

template <class T>
T& List2<T>::Iterator2::operator*()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing null iterator");
    }
    return current->value;
}

template <class T>
const T& List2<T>::Iterator2::operator*() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing null iterator");
    }
    return current->value;
}

template <class T>
bool List2<T>::Iterator2::operator==(const Iterator2& other) const
{
    return current == other.current;
}

template <class T>
bool List2<T>::Iterator2::operator!=(const Iterator2& other) const
{
    return !(*this == other);
}

template <class T>
typename List2<T>::Iterator2& List2<T>::Iterator2::operator++()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Incrementing null iterator");
    }
    current = current->next;
    return *this;
}

template <class T>
typename List2<T>::Iterator2 List2<T>::Iterator2::operator++(int)
{
    Iterator2 temp = *this;
    ++(*this);
    return temp;
}

template <class T>
typename List2<T>::Iterator2& List2<T>::Iterator2::operator--()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Decrementing null iterator");
    }
    current = current->prev;
    return *this;
}

template <class T>
typename List2<T>::Iterator2 List2<T>::Iterator2::operator--(int)
{
    Iterator2 temp = *this;
    --(*this);
    return temp;
}

template <class T>
typename List2<T>::Iterator2& List2<T>::Iterator2::operator-=(int n)
{
    for (int i = 0; i < n && current != nullptr; ++i)
    {
        current = current->prev;
    }
    return *this;
}

// List2 implementation
template <class T>
bool List2<T>::is_empty() const
{
    return _head == nullptr;
}

template <class T>
void List2<T>::push_front(const T& val) noexcept
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
void List2<T>::pop_front()
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
void List2<T>::push_back(const T& val) noexcept
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
void List2<T>::pop_back()
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
void List2<T>::insert(Node<T>* node, const T& val)
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
void List2<T>::insert(int pos, const T& val)
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
void List2<T>::erase(Node<T>* node)
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
void List2<T>::erase(int pos)
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
Node<T>* List2<T>::find(const T& val)
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
void List2<T>::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
}