#pragma once
#include "BSTree.h"
#include "ITable.h"
#include <sstream>

template<typename TKey, typename TValue>
class SortedTable : public ITable<TKey, TValue>
{
private:
    BSTree<TKey, TValue> _tree;

public:
    SortedTable() = default;
    ~SortedTable() = default;

    void insert(const TKey& Key, const TValue& Val) override
    {
        _tree.insert(Key, Val);
    }

    TValue find(const TKey& Key) const override
    {
        return const_cast<BSTree<TKey, TValue>&>(_tree).find(Key);
    }

    void erase(const TKey& Key) override
    {
        _tree.erase(Key);
    }

    std::ostream& print(std::ostream& out) const noexcept override
    {
        if (_tree.is_empty())
        {
            out << "empty";
            return out;
        }

        out << "SortedTable(size=" << _tree.size() << "): ";
        out << _tree.to_string(true); 

        return out;
    }

    bool is_empty() const noexcept override
    {
        return _tree.is_empty();
    }

    bool consist(const TKey& Key) const noexcept override
    {
        return _tree.contains(Key);
    }

    size_t size() const noexcept override
    {
        return _tree.size();
    }
};