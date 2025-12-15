#ifndef ALG_H
#define ALG_H

#include <string>
#include <vector>
#include "List.h"

bool check_breckets(std::string str);
int countIslands(const std::vector<std::vector<int>>& matrix);

template <typename T>
Node<T>* has_cycle_problem_node(List<T>& list)
{
    if (list.head() == nullptr || list.head()->next == nullptr)
        return nullptr;

    Node<T>* slow = list.head();
    Node<T>* fast = list.head();

    bool has_cycle = false;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle)
        return nullptr;

    slow = list.head();
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}


template <typename T>
bool has_cycle_hare_and_turtle(List<T>& list)
{
    if (list.head() == nullptr || list.head()->next == nullptr)
        return false;

    Node<T>* slow = list.head();
    Node<T>* fast = list.head();

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}
template <typename T>
bool has_cycle_reverse_pointers(List<T>& list)
{
    if (list.head() == nullptr || list.head()->next == nullptr)
        return false;

    Node<T>* current = list.head();
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
    Node<T>* start = list.head();
    bool has_cycle = false;

    // »спользуем временный указатель дл€ отслеживани€ начала
    Node<T>* temp_start = start;

    while (current != nullptr)
    {
        if (current->next == temp_start)
        {
            // ќбнаружили цикл
            has_cycle = true;
            break;
        }

        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // ¬осстанавливаем список после проверки
    // ƒл€ этого нужно развернуть список обратно
    current = prev;
    prev = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return has_cycle;
}


//template<typename T>
//bool has_cycle_reverse_pointers(List<T>& list)
//{
//    if (list.is_empty()) return false;
//    if (list.tail()->next == list.head()) {
//        return true;
//    }
//    Node<T>* current = list.head();
//    Node<T>* prev = nullptr;
//    Node<T>* next = nullptr;
//    bool cycle_found = false;
//    while (current != nullptr)
//    {
//        next = current->next; //save pointer on next node
//        current->next = prev; //reverse pointer for curr node
//        prev = current; //move pointer on curr node
//        current = next; // jump next node befote reverse pointer
//        if (current == list.head())
//        {
//            return true;
//        }
//        return false;
//    }
//}
#endif