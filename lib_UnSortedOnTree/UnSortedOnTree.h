#pragma once
#include "ITable.h"
#include "Tree.h"
#include <sstream>

template<typename TKey, typename TValue>
class UnorderedTable : public ITable<TKey, TValue>
{
private:
    Tree<TKey, TValue> _tree;

public:
    UnorderedTable() = default;
    ~UnorderedTable() = default;

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
        if (_tree.is_empty())
        {
            out << "empty";
            return out;
        }

        auto elements = const_cast<Tree<TKey, TValue>&>(_tree).get_elements();
        out << "Tree(size=" << _tree.size() << "): ";

        for (size_t i = 0; i < elements.size(); i++)
        {
            if (i > 0) out << " ";
            out << "(" << elements[i].first << ":" << elements[i].second << ")";
        }

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

    void print_preorder() const { _tree.print_preorder(); }
    void print_inorder() const { _tree.print_inorder(); }
    void print_postorder() const { _tree.print_postorder(); }
    void print_levelorder() const { _tree.print_levelorder(); }
};