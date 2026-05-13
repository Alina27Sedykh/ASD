#pragma once
#include "ITable.h"
#include "AVLTree.h"

template <typename TKey, typename TValue>
class OrderedTableAVL : public ITable<TKey, TValue> 
{
private:
    AVLTree<TKey, TValue> _tree;

public:
    virtual void insert(const TKey& Key, const TValue& Val) override 
    {
        _tree.insert(Key, Val);
    }

    virtual TValue find(const TKey& Key) const override
    {
        return _tree.find(Key);
    }
    virtual void erase(const TKey& Key) override 
    {
        _tree.erase(Key);
    }

    virtual std::ostream& print(std::ostream& out) const noexcept override 
    {
        _tree.print(out);
        return out;
    }
    virtual bool is_empty() const noexcept override 
    {
        return _tree.isEmpty();
    }

    virtual bool consist(const TKey& Key) const noexcept override 
    {
        return _tree.contains(Key);
    }

    virtual size_t size() const noexcept override 
    {
        return _tree.size();
    }
    virtual ~OrderedTableAVL() override {}
};