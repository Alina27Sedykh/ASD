#include <gtest/gtest.h>
#include "../lib_BSTree/BSTree.h"
#include "../lib_SortedOnBSTree/SortedOnBSTree.h"

TEST(SortedTableTest, CreateEmptyTable)
{
    SortedTable<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(SortedTableTest, InsertOneElement)
{
    SortedTable<int, std::string> table;
    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(5), "five");
}

TEST(SortedTableTest, InsertMultipleElements)
{
    SortedTable<int, std::string> table;
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

TEST(SortedTableTest, InsertDuplicateKeyUpdatesValue)
{
    SortedTable<int, int> table;
    table.insert(10, 100);
    EXPECT_EQ(table.find(10), 100);

    table.insert(10, 200);
    EXPECT_EQ(table.find(10), 200);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest, PrintSortedOrder)
{
    SortedTable<int, int> table;
    table.insert(5, 5);
    table.insert(3, 3);
    table.insert(7, 7);
    table.insert(1, 1);
    table.insert(4, 4);
    table.insert(6, 6);
    table.insert(8, 8);

    std::ostringstream oss;
    table.print(oss);
    std::string output = oss.str();

    EXPECT_TRUE(output.find("1:1") != std::string::npos);
    EXPECT_TRUE(output.find("3:3") != std::string::npos);
    EXPECT_TRUE(output.find("4:4") != std::string::npos);
    EXPECT_TRUE(output.find("5:5") != std::string::npos);
    EXPECT_TRUE(output.find("6:6") != std::string::npos);
    EXPECT_TRUE(output.find("7:7") != std::string::npos);
    EXPECT_TRUE(output.find("8:8") != std::string::npos);
}

TEST(SortedTableTest, ConsistExistingKey)
{
    SortedTable<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(SortedTableTest, ConsistNonExistingKey)
{
    SortedTable<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    EXPECT_FALSE(table.consist(3));
    EXPECT_FALSE(table.consist(0));
}

TEST(SortedTableTest, EraseLeafNode)
{
    SortedTable<int, int> table;
    table.insert(5, 5);
    table.insert(3, 3);
    table.insert(7, 7);
    table.insert(1, 1);
    table.insert(4, 4);

    EXPECT_TRUE(table.consist(4));
    table.erase(4);
    EXPECT_FALSE(table.consist(4));
    EXPECT_EQ(table.size(), 4);
}

TEST(SortedTableTest, EraseNodeWithTwoChildren)
{
    SortedTable<int, int> table;
    table.insert(5, 5);
    table.insert(3, 3);
    table.insert(7, 7);
    table.insert(1, 1);
    table.insert(4, 4);
    table.insert(6, 6);
    table.insert(8, 8);

    EXPECT_TRUE(table.consist(5));
    table.erase(5);
    EXPECT_FALSE(table.consist(5));
    EXPECT_EQ(table.size(), 6);
}

TEST(SortedTableTest, EraseRootOnly)
{
    SortedTable<int, int> table;
    table.insert(42, 4242);

    EXPECT_FALSE(table.is_empty());
    table.erase(42);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(SortedTableTest, PrintEmptyTable)
{
    SortedTable<int, int> table;
    std::ostringstream oss;
    table.print(oss);
    EXPECT_EQ(oss.str(), "empty");
}

TEST(SortedTableTest, ComplexScenario)
{
    SortedTable<int, std::string> table;

    for (int i = 1; i <= 10; i++)
    {
        table.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_EQ(table.size(), 10);

    for (int i = 1; i <= 10; i++)
    {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), "value_" + std::to_string(i));
    }

    table.erase(5);
    table.erase(7);
    table.erase(9);

    EXPECT_EQ(table.size(), 7);
    EXPECT_FALSE(table.consist(5));
    EXPECT_FALSE(table.consist(7));
    EXPECT_FALSE(table.consist(9));
}


TEST(BSTreeTest, CreateEmptyTree)
{
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.to_string(), "empty");
    EXPECT_EQ(tree.to_string(true), "empty");
}

TEST(BSTreeTest, InsertOneElement)
{
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, InsertMultipleElements)
{
    BSTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(4, "four");

    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.find(5), "five");
    EXPECT_EQ(tree.find(3), "three");
    EXPECT_EQ(tree.find(7), "seven");
    EXPECT_EQ(tree.find(1), "one");
    EXPECT_EQ(tree.find(4), "four");
}

TEST(BSTreeTest, InsertDuplicateKeyUpdatesValue)
{
    BSTree<int, int> tree;
    tree.insert(10, 100);
    EXPECT_EQ(tree.find(10), 100);

    tree.insert(10, 200);
    EXPECT_EQ(tree.find(10), 200);
    EXPECT_EQ(tree.size(), 1);
}

TEST(BSTreeTest, InsertNegativeKeys)
{
    BSTree<int, int> tree;
    tree.insert(-5, -5);
    tree.insert(-10, -10);
    tree.insert(-3, -3);

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.contains(-5));
    EXPECT_TRUE(tree.contains(-10));
    EXPECT_TRUE(tree.contains(-3));
}

