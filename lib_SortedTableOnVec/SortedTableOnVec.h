#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "ITable.h"

template <typename TKey, typename TValue>
class SortedTableOnVec : public ITable<TKey, TValue>
{
private:
    std::vector<std::pair<TKey, TValue>> _rows;
    // Вспомогательная функция для поиска позиции для вставки
    size_t find_insert_position(const TKey& Key) const;

public:
    SortedTableOnVec() = default;
    ~SortedTableOnVec() override = default;

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    size_t size() const noexcept override;
};

// Реализация вспомогательной функции
template <typename TKey, typename TValue>
size_t SortedTableOnVec<TKey, TValue>::find_insert_position(const TKey& Key) const
{
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (_rows[mid].first < Key)
        {
            left = mid + 1;
        }
        else 
        {
            right = mid;
        }
    }
    return left;
}

// Реализация основных методов
template <typename TKey, typename TValue>
void SortedTableOnVec<TKey, TValue>::insert(const TKey& Key, const TValue& Val) 
{
    size_t pos = find_insert_position(Key);

    // Проверяем, существует ли уже такой ключ
    if (pos < _rows.size() && _rows[pos].first == Key)
    {
        // Обновляем значение
        _rows[pos].second = Val;
    }
    else 
    {
        // Вставляем с сохранением упорядоченности
        _rows.insert(_rows.begin() + pos, std::make_pair(Key, Val));
    }
}

template <typename TKey, typename TValue>
TValue SortedTableOnVec<TKey, TValue>::find(const TKey& Key) const
{
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right) 
    {
        size_t mid = left + (right - left) / 2;
        if (_rows[mid].first == Key) 
        {
            return _rows[mid].second;
        }
        else if (_rows[mid].first < Key)
        {
            left = mid + 1;
        }
        else 
        {
            right = mid;
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename TKey, typename TValue>
void SortedTableOnVec<TKey, TValue>::erase(const TKey& Key) 
{
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right) 
    {
        size_t mid = left + (right - left) / 2;
        if (_rows[mid].first == Key)
        {
            _rows.erase(_rows.begin() + mid);
            return;
        }
        else if (_rows[mid].first < Key) 
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
}

template <typename TKey, typename TValue>
std::ostream& SortedTableOnVec<TKey, TValue>::print(std::ostream& out) const noexcept
{
    for (const auto& pair : _rows)
    {
        out << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
    return out;
}

template <typename TKey, typename TValue>
bool SortedTableOnVec<TKey, TValue>::is_empty() const noexcept
{
    return _rows.empty();
}

template <typename TKey, typename TValue>
bool SortedTableOnVec<TKey, TValue>::consist(const TKey& Key) const noexcept 
{
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right) 
    {
        size_t mid = left + (right - left) / 2;
        if (_rows[mid].first == Key)
        {
            return true;
        }
        else if (_rows[mid].first < Key) 
        {
            left = mid + 1;
        }
        else 
        {
            right = mid;
        }
    }
    return false;
}

template <typename TKey, typename TValue>
size_t SortedTableOnVec<TKey, TValue>::size() const noexcept
{
    return _rows.size();
}