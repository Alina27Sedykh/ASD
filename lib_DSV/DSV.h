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

DSV::DSV(int size) : _size(size)
{
    _parent = new int[_size];
    _rank = new int[_size];
    for (int i = 0; i < _size; i++)
    {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

DSV::DSV(const DSV& other) : _size(other._size)
{
    _parent = new int[_size];
    _rank = new int[_size];
    for (int i = 0; i < _size; i++)
    {
        _parent[i] = other._parent[i];
        _rank[i] = other._rank[i];
    }
}

DSV& DSV::operator=(const DSV& other)
{
    if (this != &other) 
    {
        delete[] _parent;
        delete[] _rank;

        _size = other._size;
        _parent = new int[_size];
        _rank = new int[_size];

        for (int i = 0; i < _size; i++)
        {
            _parent[i] = other._parent[i];
            _rank[i] = other._rank[i];
        }
    }
    return *this;
}

void DSV::unite(int x1, int x2)
{
    int root1 = find(x1);
    int root2 = find(x2);

    if (root1 == root2) 
    {
        return;

    }
    if (_rank[root1] < _rank[root2])
    {
        _parent[root1] = root2;
    }
    else if (_rank[root1] > _rank[root2])
    {
        _parent[root2] = root1;
    }
    else
    {
        _parent[root2] = root1;
        _rank[root1]++;
    }
}

int DSV::find(int x)
{
    if (_parent[x] != x)
    {
        _parent[x] = find(_parent[x]); 
    }
    return _parent[x];
}

bool DSV::connected(int x1, int x2)
{
    return find(x1) == find(x2);
}

int DSV::size() const
{
    return _size;
}

DSV::~DSV()
{
    delete[] _parent;
    delete[] _rank;
}
int countIslands(const std::vector<std::vector<int>>& matrix) 
{
    if (matrix.empty() || matrix[0].empty())
    {
        return 0;
    }
    int N = matrix.size();
    DSV dsv(N * N);
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (matrix[i][j] == 1) 
            {
                int currentIndex = i * N + j;
                for (const auto& dir : directions) 
                {
                    int ni = i + dir.first;
                    int nj = j + dir.second;

                    if (ni >= 0 && ni < N && nj >= 0 && nj < N && matrix[ni][nj] == 1) 
                    {
                        int neighborIndex = ni * N + nj;
                        dsv.unite(currentIndex, neighborIndex);
                    }
                }
            }
        }
    }
    std::unordered_set<int> uniqueRoots;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] == 1)
            {
                int index = i * N + j;
                int root = dsv.find(index);
                uniqueRoots.insert(root);
            }
        }
    }

    return uniqueRoots.size();
}
