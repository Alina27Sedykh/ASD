#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>

class DSV
{
    int* _parent;
    int _size;
    int* _rank;
public:
    DSV(int size);
    DSV(const DSV& other); 
    DSV& operator=(const DSV& other); 
    void unite(int x1, int x2);
    int find(int x);
    bool connected(int x1, int x2);
    int size() const;
    ~DSV();
};

