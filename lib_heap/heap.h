#pragma once 
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Heap
{
private:
    vector<T> heap;

    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int leftch(int i)
    {
        return 2 * i + 1;
    }
    int rightch(int i)
    {
        return 2 * i + 2;
    }
    void siftUp(int i)
    {
        while (i > 0 && heap[i] < heap[parent(i)])
        {
            swap(i, parent(i));
            i = parent(i);
        }
    }
    void siftDown(int i)
    {
        int n = heap.size();
        while (true)
        {
            int left = leftch(i);
            int right = rightch(i);
            int mn = i;
            if (left < n && heap[left] < heap[mn])
            {
                mn = left;
            }
            if (right < n && heap[right] < heap[mn])
            {
                mn = right;
            }
            if (mn == i)
            {
                break;
            }
            swap(i, mn);
            i = mn;
        }

    }
    void swap(int i, int j)
    {

        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

public:
    void insert(const T& value)
    {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }
    T pop()
    {
        if (heap.empty())
        {
            throw out_of_range("heap is empty");

        }
        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
        {
            siftDown(0);
        }
        return root;
    }

    void erase()
    {
        int ind = 0;
        heap[ind] = heap.back();
        heap.pop_back();
        if (ind < heap.size()) 
        {
            siftDown(ind);

        }
    }
    void print() const
    {
        for (const T& val : heap)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    bool is_empty() const
    {
        return heap.empty();
    }
    
};
