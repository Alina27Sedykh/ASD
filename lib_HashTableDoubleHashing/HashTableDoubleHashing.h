#pragma once
#include "ITable.h"
#include <vector>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <string>

template<typename TValue>
class HashTableDoubleHashing : public ITable<std::string, TValue>
{
private:
    struct Entry 
    {
        std::string key;
        TValue value;
        bool isOccupied;  
        bool isDeleted;   

        Entry() : isOccupied(false), isDeleted(false) {}
        Entry(const std::string& k, const TValue& v): key(k), value(v), isOccupied(true), isDeleted(false) {}
    };

    std::vector<Entry> _table;
    size_t _size;
    size_t _capacity;
    size_t hash1(const std::string& key) const noexcept
    {
        size_t h = 0;
        for (char c : key)
        {
            h = h * 31 + static_cast<size_t>(c);
        }
        return h % _capacity;
    }
    size_t hash2(const std::string& key) const noexcept
    {
        size_t h = 0;
        for (char c : key) {
            h = h * 37 + static_cast<size_t>(c);
        }
        return (h % (_capacity - 1)) | 1;
    }

    size_t probe(const std::string& key, size_t i) const noexcept
    {
        return (hash1(key) + i * hash2(key)) % _capacity;
    }

    void resize()
    {
        size_t oldCapacity = _capacity;
        _capacity = _capacity * 2 + 1;  
        std::vector<Entry> oldTable = std::move(_table);

        _table.clear();
        _table.resize(_capacity);
        _size = 0;

        for (size_t i = 0; i < oldCapacity; ++i)
        {
            if (oldTable[i].isOccupied && !oldTable[i].isDeleted)
            {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
    }

public:
    HashTableDoubleHashing(size_t capacity = 101) : _capacity(capacity), _size(0)
    {
        _table.resize(_capacity);
    }

    virtual void insert(const std::string& Key, const TValue& Val) override
    {
        if (_size * 10 >= _capacity * 7) 
        {
            resize();
        }

        size_t i = 0;
        size_t index = probe(Key, i);

        while (_table[index].isOccupied && !_table[index].isDeleted) 
        {
            if (_table[index].key == Key) 
            {
                return;
            }
            ++i;
            index = probe(Key, i);
        }
        _table[index] = Entry(Key, Val);
        _size++;
    }

    virtual TValue find(const std::string& Key) const override
    {
        size_t i = 0;
        size_t index = probe(Key, i);

        while (_table[index].isOccupied)
        {
            if (!_table[index].isDeleted && _table[index].key == Key) 
            {
                return _table[index].value;
            }
            ++i;
            index = probe(Key, i);
        }

        throw std::out_of_range("Key not found: " + Key);
    }

    virtual void erase(const std::string& Key) override
    {
        size_t i = 0;
        size_t index = probe(Key, i);

        while (_table[index].isOccupied)
        {
            if (!_table[index].isDeleted && _table[index].key == Key) 
            {
                _table[index].isDeleted = true;
                _size--;
                return;
            }
            ++i;
            index = probe(Key, i);
        }

        throw std::out_of_range("Key not found: " + Key);
    }

    virtual std::ostream& print(std::ostream& out) const noexcept override
    {
        for (size_t i = 0; i < _capacity; ++i)
        {
            if (_table[i].isOccupied && !_table[i].isDeleted)
            {
                out << "[" << i << "]: " << _table[i].key << " : " << _table[i].value << std::endl;
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
        size_t i = 0;
        size_t index = probe(Key, i);

        while (_table[index].isOccupied) 
        {
            if (!_table[index].isDeleted && _table[index].key == Key) 
            {
                return true;
            }
            ++i;
            index = probe(Key, i);
        }

        return false;
    }

    virtual size_t size() const noexcept override
    {
        return _size;
    }

    virtual ~HashTableDoubleHashing() override {}
};