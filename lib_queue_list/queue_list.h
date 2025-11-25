#pragma once
#include "list.h"
#include <stdexcept>

template <class T>
class MyQueue
{
    List<T> _list;

public:
    MyQueue() = default;
    MyQueue(const MyQueue& other) : _list(other._list) {}

    MyQueue& operator=(const MyQueue& other);

    void push(const T& val) noexcept;
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool empty() const;
    int size() const;
    void clear();
    void swap(MyQueue& other);
};
template <class T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other)
{
    if (this != &other)
    {
        _list = other._list;
    }
    return *this;
}

template <class T>
void MyQueue<T>::push(const T& val) noexcept
{
    _list.push_back(val);
}

template <class T>
void MyQueue<T>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Cannot pop from empty queue");
    }
    _list.pop_front();
}

template <class T>
T& MyQueue<T>::front()
{
    if (empty())
    {
        throw std::runtime_error("Cannot get front from empty queue");
    }
    return _list.front();
}

template <class T>
const T& MyQueue<T>::front() const
{
    if (empty())
    {
        throw std::runtime_error("Cannot get front from empty queue");
    }
    return _list.front();
}

template <class T>
T& MyQueue<T>::back()
{
    if (empty())
    {
        throw std::runtime_error("Cannot get back from empty queue");
    }
    return _list.back();
}

template <class T>
const T& MyQueue<T>::back() const
{
    if (empty())
    {
        throw std::runtime_error("Cannot get back from empty queue");
    }
    return _list.back();
}

template <class T>
bool MyQueue<T>::empty() const
{
    return _list.is_empty();
}

template <class T>
int MyQueue<T>::size() const
{
    return _list.size();
}

template <class T>
void MyQueue<T>::clear()
{
    _list.clear();
}

template <class T>
void MyQueue<T>::swap(MyQueue& other)
{
    List<T> temp = _list;
    _list = other._list;
    other._list = temp;
}