#pragma once
#include <stdexcept>

template <class T>
class Queue
{
    T* _data;
    int _size;
    int _front;
    int _rear;
    int _count;

public:
    Queue(int capacity);
    Queue(const Queue& other);
    ~Queue();

    void push(const T& val);
    void pop();
    inline T front() const;
    inline T back() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template <class T>
Queue<T>::~Queue()
{
    delete[] _data;
}

template <class T>
void Queue<T>::push(const T& val)
{
    if (is_full())
    {
        throw std::invalid_argument("Queue is full");
    }
    _rear = (_rear + 1) % _size;
    _data[_rear] = val;
    _count++;
}

template <class T>
void Queue<T>::pop()
{
    if (is_empty())
    {
        throw std::invalid_argument("Queue is empty");
    }
    _front = (_front + 1) % _size;
    _count--;
}

template <class T>
inline T Queue<T>::front() const
{
    if (is_empty())
    {
        throw std::invalid_argument("Queue is empty");
    }
    return _data[_front];
}

template <class T>
inline T Queue<T>::back() const
{
    if (is_empty())
    {
        throw std::invalid_argument("Queue is empty");
    }
    return _data[_rear];
}

template <class T>
inline bool Queue<T>::is_empty() const noexcept
{
    return _count == 0;
}

template <class T>
inline bool Queue<T>::is_full() const noexcept
{
    return _count == _size;
}

template <class T>
void Queue<T>::clear() noexcept
{
    _front = 0;
    _rear = -1;
    _count = 0;
}

template <class T>
Queue<T>::Queue(int capacity) : _size(capacity), _front(0), _rear(-1), _count(0)
{
    _data = new T[capacity];
}

template <class T>
Queue<T>::Queue(const Queue& other) : _size(other._size), _front(other._front), _rear(other._rear), _count(other._count)
{
    _data = new T[_size];

    if (!other.is_empty())
    {
        int i = _front;
        int elements_copied = 0;
        while (elements_copied < _count)
        {
            _data[i] = other._data[i];
            i = (i + 1) % _size;
            elements_copied++;
        }
    }
}