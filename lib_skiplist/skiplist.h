#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip> 
#include <list.h>
#include <sstream>
template <typename TKey, typename TValue>
struct SkipListNode
{
    std::pair<TKey, TValue> data;
    int level;
    SkipListNode<TKey, TValue>** next;
    SkipListNode(const TKey& key, const TValue& value, int lvl) : level(lvl)
    {
        data.first = key;
        data.second = value;
        next = new SkipListNode<TKey, TValue>* [lvl + 1];
        for (int i = 0; i <= lvl; i++)
        {
            next[i] = nullptr;
        }

    }
    ~SkipListNode()
    {
        delete[] next;
    }

};
template <typename TKey, typename TValue>
class SkipList
{
    List<SkipListNode<TKey, TValue>*> head;
    size_t size;
    int max_level;
    size_t generation_level()
    {
        int lvl = 0;
        while (rand() % 101 < 50 && lvl < max_level)
        {
            lvl++;

        }
        return lvl;
    }
public:
    SkipList(int max_lvl = 16) : max_level(max_lvl), size(0) {}
    ~SkipList()
    {
        clear();
        while (!head.is_empty())
        {
            SkipListNode<TKey, TValue>* node = head.front();
            head.pop_front();
            delete node;
        }
    }
   
    void insert(const TKey& key, const TValue& value) 
    {
        int new_level = generation_level();
        SkipListNode<TKey,TValue>* new_node = new SkipListNode<TKey, TValue>(key, value, new_level);
        if (head.is_empty())
        {
            SkipListNode<TKey, TValue>* head_node = new SkipListNode<TKey, TValue>(TKey(), TValue(), max_level);
            head.push_front(head_node);

            for (int i = 0; i <= new_level; i++)
            {
                new_node->next[i] = nullptr;
                head_node->next[i] = new_node;
            }
            size++;
            return;
        }

        SkipListNode<TKey, TValue>* head_node = head.front();
        std::vector<SkipListNode<TKey, TValue>*> prev(new_level + 1, nullptr);
        SkipListNode<TKey, TValue>* current = head_node;
        for (int i = new_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->data.first < key)
            {
                current = current->next[i];
            }
            prev[i] = current;  
        }
        
        current = current->next[0];
        if (current != nullptr && current->data.first == key)
        {
            current->data.second = value;
            delete new_node;  
            return;
        }
        for (int i = 0; i <= new_level; i++)
        {
            if (prev[i] != nullptr)
            {
                new_node->next[i] = prev[i]->next[i];
                prev[i]->next[i] = new_node;
            }
            else
            {
                new_node->next[i] = head_node->next[i];
                head_node->next[i] = new_node;
            }
        }

        size++;
    }
    void print(std::ostream& out = std::cout) const
    {
        if (head.is_empty())
        {
            return;
        }
        SkipListNode<TKey, TValue>* head_node = head.front();
        std::vector<SkipListNode<TKey, TValue>*> nodes;
        SkipListNode<TKey, TValue>* current = head_node->next[0];
        while (current != nullptr)
        {
            nodes.push_back(current);
            current = current->next[0];
        }
        for (auto node : nodes)
        {
            out << "(";
            out << std::setw(10) << std::right;
            std::cout << node->data.first;
            out << " : ";
            out << std::left << std::setw(20);
            out << node->data.second;
            out << ")";
            for (int i = 0; i <= max_level; i++)
            {
                if (i <= node->level)
                    out << "[*] ";
                else
                    out << "[ ] ";
            }
            out << std::endl;
        }
    }
    void clear()
    {
        if (head.is_empty())
        {
            return;
        }
        SkipListNode<TKey, TValue>* head_node = head.front();
        SkipListNode<TKey, TValue>* current = head_node->next[0];

        while (current != nullptr)
        {
            SkipListNode<TKey, TValue>* next = current->next[0];//сохраняю указатель на следующий узел 
            delete current;
            current = next;
        }
        for (int i = 0; i <= max_level; i++)
        {
            head_node->next[i] = nullptr;
        }

        size = 0;
    }

};

