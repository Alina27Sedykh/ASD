#include <gtest/gtest.h>
#include "../lib_list2/list2.h"


TEST(List2Iterator, IterateEmpty)
{
    DoubleLinkedList<int> list;

    int iterationCount = 0;
    for (DoubleLinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        iterationCount++;
    }
    EXPECT_EQ(iterationCount, 0);
}

TEST(List2Iterator, IterateAndRead)
{
    DoubleLinkedList<int> list;
    for (int i = 1; i <= 5; ++i)
    {
        list.push_back(i * 10); 
    }

    int expected_val = 10;
    int count = 0;

    for (DoubleLinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected_val);
        expected_val += 10;
        count++;
    }
    EXPECT_EQ(count, 5);
}

TEST(List2Iterator, IterateAndModify)
{
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);


    DoubleLinkedList<int>::Iterator it = list.begin();
    *it = 100;
    ++it;
    *it = 200;
    ++it;
    *it = 300;
}
