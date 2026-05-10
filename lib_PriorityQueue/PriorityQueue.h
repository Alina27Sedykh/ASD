#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include"heap.h"
using namespace std;

enum class Priority
{
    PAID = 1,        
    APPOINTMENT = 2, 
    WALK_IN = 3      
};

template<typename T>
struct PriorityNode
{
    T name;
    Priority priority;
    int order;

    PriorityNode(const string& n, Priority p, int ord) : name(n), priority(p), order(ord) {}
    bool operator<(const PriorityNode& other) const
    {
        if (priority != other.priority)
        {
            return static_cast<int>(priority) < static_cast<int>(other.priority);
        }
        return order < other.order;
    }


    friend ostream& operator<<(ostream& os, const PriorityNode<T>& node)
    {
        os << node.name << "(" << static_cast<int>(node.priority) << "," << node.order << ")";
        return os;
    }
};

template<typename T>
class PriorityQueue : public Heap<PriorityNode<T>>
{
private:
    int nextOrder = 0;  

public:
    
    void enqueue(const T& name, Priority priority)
    {
        insert(PriorityNode<T>(name, priority, nextOrder++));
    }

    T dequeue()
    {
        return pop().name;
    }
    bool empty() const
    {
        return is_empty();
    }

    void show() const
    {
        print();
    }
};


