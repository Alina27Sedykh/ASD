#include <gtest/gtest.h>
#include "../lib_list2/list2.h"

// Тест 1: Итерирование пустого списка
TEST(ListIterator, IterateEmptyList)
{
    List<int> list;

    EXPECT_EQ(list.begin(), list.end());

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Тест 2: Базовый итератор на чтение
TEST(ListIterator, BasicIterateAndRead)
{
    List<int> list;
    list.push_back(1);

    List<int>::Iterator it = list.begin();
    EXPECT_NE(it, list.end());
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(it, list.end());
}

// Тест 3: Базовый итератор на запись
TEST(ListIterator, BasicIterateAndModify)
{
    List<int> list;
    list.push_back(5);

    List<int>::Iterator it = list.begin();
    *it = 10;

    EXPECT_EQ(*list.begin(), 10);
}