#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "ITable.h"
template <typename TKey, typename TValue>
class UnSortedTableOnVec: public ITable<TKey, TValue>
{
	std::vector<std::pair<TKey, TValue>> _rows;
public:
    UnSortedTableOnVec() = default;
    ~UnSortedTableOnVec() override = default;

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    size_t size() const noexcept override;
};

template <typename TKey, typename TValue>
void UnSortedTableOnVec<TKey, TValue>::insert(const TKey& Key, const TValue& Val) 
{
    // Проверяем, существует ли уже такой ключ
    auto it = _rows.end();
    for (size_t i = 0; i < _rows.size(); ++i) 
    {
        if (_rows[i].first == Key)
        {
            it = _rows.begin() + i;
            break;
        }
    }
    
    if (it != _rows.end())
    {
        // Если ключ существует, обновляем значение
        it->second = Val;
    } 
    else
    {
        // Иначе добавляем новую пару
        _rows.push_back(std::make_pair(Key, Val));
    }
}

template <typename TKey, typename TValue>
TValue UnSortedTableOnVec<TKey, TValue>::find(const TKey& Key) const 
{
    auto it = _rows.end();
    for (size_t i = 0; i < _rows.size(); ++i) 
    {
        if (_rows[i].first == Key)
        {
            return _rows[i].second;
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename TKey, typename TValue>
void UnSortedTableOnVec<TKey, TValue>::erase(const TKey& Key)
{
    for (size_t i = 0; i < _rows.size(); ++i)
    {
        if (_rows[i].first == Key)
        {
            _rows.erase(_rows.begin() + i);
            return;  // Выходим после удаления
        }
    }
}

template <typename TKey, typename TValue>
std::ostream& UnSortedTableOnVec<TKey, TValue>::print(std::ostream& out) const noexcept 
{
    for (const auto& pair : _rows) 
    {
        out << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
    return out;
}

template <typename TKey, typename TValue>
bool UnSortedTableOnVec<TKey, TValue>::is_empty() const noexcept 
{
    return _rows.empty();
}

template <typename TKey, typename TValue>
bool UnSortedTableOnVec<TKey, TValue>::consist(const TKey& Key) const noexcept 
{
    auto it = _rows.end();
    for (size_t i = 0; i < _rows.size(); ++i)
    {
        if (_rows[i].first == Key)
        {
            return true;
        }
    }

    return false;
}

template <typename TKey, typename TValue>
size_t UnSortedTableOnVec<TKey, TValue>::size() const noexcept 
{
    return _rows.size();
}
