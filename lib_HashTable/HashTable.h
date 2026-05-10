#include "ITable.h"
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>
template<typename TValue>
class HashTableChaining : public ITable<std::string, TValue>
{
private:
    std::vector<std::list<std::pair<std::string, TValue>>> _rows;
    size_t _size;  

    size_t h(const std::string& key) const noexcept 
    {
        return std::hash<std::string>{}(key) % _rows.size();
    }

    void resize()
    {
        std::vector<std::list<std::pair<std::string, TValue>>> old_rows;
        old_rows.swap(_rows);
        _rows.resize(old_rows.size() * 2);
        _size = 0;

        for (const auto& bucket : old_rows) 
        {
            for (const auto& pair : bucket) 
            {
                insert(pair.first, pair.second);
            }
        }
    }

public:
    HashTableChaining(size_t size = 16) : _rows(size), _size(0) {}

    void insert(const std::string& Key, const TValue& Val) override 
    {
        // Проверка на необходимость ресайза
        if (static_cast<double>(_size) / _rows.size() > 0.75) {
            resize();
        }

        size_t index = h(Key);

        // Ищем ключ в цепочке
        for (auto& pair : _rows[index]) 
        {
            if (pair.first == Key)
            {
                pair.second = Val;  // обновляем значение
                return;
            }
        }

        // Не нашли - добавляем новую пару
        _rows[index].push_back({ Key, Val });
        _size++;
    }

    TValue find(const std::string& Key) const override
    {
        size_t index = h(Key);

        for (const auto& pair : _rows[index])
        {
            if (pair.first == Key)
            {
                return pair.second;
            }
        }
        throw std::runtime_error("Key not found: " + Key);
    }

