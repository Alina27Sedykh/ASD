#include <gtest/gtest.h>
#include "../lib_Tree/Tree.h"
#include "../lib_UnSortedOnTree/UnSortedOnTree.h"

TEST(TreeTest, CreateEmptyTree)
{
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(TreeTest, InsertOneElement)
{
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.find(5), "five");
}

TEST(TreeTest, InsertMultipleElements)
{
    Tree<int, std::string> tree;
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

TEST(TreeTest, InsertDuplicateKeyUpdatesValue)
{
    Tree<int, int> tree;
    tree.insert(10, 100);
    EXPECT_EQ(tree.find(10), 100);

    tree.insert(10, 200);
    EXPECT_EQ(tree.find(10), 200);
    EXPECT_EQ(tree.size(), 1);
}

TEST(TreeTest, ContainsExistingKey)
{
    Tree<int, int> tree;
    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);

    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(3));
}

TEST(TreeTest, ContainsNonExistingKey)
{
    Tree<int, int> tree;
    tree.insert(1, 10);
    tree.insert(2, 20);

    EXPECT_FALSE(tree.contains(3));
    EXPECT_FALSE(tree.contains(0));
}

TEST(TreeTest, FindExistingKey)
{
    Tree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");

    EXPECT_EQ(tree.find(1), "one");
    EXPECT_EQ(tree.find(2), "two");
}

TEST(TreeTest, FindNonExistingKeyThrowsException)
{
    Tree<int, int> tree;
    tree.insert(1, 10);

    EXPECT_THROW(tree.find(2), std::logic_error);
}

TEST(TreeTest, FindInEmptyTreeThrowsException)
{
    Tree<int, int> tree;
    EXPECT_THROW(tree.find(1), std::logic_error);
}

TEST(TreeTest, EraseLeafNode)
{
    Tree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);

    EXPECT_TRUE(tree.contains(7));
    tree.erase(7);
    EXPECT_FALSE(tree.contains(7));
    EXPECT_EQ(tree.size(), 2);
}

TEST(TreeTest, EraseNodeWithOneChild)
{
    Tree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(6, 6);

    EXPECT_TRUE(tree.contains(7));
    tree.erase(7);
    EXPECT_FALSE(tree.contains(7));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_EQ(tree.size(), 3);
}

TEST(TreeTest, EraseNodeWithTwoChildren)
{
    Tree<int, int> tree;
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
}

TEST(TreeTest, EraseRootOnly)
{
    Tree<int, int> tree;
    tree.insert(42, 4242);

    EXPECT_FALSE(tree.is_empty());
    tree.erase(42);
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(TreeTest, EraseNonExistingKeyThrowsException)
{
    Tree<int, int> tree;
    tree.insert(1, 10);

    EXPECT_THROW(tree.erase(2), std::logic_error);
}

TEST(TreeTest, EraseFromEmptyTreeThrowsException)
{
    Tree<int, int> tree;
    EXPECT_THROW(tree.erase(1), std::logic_error);
}

TEST(TreeTest, GetElementsFromEmptyTree)
{
    Tree<int, int> tree;
    auto elements = tree.get_elements();
    EXPECT_TRUE(elements.empty());
}

TEST(TreeTest, GetElementsFromNonEmptyTree)
{
    Tree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);

    auto elements = tree.get_elements();
    EXPECT_EQ(elements.size(), 3);
}

TEST(TreeTest, ComplexScenario)
{
    Tree<int, std::string> tree;

    // Вставка
    for (int i = 1; i <= 10; i++)
    {
        tree.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_EQ(tree.size(), 10);

    // Проверка contains
    for (int i = 1; i <= 10; i++)
    {
        EXPECT_TRUE(tree.contains(i));
    }

    // Удаление
    tree.erase(5);
    tree.erase(7);
    tree.erase(9);

    EXPECT_EQ(tree.size(), 7);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_FALSE(tree.contains(7));
    EXPECT_FALSE(tree.contains(9));

    // Проверка оставшихся
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(4));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_TRUE(tree.contains(8));
    EXPECT_TRUE(tree.contains(10));
}

