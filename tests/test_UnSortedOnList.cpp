#include <gtest/gtest.h>
#include <sstream>
#include "UnsortedTableOnList.h"
TEST(UnsortedTableOnListTest, CreateEmptyTable)
{
    UnsortedTableOnList<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(UnsortedTableOnListTest, InsertOneElement)
{
    UnsortedTableOnList<int, std::string> table;
    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(5), "five");
}

TEST(UnsortedTableOnListTest, InsertMultipleElements)
{
    UnsortedTableOnList<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");
    table.insert(1, "one");
    table.insert(4, "four");

    EXPECT_EQ(table.size(), 5);
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.find(7), "seven");
    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(4), "four");
}

TEST(UnsortedTableOnListTest, InsertDuplicateKeyUpdatesValue)
{
    UnsortedTableOnList<int, int> table;
    table.insert(10, 100);
    EXPECT_EQ(table.find(10), 100);

    table.insert(10, 200);
    EXPECT_EQ(table.find(10), 200);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnsortedTableOnListTest, ConsistExistingKey)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(UnsortedTableOnListTest, ConsistNonExistingKey)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    EXPECT_FALSE(table.consist(3));
    EXPECT_FALSE(table.consist(0));
}

TEST(UnsortedTableOnListTest, FindExistingKey)
{
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST(UnsortedTableOnListTest, FindNonExistingKeyThrowsException)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    EXPECT_THROW(table.find(3), std::logic_error);
    EXPECT_THROW(table.find(0), std::logic_error);
}

TEST(UnsortedTableOnListTest, FindInEmptyTableThrowsException)
{
    UnsortedTableOnList<int, int> table;
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST(UnsortedTableOnListTest, EraseExistingKey)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    EXPECT_TRUE(table.consist(2));
    table.erase(2);
    EXPECT_FALSE(table.consist(2));
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table.find(1), 10);
    EXPECT_EQ(table.find(3), 30);
}

TEST(UnsortedTableOnListTest, EraseFirstElement)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    table.erase(1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(UnsortedTableOnListTest, EraseLastElement)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    table.erase(3);
    EXPECT_FALSE(table.consist(3));
    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
}

TEST(UnsortedTableOnListTest, EraseOnlyElement)
{
    UnsortedTableOnList<int, int> table;
    table.insert(42, 4242);

    EXPECT_FALSE(table.is_empty());
    table.erase(42);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(UnsortedTableOnListTest, EraseNonExistingKeyThrowsException)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    EXPECT_THROW(table.erase(3), std::logic_error);
    EXPECT_THROW(table.erase(0), std::logic_error);
}

TEST(UnsortedTableOnListTest, EraseFromEmptyTableThrowsException)
{
    UnsortedTableOnList<int, int> table;
    EXPECT_THROW(table.erase(1), std::logic_error);
}

TEST(UnsortedTableOnListTest, PrintEmptyTable)
{
    UnsortedTableOnList<int, int> table;
    std::ostringstream oss;
    table.print(oss);
    EXPECT_EQ(oss.str(), "empty");
}

TEST(UnsortedTableOnListTest, PrintNonEmptyTable)
{
    UnsortedTableOnList<int, int> table;
    table.insert(5, 5);
    table.insert(3, 3);
    table.insert(7, 7);

    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();

    EXPECT_TRUE(output.find("UnsortedTableOnList(size=3)") != std::string::npos);
    EXPECT_TRUE(output.find("(5:5)") != std::string::npos);
    EXPECT_TRUE(output.find("(3:3)") != std::string::npos);
    EXPECT_TRUE(output.find("(7:7)") != std::string::npos);
}

TEST(UnsortedTableOnListTest, ClearTable)
{
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    EXPECT_EQ(table.size(), 3);
    table.clear();
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}
