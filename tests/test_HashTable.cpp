#include <gtest/gtest.h>
#include "../lib_HashTable/HashTable.h"
#include "../lib_HashTableDoubleHashing/HashTableDoubleHashing.h"

TEST(HashTableChainingTest, CreateEmpty)
{
    HashTableChaining<int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(HashTableChainingTest, InsertAndFind)
{
    HashTableChaining<int> table;
    table.insert("apple", 10);
    table.insert("banana", 20);
    table.insert("cherry", 30);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("apple"));
    EXPECT_TRUE(table.consist("banana"));
    EXPECT_TRUE(table.consist("cherry"));
    EXPECT_FALSE(table.consist("grape"));

    EXPECT_EQ(table.find("apple"), 10);
    EXPECT_EQ(table.find("banana"), 20);
    EXPECT_EQ(table.find("cherry"), 30);
}

TEST(HashTableChainingTest, FindThrowsWhenNotFound)
{
    HashTableChaining<int> table;
    table.insert("key", 100);

    EXPECT_THROW(table.find("wrong"), std::out_of_range);
}

TEST(HashTableChainingTest, Erase)
{
    HashTableChaining<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    table.erase("two");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("two"));
    EXPECT_TRUE(table.consist("one"));
    EXPECT_TRUE(table.consist("three"));

    table.erase("one");
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.consist("one"));

    table.erase("three");
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableChainingTest, EraseThrowsWhenNotFound)
{
    HashTableChaining<int> table;
    table.insert("key", 1);

    EXPECT_THROW(table.erase("wrong"), std::out_of_range);
}

TEST(HashTableChainingTest, InsertDuplicateDoesNothing)
{
    HashTableChaining<int> table;
    table.insert("key", 100);
    table.insert("key", 200);

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find("key"), 100);
}

TEST(HashTableChainingTest, PrintDoesNotCrash)
{
    HashTableChaining<int> table;
    table.insert("a", 1);
    table.insert("b", 2);

    std::ostringstream oss;
    EXPECT_NO_THROW(table.print(oss));
    EXPECT_FALSE(oss.str().empty());
}

TEST(HashTableChainingTest, LargeData)
{
    HashTableChaining<int> table;

    for (int i = 0; i < 1000; ++i) {
        table.insert("key_" + std::to_string(i), i);
    }

    EXPECT_EQ(table.size(), 1000);

    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(table.consist("key_" + std::to_string(i)));
        EXPECT_EQ(table.find("key_" + std::to_string(i)), i);
    }
}


TEST(HashTableDoubleHashingTest, CreateEmpty)
{
    HashTableDoubleHashing<int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(HashTableDoubleHashingTest, InsertAndFind)
{
    HashTableDoubleHashing<int> table;
    table.insert("apple", 10);
    table.insert("banana", 20);
    table.insert("cherry", 30);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("apple"));
    EXPECT_TRUE(table.consist("banana"));
    EXPECT_TRUE(table.consist("cherry"));
    EXPECT_FALSE(table.consist("grape"));

    EXPECT_EQ(table.find("apple"), 10);
    EXPECT_EQ(table.find("banana"), 20);
    EXPECT_EQ(table.find("cherry"), 30);
}

TEST(HashTableDoubleHashingTest, FindThrowsWhenNotFound)
{
    HashTableDoubleHashing<int> table;
    table.insert("key", 100);

    EXPECT_THROW(table.find("wrong"), std::out_of_range);
}

TEST(HashTableDoubleHashingTest, Erase)
{
    HashTableDoubleHashing<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    table.erase("two");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("two"));
    EXPECT_TRUE(table.consist("one"));
    EXPECT_TRUE(table.consist("three"));

    table.erase("one");
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.consist("one"));

    table.erase("three");
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableDoubleHashingTest, EraseThrowsWhenNotFound)
{
    HashTableDoubleHashing<int> table;
    table.insert("key", 1);

    EXPECT_THROW(table.erase("wrong"), std::out_of_range);
}

TEST(HashTableDoubleHashingTest, InsertDuplicateDoesNothing)
{
    HashTableDoubleHashing<int> table;
    table.insert("key", 100);
    table.insert("key", 200);

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find("key"), 100);
}

TEST(HashTableDoubleHashingTest, PrintDoesNotCrash)
{
    HashTableDoubleHashing<int> table;
    table.insert("a", 1);
    table.insert("b", 2);

    std::ostringstream oss;
    EXPECT_NO_THROW(table.print(oss));
    EXPECT_FALSE(oss.str().empty());
}

TEST(HashTableDoubleHashingTest, ResizeWorks)
{
    HashTableDoubleHashing<int> table(5); 

    for (int i = 0; i < 20; ++i) {
        table.insert("key_" + std::to_string(i), i);
    }

    EXPECT_EQ(table.size(), 20);

    for (int i = 0; i < 20; ++i) {
        EXPECT_TRUE(table.consist("key_" + std::to_string(i)));
        EXPECT_EQ(table.find("key_" + std::to_string(i)), i);
    }
}