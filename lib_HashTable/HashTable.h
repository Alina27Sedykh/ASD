#pragma once
#include "ITable.h"
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <string>

template<typename TValue>
class HashTableChaining : public ITable<std::string, TValue>
{
private:
    std::vector<std::list<std::pair<std::string, TValue>>> _table;
    size_t _size;

    size_t hash(const std::string& key) const noexcept
    {
        size_t h = 0;
        for (char c : key) 
        {
            h = h * 31 + static_cast<size_t>(c);
        }
        return h % _table.size();
    }

public:
    HashTableChaining(size_t capacity = 101) : _table(capacity), _size(0) {}

    virtual void insert(const std::string& Key, const TValue& Val) override
    {
        size_t index = hash(Key);
        for (auto& pair : _table[index]) 
        {
            if (pair.first == Key) 
            {
                return;
            }
        }
        _table[index].push_back({ Key, Val });
        _size++;
    }

    virtual TValue find(const std::string& Key) const override
    {
        size_t index = hash(Key);

        for (const auto& pair : _table[index]) 
        {
            if (pair.first == Key) 
            {
                return pair.second;
            }
        }

        throw std::out_of_range("Key not found: " + Key);
    }

    virtual void erase(const std::string& Key) override
    {
        size_t index = hash(Key);
        auto& chain = _table[index];

        for (auto it = chain.begin(); it != chain.end(); ++it)
        {
            if (it->first == Key) 
            {
                chain.erase(it);
                _size--;
                return;
            }
        }

        throw std::out_of_range("Key not found: " + Key);
    }

    virtual std::ostream& print(std::ostream& out) const noexcept override
    {
        for (size_t i = 0; i < _table.size(); ++i) 
        {
            if (!_table[i].empty()) 
            {
                out << "[" << i << "]: ";
                for (const auto& pair : _table[i])
                {
                    out << "(" << pair.first << ":" << pair.second << ") ";
                }
                out << std::endl;
            }
        }
        return out;
    }

    virtual bool is_empty() const noexcept override
    {
        return _size == 0;
    }

    virtual bool consist(const std::string& Key) const noexcept override
    {
        size_t index = hash(Key);
        for (const auto& pair : _table[index])
        {
            if (pair.first == Key) 
            {
                return true;
            }
        }
        return false;
    }

    virtual size_t size() const noexcept override
    {
        return _size;
    }

    virtual ~HashTableChaining() override {}
};
//template<class T>
//HashTableChaining<T> merge_dict(const std::vector<std::pair<std::string, T>>& dict1, const std::vector<std::pair<std::string, T>>& dict2)
//{
//    HashTableChaining<T> result;
//    for (const auto& pair : dict1) 
//    {
//        result.insert(pair.first, pair.second);
//    }
//
//    for (const auto& pair : dict2) 
//    {
//        if (!result.consist(pair.first)) 
//        {
//            result.insert(pair.first, pair.second);
//        }
//    }
//
//    return result;
//}