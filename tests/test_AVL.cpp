#include <gtest/gtest.h>
#include "../lib_AVLTree/AVLTree.h"
#include "../lib_OrderedTableAVL/OrderedTableAVL.h"

TEST(AVLTreeTest, CreateEmptyTree)
{
    AVLTree<int, std::string> tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, InsertOneElement)
{
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_TRUE(tree.contains(5));
    EXPECT_EQ(tree.find(5), "five");
}

TEST(AVLTreeTest, InsertMultipleElements)
{
    AVLTree<int, std::string> tree;
    tree.insert(3, "three");
    tree.insert(1, "one");
    tree.insert(4, "four");
    tree.insert(2, "two");
    tree.insert(5, "five");

    EXPECT_EQ(tree.size(), 5);
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(4));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(5));
}

TEST(AVLTreeTest, InsertDuplicateKey)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(10, "TEN");

    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.find(10), "ten");
}

TEST(AVLTreeTest, FindExistingKey)
{
    AVLTree<int, std::string> tree;
    tree.insert(42, "answer");
    tree.insert(7, "lucky");
    tree.insert(99, "ninety nine");

    EXPECT_EQ(tree.find(42), "answer");
    EXPECT_EQ(tree.find(7), "lucky");
    EXPECT_EQ(tree.find(99), "ninety nine");
}

TEST(AVLTreeTest, FindNonExistingKey)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_THROW(tree.find(30), std::out_of_range);
    EXPECT_THROW(tree.find(5), std::out_of_range);
}

TEST(AVLTreeTest, ContainsKey)
{
    AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");

    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_FALSE(tree.contains(4));
    EXPECT_FALSE(tree.contains(0));
}

TEST(AVLTreeTest, EraseLeafNode)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");

    tree.erase(5);
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(15));
}

TEST(AVLTreeTest, EraseNodeWithOneChild)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(3, "three");

    tree.erase(5);
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(3));
}

TEST(AVLTreeTest, EraseNodeWithTwoChildren)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree.insert(12, "twelve");
    tree.insert(18, "eighteen");

    tree.erase(15);
    EXPECT_EQ(tree.size(), 4);
    EXPECT_FALSE(tree.contains(15));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(12));
    EXPECT_TRUE(tree.contains(18));
}

TEST(AVLTreeTest, EraseRoot)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");

    tree.erase(10);
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.contains(10));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(15));
}

TEST(AVLTreeTest, EraseNonExistingKey)
{
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    tree.erase(99);
    EXPECT_EQ(tree.size(), 2);
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(20));
}

TEST(AVLTreeTest, EraseAllElements)
{
    AVLTree<int, std::string> tree;

    for (int i = 1; i <= 10; i++) {
        tree.insert(i, "val_" + std::to_string(i));
    }

    EXPECT_EQ(tree.size(), 10);

    for (int i = 1; i <= 10; i++) {
        tree.erase(i);
        EXPECT_EQ(tree.size(), 10 - i);
    }

    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.isEmpty());

    for (int i = 1; i <= 10; i++) {
        EXPECT_FALSE(tree.contains(i));
    }

    // ѕроверка, что можно вставить после удалени€
    tree.insert(100, "hundred");
    EXPECT_EQ(tree.size(), 1);
    EXPECT_TRUE(tree.contains(100));
}

TEST(AVLTreeTest, InorderTraversal)
{
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(9, "nine");
    tree.insert(4, "four");
    tree.insert(6, "six");

    std::vector<std::pair<int, std::string>> result = tree.inorder();

    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result[0].first, 1);
    EXPECT_EQ(result[1].first, 3);
    EXPECT_EQ(result[2].first, 4);
    EXPECT_EQ(result[3].first, 5);
    EXPECT_EQ(result[4].first, 6);
    EXPECT_EQ(result[5].first, 7);
    EXPECT_EQ(result[6].first, 9);
}

TEST(AVLTreeTest, InorderEmptyTree)
{
    AVLTree<int, std::string> tree;
    std::vector<std::pair<int, std::string>> result = tree.inorder();
    EXPECT_TRUE(result.empty());
}

TEST(AVLTreeTest, BalanceAfterAscendingInsert)
{
    AVLTree<int, std::string> tree;

    for (int i = 1; i <= 30; i++) {
        tree.insert(i, std::to_string(i));
    }

    EXPECT_EQ(tree.size(), 30);

    for (int i = 1; i <= 30; i++) {
        EXPECT_TRUE(tree.contains(i));
    }
}

