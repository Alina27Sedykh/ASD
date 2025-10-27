#pragma once
#include <stdexcept>

template <class T>
struct Node
{
    T value;
    Node<T>* next;
    Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};

template <class T>
class List
{
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    List() : _head(nullptr), _tail(nullptr), _count(0) {}
    List(const List& other) : _head(nullptr), _tail(nullptr), _count(0)
    {
        Node<T>* current = other._head;
        while (current != nullptr)
        {
            push_back(current->value);
            current = current->next;
        }
    }
    ~List()
    {
        clear();
    }
    List& operator=(const List& other)
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
};

template <class T>
bool List<T>::is_empty() const
{
    return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& val) noexcept
{
    Node<T>* node = new Node<T>(val, _head);
    if (is_empty())
    {
        _tail = node;
    }
    _head = node;
    _count++;
}

template <class T>
void List<T>::pop_front()
{
    if (is_empty())
    {
        throw std::runtime_error("Cannot pop from empty list");
    }
    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
    _count--;
    if (_head == nullptr)
    {
        _tail = nullptr;
    }
}

template <class T>
void List<T>::push_back(const T& val) noexcept
{
    Node<T>* node = new Node<T>(val);
    if (is_empty())
    {
        _head = node;
        _tail = node;
    }
    else
    {
        _tail->next = node;
        _tail = node;
    }
    _count++;
}

template <class T>
void List<T>::pop_back()
{
    if (is_empty())
    {
        throw std::runtime_error("Cannot pop from empty list");
    }
    if (_head == _tail)
    {
        delete _head;
        _head = _tail = nullptr;
    }
    else
    {
        Node<T>* current = _head;
        while (current->next != _tail)
        {
            current = current->next;
        }

        delete _tail;
        _tail = current;
        _tail->next = nullptr;
    }
    _count--;
}

template <class T>
void List<T>::insert(Node<T>* node, const T& val)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("Node cannot be null");
    }
    Node<T>* new_node = new Node<T>(val, node->next);
    node->next = new_node;
    if (_tail == node)
    {
        _tail = new_node;
    }
    _count++;
}

template <class T>
void List<T>::insert(int pos, const T& val)
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
        int cur_pos = 0;
        Node<T>* cur = _head;
        while (cur != nullptr && cur_pos < pos - 1)
        {
            cur_pos++;
            cur = cur->next;
        }
        insert(cur, val);
    }
}

template <class T>
void List<T>::erase(Node<T>* node)
{
    if (node == nullptr || is_empty())
    {
        throw std::invalid_argument("Node cannot be null or list is empty");
    }

    if (node == _head)
    {
        pop_front();
        return;
    }

    Node<T>* cur = _head;
    while (cur != nullptr && cur->next != node)
    {
        cur = cur->next;
    }

    if (cur == nullptr)
    {
        throw std::invalid_argument("Node not found in list");
    }
    cur->next = node->next;
    if (node == _tail)
    {
        _tail = cur;
    }
    delete node;
    _count--;

}

template <class T>
void List<T>::erase(int pos)
{
    if (pos < 0 || pos >= _count)
    {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0)
    {
        pop_front();
    }
    else
    {
        int cur_pos = 0;
        Node<T>* cur = _head;
        while (cur_pos < pos - 1)
        {
            cur_pos++;
            cur = cur->next;
        }
        erase(cur->next);
    }
}

template <class T>
Node<T>* List<T>::find(const T& val)
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
void List<T>::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
}