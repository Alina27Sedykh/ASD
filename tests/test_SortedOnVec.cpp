#include <gtest/gtest.h>
#include "../lib_SortedTableOnVec/SortedTableOnVec.h"
TEST(SortedTableTest, InsertAndFind)
{
    SortedTableOnVec<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(4, "four");

    EXPECT_EQ(table.size(), 5);
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.find(4), "four");
    EXPECT_EQ(table.find(5), "five");
}

TEST(SortedTableTest, InsertUpdatesExistingKey)
{
    SortedTableOnVec<int, std::string> table;

    table.insert(1, "one");
    table.insert(1, "ONE");

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "ONE");
}

TEST(SortedTableTest, FindThrowsForNonexistentKey)
{
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    EXPECT_THROW(table.find(2), std::runtime_error);
}

TEST(SortedTableTest, EraseRemovesElement)
{
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);

    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(SortedTableTest, EraseNonexistentKeyDoesNothing)
{
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    table.erase(999);

    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.consist(1));
}

TEST(SortedTableTest, IsEmpty)
{
    SortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());

    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());

    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}

TEST(SortedTableTest, Consist)
{
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
}

TEST(SortedTableTest, Size)
{
    SortedTableOnVec<int, std::string> table;
    EXPECT_EQ(table.size(), 0);

    table.insert(1, "one");
    EXPECT_EQ(table.size(), 1);

    table.insert(2, "two");
    EXPECT_EQ(table.size(), 2);

    table.erase(1);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest, Print)
{
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    std::stringstream ss;
    table.print(ss);
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Key: 1, Value: one") != std::string::npos);
    EXPECT_TRUE(output.find("Key: 2, Value: two") != std::string::npos);
}

TEST(SortedTableTest, BinarySearchEfficiency)
{
    SortedTableOnVec<int, std::string> table;

    // Вставляем много элементов
    for (int i = 0; i < 1000; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }

    // Проверяем быстрый поиск
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(table.consist(i));
    }

    // Проверяем граничные случаи
    EXPECT_TRUE(table.consist(0));
    EXPECT_TRUE(table.consist(999));
    EXPECT_FALSE(table.consist(-1));
    EXPECT_FALSE(table.consist(1000));
}

TEST(SortedTableTest, StringKeys)
{
    SortedTableOnVec<std::string, int> table;

    table.insert("banana", 3);
    table.insert("apple", 5);
    table.insert("cherry", 2);

    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table.find("apple"), 5);
    EXPECT_EQ(table.find("banana"), 3);
    EXPECT_EQ(table.find("cherry"), 2);
}

TEST(SortedTableTest, ComplexOperations)
{
    SortedTableOnVec<int, std::string> table;

    // Вставка в разном порядке
    std::vector<int> keys = { 5, 2, 8, 1, 9, 3, 7, 4, 6, 0 };
    for (int key : keys) {
        table.insert(key, "val_" + std::to_string(key));
    }
    EXPECT_EQ(table.size(), 10);

    // Проверка всех ключей
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), "val_" + std::to_string(i));
    }

    // Обновление
    table.insert(5, "UPDATED_5");
    EXPECT_EQ(table.find(5), "UPDATED_5");
    EXPECT_EQ(table.size(), 10);

    // Удаление нечетных
    for (int i = 1; i < 10; i += 2) {
        table.erase(i);
    }
    EXPECT_EQ(table.size(), 5);

    // Проверка оставшихся
    for (int i = 0; i < 10; i += 2) {
        EXPECT_TRUE(table.consist(i));
    }
    for (int i = 1; i < 10; i += 2) {
        EXPECT_FALSE(table.consist(i));
    }
}

TEST(SortedTableTest, DuplicateKeys)
{
    SortedTableOnVec<int, std::string> table;

    table.insert(1, "first");
    table.insert(1, "second");  // Должно обновить
    table.insert(1, "third");   // Должно обновить

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "third");
}