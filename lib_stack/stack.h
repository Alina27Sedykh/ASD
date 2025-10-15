#pragma once
#include <cmath>
#include <stdexcept>
template <class T>
class Stak
{
	T* _data;
	int _size;
	int _top;
public:
	Stak(int capacity);
	Stak(const Stak& other);
	~Stak();
	
	void push(const T& val);
	void pop();
	inline T top()const;
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept;
};
template <class T>
Stak<T>::~Stak()
{
	delete[] _data;
}
template <class T>
void Stak<T>::push(const T& val)
{
	if (is_full())
	{
		throw std::invalid_argument("Stak is full");
	}
	_data[++_top] = val;
}
template <class T>
void Stak<T>::pop()
{
	if (is_empty())
	{
		throw std::invalid_argument("Stak is empty");
	}
	--_top;
}
template <class T>
inline T Stak<T>::top() const 
{
	if (is_empty())
	{
		throw std::invalid_argument("Stak is empty");
	}
	return _data[_top];
}

template <class T>
inline bool Stak<T>::is_empty() const noexcept
{
	return _top == -1;
}

template <class T>
inline bool Stak<T>::is_full()  const noexcept
{
	return _top == _size - 1;
}

template <class T>
void Stak<T>::clear() noexcept
{
	_top = -1;
}
template <class T>
Stak<T>::Stak(int capacity) : _size(capacity), _top(-1)
{
	_data = new T[capacity];
}
template <class T>
Stak<T>::Stak(const Stak& other) : _size(other._size), _top(other._top)
{
	_data = new T[_size];
	for (int i = 0; i <= _top; ++i)
	{
		_data[i] = other._data[i];
	}
}