//
TEST(UnorderedTableTest, CreateEmptyTable)
{
    UnorderedTable<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(UnorderedTableTest, InsertOneElement)
{
    UnorderedTable<int, std::string> table;
    table.insert(5, "five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(5), "five");
}

TEST(UnorderedTableTest, InsertMultipleElements)
{
    UnorderedTable<int, std::string> table;
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

TEST(UnorderedTableTest, InsertDuplicateKeyUpdatesValue)
{
    UnorderedTable<int, int> table;
    table.insert(10, 100);
    EXPECT_EQ(table.find(10), 100);

    table.insert(10, 200);
    EXPECT_EQ(table.find(10), 200);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnorderedTableTest, ConsistExistingKey)
{
    UnorderedTable<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
}

TEST(UnorderedTableTest, ConsistNonExistingKey)
{
    UnorderedTable<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    EXPECT_FALSE(table.consist(3));
    EXPECT_FALSE(table.consist(0));
}

TEST(UnorderedTableTest, FindExistingKey)
{
    UnorderedTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
}

TEST(UnorderedTableTest, FindNonExistingKeyThrowsException)
{
    UnorderedTable<int, int> table;
    table.insert(1, 10);

    EXPECT_THROW(table.find(2), std::logic_error);
}

TEST(UnorderedTableTest, FindInEmptyTableThrowsException)
{
    UnorderedTable<int, int> table;
    EXPECT_THROW(table.find(1), std::logic_error);
}

TEST(UnorderedTableTest, EraseLeafNode)
{
    UnorderedTable<int, int> table;
    table.insert(5, 5);
    table.insert(3, 3);
    table.insert(7, 7);

    EXPECT_TRUE(table.consist(7));
    table.erase(7);
    EXPECT_FALSE(table.consist(7));
    EXPECT_EQ(table.size(), 2);
}

TEST(UnorderedTableTest, EraseNodeWithChildren)
{
    UnorderedTable<int, int> table;
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

TEST(UnorderedTableTest, EraseRootOnly)
{
    UnorderedTable<int, int> table;
    table.insert(42, 4242);

    EXPECT_FALSE(table.is_empty());
    table.erase(42);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(UnorderedTableTest, EraseNonExistingKeyThrowsException)
{
    UnorderedTable<int, int> table;
    table.insert(1, 10);

    EXPECT_THROW(table.erase(2), std::logic_error);
}

TEST(UnorderedTableTest, EraseFromEmptyTableThrowsException)
{
    UnorderedTable<int, int> table;
    EXPECT_THROW(table.erase(1), std::logic_error);
}

TEST(UnorderedTableTest, SizeAfterOperations)
{
    UnorderedTable<int, int> table;
    EXPECT_EQ(table.size(), 0);

    table.insert(1, 10);
    EXPECT_EQ(table.size(), 1);

    table.insert(2, 20);
    table.insert(3, 30);
    EXPECT_EQ(table.size(), 3);

    table.erase(2);
    EXPECT_EQ(table.size(), 2);

    table.erase(1);
    table.erase(3);
    EXPECT_EQ(table.size(), 0);
}

TEST(UnorderedTableTest, IsEmpty)
{
    UnorderedTable<int, int> table;
    EXPECT_TRUE(table.is_empty());

    table.insert(1, 10);
    EXPECT_FALSE(table.is_empty());

    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}

TEST(UnorderedTableTest, PrintEmptyTable)
{
    UnorderedTable<int, int> table;
    std::ostringstream oss;
    table.print(oss);
    EXPECT_EQ(oss.str(), "empty");
}

TEST(UnorderedTableTest, PrintNonEmptyTable)
{
    UnorderedTable<int, int> table;
    table.insert(5, 5);
    table.insert(3, 3);
    table.insert(7, 7);

    std::ostringstream oss;
    table.print(oss);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_TRUE(oss.str().find("Tree(size=3)") != std::string::npos);
}

TEST(UnorderedTableTest, ComplexScenario)
{
    UnorderedTable<int, std::string> table;

    // Вставка
    for (int i = 1; i <= 10; i++)
    {
        table.insert(i, "value_" + std::to_string(i));
    }
    EXPECT_EQ(table.size(), 10);

    // Проверка consist
    for (int i = 1; i <= 10; i++)
    {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), "value_" + std::to_string(i));
    }

    // Удаление
    table.erase(5);
    table.erase(7);
    table.erase(9);

    EXPECT_EQ(table.size(), 7);
    EXPECT_FALSE(table.consist(5));
    EXPECT_FALSE(table.consist(7));
    EXPECT_FALSE(table.consist(9));

    // Проверка оставшихся
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(4));
    EXPECT_TRUE(table.consist(6));
    EXPECT_TRUE(table.consist(8));
    EXPECT_TRUE(table.consist(10));
}

TEST(UnorderedTableTest, MixedOperations)
{
    UnorderedTable<int, int> table;

    table.insert(10, 100);
    table.insert(20, 200);
    table.insert(30, 300);
    EXPECT_EQ(table.size(), 3);

    table.insert(20, 250);
    EXPECT_EQ(table.find(20), 250);
    EXPECT_EQ(table.size(), 3);

    table.erase(10);
    EXPECT_FALSE(table.consist(10));
    EXPECT_EQ(table.size(), 2);

    table.insert(40, 400);
    EXPECT_TRUE(table.consist(40));
    EXPECT_EQ(table.size(), 3);

    EXPECT_EQ(table.find(20), 250);
    EXPECT_EQ(table.find(30), 300);
    EXPECT_EQ(table.find(40), 400);
}

TEST(UnorderedTableTest, LargeNumberOfElements)
{
    UnorderedTable<int, int> table;
    const int num_elements = 100;

    for (int i = 0; i < num_elements; i++)
    {
        table.insert(i, i * 2);
    }
    EXPECT_EQ(table.size(), num_elements);

    for (int i = 0; i < num_elements; i++)
    {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), i * 2);
    }

    for (int i = 0; i < num_elements; i += 2)
    {
        table.erase(i);
    }
    EXPECT_EQ(table.size(), num_elements / 2);

    for (int i = 0; i < num_elements; i += 2)
    {
        EXPECT_FALSE(table.consist(i));
    }

    for (int i = 1; i < num_elements; i += 2)
    {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), i * 2);
    }
}