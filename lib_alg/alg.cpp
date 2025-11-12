#include "Alg.h"
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