    void erase(const std::string& Key) override
    {
        size_t index = h(Key);
        auto& bucket = _rows[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == Key)
            {
                bucket.erase(it);
                _size--;
                return;
            }
        }
        throw std::runtime_error("Key not found for erase: " + Key);
    }

    std::ostream& print(std::ostream& out) const noexcept override
    {
        for (size_t i = 0; i < _rows.size(); ++i) 
        {
            if (!_rows[i].empty()) 
            {
                out << "Bucket " << i << ": ";
                for (const auto& pair : _rows[i]) 
                {
                    out << "\"" << pair.first << "\" -> " << pair.second << "; ";
                }
                out << std::endl;
            }
        }
        return out;
    }

    bool is_empty() const noexcept override
    {
        return _size == 0;
    }

    bool consist(const std::string& Key) const noexcept override
    {
        size_t index = h(Key);
        for (const auto& pair : _rows[index])
        {
            if (pair.first == Key) 
            {
                return true;
            }
        }
        return false;
    }

    size_t size() const noexcept override 
    {
        return _size;
    }
};
//#pragma once
//#include "ITable.h"
//#include "list.h"
//#include <vector>
//#include <functional>
//#include <stdexcept>
//#include <sstream>
//#include <string>
//
//template<typename TValue>
//class HashTableC : public ITable<std::string, TValue>
//{
//private:
//    std::vector<List<std::pair<std::string, TValue>>> _rows;
//    size_t _size;
//
//    // Простая хеш-функция для строк
//    size_t h(const std::string& key) const noexcept;
//
//public:
//    // Конструктор
//    HashTableC(size_t size = 100);
//
//    // Деструктор
//    ~HashTableC() = default;
//
//    // Методы ITable
//    void insert(const std::string& Key, const TValue& Val) override;
//    TValue find(const std::string& Key) const override;
//    void erase(const std::string& Key) override;
//    std::ostream& print(std::ostream& out) const noexcept override;
//    bool is_empty() const noexcept override;
//    bool consist(const std::string& Key) const noexcept override;
//    size_t size() const noexcept override;
//
//   
//    void clear();
//    std::vector<std::pair<std::string, TValue>> get_elements() const;
//};
//
//// ==================== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================
//
//template<typename TValue>
//size_t HashTableC<TValue>::h(const std::string& key) const noexcept
//{
//    size_t hash = 0;
//    for (char c : key)
//    {
//        hash = hash * 31 + c;
//    }
//    return hash % _rows.size();
//}
//
//// ==================== КОНСТРУКТОР ====================
//
//template<typename TValue>
//HashTableC<TValue>::HashTableC(size_t size) : _rows(size), _size(0) {}
//template<typename TValue>
//void HashTableC<TValue>::insert(const std::string& Key, const TValue& Val)
//{
//    size_t index = h(Key);
//
//    // Ищем ключ в списке
//    int pos = 0;
//    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it)
//    {
//        if ((*it).first == Key)
//        {
//            // Ключ найден - обновляем значение
//            (*it).second = Val;
//            return;
//        }
//        pos++;
//    }
//
//    // Ключ не найден - добавляем новую пару
//    std::pair<std::string, TValue> new_data = { Key, Val };
//    _rows[index].push_back(new_data);
//    _size++;
//}
//
//template<typename TValue>
//TValue HashTableC<TValue>::find(const std::string& Key) const
//{
//    size_t index = h(Key);
//
//    
//    auto& rows_const = const_cast<std::vector<List<std::pair<std::string, TValue>>>&>(_rows);
//
//    for (auto it = rows_const[index].begin(); it != rows_const[index].end(); ++it)
//    {
//        if ((*it).first == Key)
//        {
//            return (*it).second;
//        }
//    }
//
//    throw std::logic_error("Key not found");
//}
//
//template<typename TValue>
//void HashTableC<TValue>::erase(const std::string& Key)
//{
//    size_t index = h(Key);
//
//    int pos = 0;
//    for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it)
//    {
//        if ((*it).first == Key)
//        {
//            _rows[index].erase(pos);
//            _size--;
//            return;
//        }
//        pos++;
//    }
//
//    throw std::logic_error("Key not found");
//}
//
//template<typename TValue>
//std::ostream& HashTableC<TValue>::print(std::ostream& out) const noexcept
//{
//    if (is_empty())
//    {
//        out << "empty";
//        return out;
//    }
//
//    out << "HashTableC(size=" << _size << "): ";
//
//    bool first = true;
//    for (size_t i = 0; i < _rows.size(); i++)
//    {
//        auto& rows_const = const_cast<std::vector<List<std::pair<std::string, TValue>>>&>(_rows);
//        for (auto it = rows_const[i].begin(); it != rows_const[i].end(); ++it)
//        {
//            if (!first) out << " ";
//            out << "(" << (*it).first << ":" << (*it).second << ")";
//            first = false;
//        }
//    }
//
//    return out;
//}
//
//template<typename TValue>
//bool HashTableC<TValue>::is_empty() const noexcept
//{
//    return _size == 0;
//}
//
//template<typename TValue>
//bool HashTableC<TValue>::consist(const std::string& Key) const noexcept
//{
//    size_t index = h(Key);
//
//    auto& rows_const = const_cast<std::vector<List<std::pair<std::string, TValue>>>&>(_rows);
//    for (auto it = rows_const[index].begin(); it != rows_const[index].end(); ++it)
//    {
//        if ((*it).first == Key)
//        {
//            return true;
//        }
//    }
//
//    return false;
//}
//
//template<typename TValue>
//size_t HashTableC<TValue>::size() const noexcept
//{
//    return _size;
//}
//
//template<typename TValue>
//void HashTableC<TValue>::clear()
//{
//    for (auto& row : _rows)
//    {
//        row.clear();
//    }
//    _size = 0;
//}
//
//template<typename TValue>
//std::vector<std::pair<std::string, TValue>> HashTableC<TValue>::get_elements() const
//{
//    std::vector<std::pair<std::string, TValue>> result;
//
//    for (size_t i = 0; i < _rows.size(); i++)
//    {
//        auto& rows_const = const_cast<std::vector<List<std::pair<std::string, TValue>>>&>(_rows);
//        for (auto it = rows_const[i].begin(); it != rows_const[i].end(); ++it)
//        {
//            result.push_back(*it);
//        }
//    }
//
//    return result;
//}
////#pragma once
//#include "ITable.h"
//#include "list.h"
//#include <vector>
//#include <functional>
//#include <stdexcept>
//#include <sstream>
//#include <string>
//
//template<typename TValue>
//class HashTableC : public ITable<std::string, TValue>
//{
//private:
//    std::vector<List<std::pair<std::string, TValue>>> _rows;
//    size_t h(const std::string& key) const noexcept;
//public:
//    HashTableC(size_t size = 100) : _rows(size) {}
//};
//void HashTableC::insert(std::string Key, TValue val)
//{
//    std::pair<std::string, TValue>;
//    new_data = { key,Val }
//    size_t h = h(key);
//    for (auto it = rows[h].begin());
//    it != _rows[h].end() it == {
//        if (it->first == key
//            ///
//            )
//            _rows[h].push_back(new_data);
//    }
//
//}
//void HashTableC::erase(std::string Key)
//{
//    size_t h = h(key);
//    for (auto it = _rows = _rows[h].begin())
//        if (it->first == key) {
//            _rows[h].erase(pos);
//            return
//        }
//    pos++;
//}thow ...
//
//}