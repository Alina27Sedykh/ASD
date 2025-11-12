#include "Alg.h"
#include "DSV.h"
#include <stack>
#include <unordered_map>

bool check_breckets(std::string str) 
{
    std::stack<char> breckets_stack;

    std::unordered_map<char, char> brecket_pairs =
    {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    };

    for (char c : str) 
    {
        if (c == '(' || c == '[' || c == '{') 
        {
            breckets_stack.push(c);
        }
        else if (c == ')' || c == ']' ||  c == '}') 
        {
            if (breckets_stack.empty())
            {
                return false;
            }
            char top = breckets_stack.top();
            breckets_stack.pop();
            if (brecket_pairs[top]!=c)
            {
                return false;
            }
        }
    }
    return breckets_stack.empty();
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