#include <gtest/gtest.h>
#include "../lib_list2/list2.h"


TEST(List2Iterator, IterateEmpty)
{
    List2<int> list;

    int iterationCount = 0;
    for (List2<int>::Iterator2 it = list.begin(); it != list.end(); ++it)
    {
        iterationCount++;
    }
    EXPECT_EQ(iterationCount, 0);
}

TEST(List2Iterator, IterateAndRead)
{
    List2<int> list;
    for (int i = 1; i <= 5; ++i)
    {
        list.push_back(i * 10); 
    }

    int expected_val = 10;
    int count = 0;

    for (List2<int>::Iterator2 it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected_val);
        expected_val += 10;
        count++;
    }
    EXPECT_EQ(count, 5);
}

TEST(List2Iterator, IterateAndModify)
{
    List2<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);


    List2<int>::Iterator2 it = list.begin();
    *it = 100;
    ++it;
    *it = 200;
    ++it;
    *it = 300;

    it = list.begin();
    EXPECT_EQ(*it, 100);
    ++it;
    EXPECT_EQ(*it, 200);
    ++it;
    EXPECT_EQ(*it, 300);
}