TEST(AVLTreeTest, BalanceAfterDescendingInsert)
{
    AVLTree<int, std::string> tree;

    for (int i = 30; i >= 1; i--) {
        tree.insert(i, std::to_string(i));
    }

    EXPECT_EQ(tree.size(), 30);

    for (int i = 1; i <= 30; i++) {
        EXPECT_TRUE(tree.contains(i));
    }
}

TEST(AVLTreeTest, LargeDataTest)
{
    AVLTree<int, int> tree;
    const int N = 1000;

    for (int i = 0; i < N; i++) {
        tree.insert(i, i * 2);
    }

    EXPECT_EQ(tree.size(), N);

    for (int i = 0; i < N; i++) {
        EXPECT_TRUE(tree.contains(i));
        EXPECT_EQ(tree.find(i), i * 2);
    }

    for (int i = 0; i < N / 2; i++) {
        tree.erase(i);
    }

    EXPECT_EQ(tree.size(), N - N / 2);

    for (int i = 0; i < N / 2; i++) {
        EXPECT_FALSE(tree.contains(i));
    }

    for (int i = N / 2; i < N; i++) {
        EXPECT_TRUE(tree.contains(i));
    }
}

TEST(AVLTreeTest, StringKeys)
{
    AVLTree<std::string, int> tree;
    tree.insert("apple", 10);
    tree.insert("banana", 20);
    tree.insert("cherry", 30);

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.contains("banana"));
    EXPECT_EQ(tree.find("apple"), 10);
    EXPECT_EQ(tree.find("cherry"), 30);

    tree.erase("banana");
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.contains("banana"));
}

TEST(AVLTreeTest, EraseInReverseOrder)
{
    AVLTree<int, std::string> tree;

    for (int i = 1; i <= 20; i++) {
        tree.insert(i, "val_" + std::to_string(i));
    }

    for (int i = 20; i >= 1; i--) {
        tree.erase(i);
        EXPECT_EQ(tree.size(), i - 1);
    }

    EXPECT_TRUE(tree.isEmpty());
}

TEST(AVLTreeTest, InterleavedInsertAndErase)
{
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.erase(10);
    tree.insert(15, "fifteen");
    tree.insert(5, "five");
    tree.erase(20);
    tree.insert(25, "twenty five");

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(25));
    EXPECT_FALSE(tree.contains(10));
    EXPECT_FALSE(tree.contains(20));
}
//
TEST(OrderedTableTest, CreateEmptyTable)
{
    OrderedTableAVL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(OrderedTableTest, InsertAndFind)
{
    OrderedTableAVL<int, std::string> table;

    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");

    EXPECT_EQ(table.size(), 3);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_FALSE(table.consist(10));

    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.find(7), "seven");
}

TEST(OrderedTableTest, FindThrowsWhenKeyNotFound)
{
    OrderedTableAVL<int, std::string> table;
    table.insert(10, "ten");

    EXPECT_THROW(table.find(20), std::out_of_range);
}

TEST(OrderedTableTest, Erase)
{
    OrderedTableAVL<int, std::string> table;
    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    table.erase(20);
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist(20));
    EXPECT_TRUE(table.consist(10));
    EXPECT_TRUE(table.consist(30));

    table.erase(10);
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.consist(10));
    EXPECT_TRUE(table.consist(30));

    table.erase(30);
    EXPECT_EQ(table.size(), 0);
    EXPECT_TRUE(table.is_empty());
}

TEST(OrderedTableTest, InsertDuplicateDoesNotChangeSize)
{
    OrderedTableAVL<int, std::string> table;
    table.insert(42, "answer");
    table.insert(42, "ANSWER");

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(42), "answer");
}

TEST(OrderedTableTest, PrintDoesNotCrash)
{
    OrderedTableAVL<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");

    std::ostringstream oss;
    EXPECT_NO_THROW(table.print(oss));
    EXPECT_FALSE(oss.str().empty());
}

TEST(OrderedTableTest, StringKeys)
{
    OrderedTableAVL<std::string, int> table;
    table.insert("apple", 10);
    table.insert("banana", 20);
    table.insert("cherry", 30);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("banana"));
    EXPECT_EQ(table.find("apple"), 10);
    EXPECT_EQ(table.find("cherry"), 30);

    table.erase("banana");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("banana"));
}