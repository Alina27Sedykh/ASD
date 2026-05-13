#include <gtest/gtest.h>
#include "../lib_RBTree/RBTree.h"
#include "../lib_OrderedTableRB/OrderedTableRB.h"

TEST(RBTreeTest, CreateEmptyTree)
{
    RBTree<int, std::string> tree;
    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
}

TEST(RBTreeTest, InsertOneElement)
{
    RBTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_EQ(tree.size(), 1);
    EXPECT_TRUE(tree.contains(5));
    EXPECT_EQ(tree.find(5), "five");
}

TEST(RBTreeTest, InsertMultipleElements)
{
    RBTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(15));
}

TEST(RBTreeTest, UpdateExistingKey)
{
    RBTree<int, std::string> tree;
    tree.insert(10, "ten");
    EXPECT_EQ(tree.find(10), "ten");

    tree.insert(10, "TEN");
    EXPECT_EQ(tree.find(10), "TEN");
    EXPECT_EQ(tree.size(), 1);
}

TEST(RBTreeTest, InorderTraversal)
{
    RBTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    auto result = tree.inorder();
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0].first, 3);
    EXPECT_EQ(result[1].first, 5);
    EXPECT_EQ(result[2].first, 7);
    EXPECT_EQ(result[3].first, 10);
    EXPECT_EQ(result[4].first, 15);
}
TEST(OrderedTableRBTest, CreateEmptyTable)
{
    OrderedTable<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(OrderedTableRBTest, InsertOneElement)
{
    OrderedTable<int, std::string> table;
    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.consist(5));
    EXPECT_EQ(table.find(5), "five");
}

TEST(OrderedTableRBTest, UpdateExistingKey)
{
    OrderedTable<int, std::string> table;
    table.insert(10, "ten");
    EXPECT_EQ(table.find(10), "ten");

    table.insert(10, "TEN");
    EXPECT_EQ(table.find(10), "TEN");
    EXPECT_EQ(table.size(), 1);
}

TEST(OrderedTableRBTest, ToVectorReturnsSortedElements)
{
    OrderedTable<int, std::string> table;
    table.insert(10, "ten");
    table.insert(5, "five");
    table.insert(15, "fifteen");
    table.insert(3, "three");
    table.insert(7, "seven");

    auto result = table.toVector();
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0].first, 3);
    EXPECT_EQ(result[1].first, 5);
    EXPECT_EQ(result[2].first, 7);
    EXPECT_EQ(result[3].first, 10);
    EXPECT_EQ(result[4].first, 15);
}

TEST(OrderedTableRBTest, StringKeys)
{
    OrderedTable<std::string, int> table;

    table.insert("apple", 5);
    table.insert("banana", 3);
    table.insert("cherry", 7);

    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(table.find("apple"), 5);
    EXPECT_EQ(table.find("banana"), 3);
    EXPECT_EQ(table.find("cherry"), 7);

    auto result = table.toVector();
    EXPECT_EQ(result[0].first, "apple");
    EXPECT_EQ(result[1].first, "banana");
    EXPECT_EQ(result[2].first, "cherry");
}