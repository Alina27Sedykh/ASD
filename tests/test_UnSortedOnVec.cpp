#include <gtest/gtest.h>
#include "../lib_UnSortedTableOnVec/UnSortedTableOnVec.h"
#include "../lib_SortedTableOnVec/SortedTableOnVec.h"

TEST(UnsortedTableTest, InsertAndFind)
{
    UnSortedTableOnVec<int, std::string> myITable;

    myITable.insert(1, "one");
    myITable.insert(2, "two");
    myITable.insert(3, "three");

    EXPECT_EQ(myITable.size(), 3);
    EXPECT_EQ(myITable.find(1), "one");
    EXPECT_EQ(myITable.find(2), "two");
    EXPECT_EQ(myITable.find(3), "three");
}

TEST(UnsortedTableTest, InsertUpdatesExistingKey)
{
    UnSortedTableOnVec<int, std::string> table;

    table.insert(1, "one");
    table.insert(1, "ONE");

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "ONE");
}

TEST(UnsortedTableTest, FindThrowsForNonexistentKey)
{
    UnSortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    EXPECT_THROW(table.find(2), std::runtime_error);
}

TEST(UnsortedTableTest, EraseRemovesElement)
{
    UnSortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);

    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(UnsortedTableTest, EraseNonexistentKeyDoesNothing)
{
    UnSortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    table.erase(999);

    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.consist(1));
}

TEST(UnsortedTableTest, IsEmpty)
{
    UnSortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());

    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());

    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}

TEST(UnsortedTableTest, Consist)
{
    UnSortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
}

TEST(UnsortedTableTest, Size)
{
    UnSortedTableOnVec<int, std::string> table;
    EXPECT_EQ(table.size(), 0);

    table.insert(1, "one");
    EXPECT_EQ(table.size(), 1);

    table.insert(2, "two");
    EXPECT_EQ(table.size(), 2);

    table.erase(1);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnsortedTableTest, Print)
{
    UnSortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    std::stringstream ss;
    table.print(ss);
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Key: 1, Value: one") != std::string::npos);
    EXPECT_TRUE(output.find("Key: 2, Value: two") != std::string::npos);
}

TEST(UnsortedTableTest, StringKeys)
{
    UnSortedTableOnVec<std::string, int> table;
    table.insert("apple", 5);
    table.insert("banana", 3);

    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table.find("apple"), 5);
    EXPECT_EQ(table.find("banana"), 3);
}

TEST(UnsortedTableTest, ComplexOperations)
{
    UnSortedTableOnVec<int, std::string> table;

    // Вставка нескольких элементов
    for (int i = 0; i < 10; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_EQ(table.size(), 10);

    // Проверка наличия
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(table.consist(i));
    }

    // Обновление четных элементов
    for (int i = 0; i < 10; i += 2) {
        table.insert(i, "UPDATED_" + std::to_string(i));
    }
    EXPECT_EQ(table.size(), 10);

    // Проверка обновленных значений
    for (int i = 0; i < 10; i += 2) {
        EXPECT_EQ(table.find(i), "UPDATED_" + std::to_string(i));
    }
    for (int i = 1; i < 10; i += 2) {
        EXPECT_EQ(table.find(i), "value_" + std::to_string(i));
    }

    // Удаление половины
    for (int i = 0; i < 10; i += 2) {
        table.erase(i);
    }
    EXPECT_EQ(table.size(), 5);

    // Проверка оставшихся
    for (int i = 0; i < 10; i += 2) {
        EXPECT_FALSE(table.consist(i));
    }
    for (int i = 1; i < 10; i += 2) {
        EXPECT_TRUE(table.consist(i));
    }
}