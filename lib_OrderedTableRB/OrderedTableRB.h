#pragma once
#include "ITable.h"
#include "RBTree.h"
template<typename TKey, typename TValue>
class OrderedTable : public ITable<TKey, TValue>
{
private:
    RBTree<TKey, TValue> _tree;

public:
    OrderedTable() = default;

    void insert(const TKey& Key, const TValue& Val) override
    {
        _tree.insert(Key, Val);
    }

    TValue find(const TKey& Key) const override
    {
        return _tree.find(Key);
    }

    void erase(const TKey& Key) override
    {
        _tree.erase(Key);
    }
   
    std::ostream& print(std::ostream& out) const noexcept override
    {
        _tree.print(out);
        return out;
    }

    bool is_empty() const noexcept override
    {
        return _tree.empty();
    }

    bool consist(const TKey& Key) const noexcept override
    {
        return _tree.contains(Key);
    }

    size_t size() const noexcept override
    {
        return _tree.size();
    }

    std::vector<std::pair<TKey, TValue>> toVector() const
    {
        return _tree.inorder();
    }
};