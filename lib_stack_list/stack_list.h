#pragma once
#include <stdexcept>
#include"list.h"
template <class T>
class MyStack
{
    List<T> _list;

public:
    MyStack() = default;
    MyStack(const MyStack& other) : _list(other._list) {}

    MyStack& operator=(const MyStack& other);

    void push(const T& val) noexcept;
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    int size() const;
    void clear();
    void swap(MyStack& other);
};
template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other)
{
    if (this != &other)
    {
        _list = other._list;
    }
    return *this;
}

template <class T>
void MyStack<T>::push(const T& val) noexcept
{
    _list.push_front(val);
}

template <class T>
void MyStack<T>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Cannot pop from empty stack");
    }
    _list.pop_front();
}

template <class T>
T& MyStack<T>::top()
{
    if (empty())
    {
        throw std::runtime_error("Cannot get top from empty stack");
    }
    return _list.front();
}

template <class T>
const T& MyStack<T>::top() const
{
    if (empty())
    {
        throw std::runtime_error("Cannot get top from empty stack");
    }
    return _list.front();
}

template <class T>
bool MyStack<T>::empty() const
{
    return _list.is_empty();
}

template <class T>
int MyStack<T>::size() const
{
    return _list.size();
}

template <class T>
void MyStack<T>::clear()
{
    _list.clear();
}

template <class T>
void MyStack<T>::swap(MyStack& other)
{
    List<T> temp = _list;
    _list = other._list;
    other._list = temp;
}