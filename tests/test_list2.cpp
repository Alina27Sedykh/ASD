#include <gtest/gtest.h>
#include "../lib_list2/list2.h"

TEST(List2Iterator, IterateAndRead)
{
    List<int> list;
    for (int i = 1; i <= 10; ++i)
    {
        list.push_back(i);
    }

    int expected_val = 1;

    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }
}

TEST(List2Iterator, IterateAndModify)
{
    List<int> list;
    for (int i = 1; i <= 5; ++i)
    {
        list.push_back(i);
    }

    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        *it = (*it) * 10;
    }

    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_GE(*it, 10);
    }
}

TEST(List2Iterator, EmptyList)
{
    List<int> list;
    List<int>::Iterator it = list.begin();

    ASSERT_EQ(it, list.end());
    EXPECT_THROW(*it, std::out_of_range);
}