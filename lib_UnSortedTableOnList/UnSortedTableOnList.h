#pragma once
#include "ITable.h"
#include "list.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

template<typename TKey, typename TValue>
class UnsortedTableOnList : public ITable<TKey, TValue>
{
private:
    List<std::pair<TKey, TValue>> _list;

public:
    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() = default;
    void insert(const TKey& Key, const TValue& Val) override
    {
        auto it = _list.begin();
        int pos = 0;
        while (it != _list.end())
        {
            if ((*it).first == Key)
            {
                (*it).second = Val;
                return;
            }
            ++it;
            ++pos;
        }
        _list.push_back({ Key, Val });
    }
    TValue find(const TKey& Key) const override
    {
        auto it = _list.begin();
        while (it != _list.end())
        {
            if ((*it).first == Key)
                return (*it).second;
            ++it;
        }
        throw std::logic_error("Key not found");
    }
    void erase(const TKey& Key) override
    {
        auto it = _list.begin();
        int pos = 0;
        while (it != _list.end())
        {
            if ((*it).first == Key)
            {
                _list.erase(pos);
                return;
            }
            ++it;
            ++pos;
        }
        throw std::logic_error("Key not found");
    }
    std::ostream& print(std::ostream& out) const noexcept override
    {
        if (_list.is_empty())
        {
            out << "empty";
            return out;
        }

        out << "UnsortedTableOnList(size=" << _list.size() << "): ";

        auto it = const_cast<List<std::pair<TKey, TValue>>&>(_list).begin();
        bool first = true;
        while (it != const_cast<List<std::pair<TKey, TValue>>&>(_list).end())
        {
            if (!first) out << " ";
            out << "(" << (*it).first << ":" << (*it).second << ")";
            first = false;
            ++it;
        }

        return out;
    }
    bool is_empty() const noexcept override
    {
        return _list.is_empty();
    }
    bool consist(const TKey& Key) const noexcept override
    {
        auto it = const_cast<List<std::pair<TKey, TValue>>&>(_list).begin();
        while (it != const_cast<List<std::pair<TKey, TValue>>&>(_list).end())
        {
            if ((*it).first == Key)
                return true;
            ++it;
        }
        return false;
    }
    size_t size() const noexcept override
    {
        return _list.size();
    }
    void clear()
    {
        _list.clear();
    }
};