TEST(BSTreeTest, ContainsExistingKey)
{
    BSTree<int, int> tree;
    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);

    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(3));
}

TEST(BSTreeTest, ContainsNonExistingKey)
{
    BSTree<int, int> tree;
    tree.insert(1, 10);
    tree.insert(2, 20);

    EXPECT_FALSE(tree.contains(3));
    EXPECT_FALSE(tree.contains(0));
    EXPECT_FALSE(tree.contains(100));
}

TEST(BSTreeTest, FindExistingKey)
{
    BSTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");

    EXPECT_EQ(tree.find(1), "one");
    EXPECT_EQ(tree.find(2), "two");
    EXPECT_EQ(tree.find(3), "three");
}

TEST(BSTreeTest, FindNonExistingKeyThrowsException)
{
    BSTree<int, int> tree;
    tree.insert(1, 10);
    tree.insert(2, 20);

    EXPECT_THROW(tree.find(3), std::logic_error);
    EXPECT_THROW(tree.find(0), std::logic_error);
}

TEST(BSTreeTest, FindInEmptyTreeThrowsException)
{
    BSTree<int, int> tree;
    EXPECT_THROW(tree.find(1), std::logic_error);
}

TEST(BSTreeTest, EraseLeafNode)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    EXPECT_TRUE(tree.contains(4));
    tree.erase(4);
    EXPECT_FALSE(tree.contains(4));
    EXPECT_EQ(tree.size(), 4);
    EXPECT_EQ(tree.to_string(true), "1:1 3:3 5:5 7:7");
}

TEST(BSTreeTest, EraseNodeWithOnlyLeftChild)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(0, 0);

    EXPECT_TRUE(tree.contains(1));
    tree.erase(1);
    EXPECT_FALSE(tree.contains(1));
    EXPECT_EQ(tree.size(), 4);
    EXPECT_TRUE(tree.contains(0));
}

TEST(BSTreeTest, EraseNodeWithOnlyRightChild)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(4, 4);
    tree.insert(6, 6);

    EXPECT_TRUE(tree.contains(3));
    tree.erase(3);
    EXPECT_FALSE(tree.contains(3));
    EXPECT_EQ(tree.size(), 4);
    EXPECT_TRUE(tree.contains(4));
}

TEST(BSTreeTest, EraseNodeWithTwoChildren)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);
    tree.insert(6, 6);
    tree.insert(8, 8);

    EXPECT_TRUE(tree.contains(5));
    tree.erase(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_EQ(tree.size(), 6);
    // Максимальный элемент в левом поддереве (4) должен встать на место 5
    EXPECT_TRUE(tree.contains(4));
    EXPECT_EQ(tree.to_string(true), "1:1 3:3 4:4 6:6 7:7 8:8");
}

TEST(BSTreeTest, EraseRootWithOneChild)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(4, 4);

    EXPECT_TRUE(tree.contains(5));
    tree.erase(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_EQ(tree.size(), 2);
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(4));
}

TEST(BSTreeTest, EraseRootOnly)
{
    BSTree<int, int> tree;
    tree.insert(42, 4242);

    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(tree.size(), 1);
    tree.erase(42);
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.to_string(), "empty");
}

TEST(BSTreeTest, EraseNonExistingKeyThrowsException)
{
    BSTree<int, int> tree;
    tree.insert(1, 10);
    tree.insert(2, 20);

    EXPECT_THROW(tree.erase(3), std::logic_error);
    EXPECT_THROW(tree.erase(0), std::logic_error);
}

TEST(BSTreeTest, EraseFromEmptyTreeThrowsException)
{
    BSTree<int, int> tree;
    EXPECT_THROW(tree.erase(1), std::logic_error);
}

TEST(BSTreeTest, EraseAllElementsSequentially)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);
    tree.insert(6, 6);
    tree.insert(8, 8);

    tree.erase(1);
    tree.erase(3);
    tree.erase(4);
    tree.erase(5);
    tree.erase(6);
    tree.erase(7);
    tree.erase(8);

    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(BSTreeTest, EraseAndInsertAgain)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);

    tree.erase(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_EQ(tree.size(), 2);

    tree.insert(5, 55);
    EXPECT_TRUE(tree.contains(5));
    EXPECT_EQ(tree.find(5), 55);
    EXPECT_EQ(tree.size(), 3);
}


TEST(BSTreeTest, ToStringUnsorted)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    std::string result = tree.to_string(false);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.find("(5:5)") != std::string::npos);
}

TEST(BSTreeTest, ToStringSorted)
{
    BSTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);
    tree.insert(6, 6);
    tree.insert(8, 8);

    std::string sorted = tree.to_string(true);
    EXPECT_EQ(sorted, "1:1 3:3 4:4 5:5 6:6 7:7 8:8");
}

TEST(BSTreeTest, ToStringSortedWithNegativeKeys)
{
    BSTree<int, int> tree;
    tree.insert(-5, -5);
    tree.insert(-10, -10);
    tree.insert(0, 0);
    tree.insert(5, 5);
    tree.insert(3, 3);

    std::string sorted = tree.to_string(true);
    EXPECT_EQ(sorted, "-10:-10 -5:-5 0:0 3:3 5:5");
}

