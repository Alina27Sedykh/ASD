#include <gtest/gtest.h>
#include "../lib_stack/stack.h"


TEST(Stak_Constructors, CapacityConstructor)
{
    Stak<int> stack(5);
    ASSERT_TRUE(stack.is_empty());
    ASSERT_FALSE(stack.is_full());
}

TEST(Stak_Constructors, CopyConstructor) 
{
    Stak<int> stack1(3);
    stack1.push(1);
    stack1.push(2);

    Stak<int> stack2(stack1);
    ASSERT_EQ(stack1.top(), stack2.top());
    stack1.pop();
    ASSERT_EQ(2, stack2.top()); // stack2 не должен измениться после pop в stack1
}

// Тесты для push
TEST(Stak_Push, NormalPush)
{
    Stak<int> stack(2);
    stack.push(10);
    ASSERT_EQ(10, stack.top());
    ASSERT_FALSE(stack.is_empty());
    ASSERT_FALSE(stack.is_full());

    stack.push(20);
    ASSERT_EQ(20, stack.top());
    ASSERT_TRUE(stack.is_full());
}

TEST(Stak_Push, PushException)
{
    Stak<int> stack(1);
    stack.push(10);
    EXPECT_THROW(stack.push(20), std::invalid_argument);
}

// Тесты для pop
TEST(Stak_Pop, NormalPop)
{
    Stak<int> stack(2);
    stack.push(10);
    stack.push(20);

    stack.pop();
    ASSERT_EQ(10, stack.top());
    ASSERT_FALSE(stack.is_empty());

    stack.pop();
    ASSERT_TRUE(stack.is_empty());
}

TEST(Stak_Pop, PopException)
{
    Stak<int> stack(1);
    EXPECT_THROW(stack.pop(), std::invalid_argument);
}

// Тесты для top
TEST(Stak_Top, NormalTop)
{
    Stak<int> stack(2);
    stack.push(42);
    ASSERT_EQ(42, stack.top());

    stack.push(100);
    ASSERT_EQ(100, stack.top());
}

TEST(Stak_Top, TopException)
{
    Stak<int> stack(1);
    EXPECT_THROW(stack.top(), std::invalid_argument);
}

// Тесты для is_empty
TEST(Stak_IsEmpty, WhenEmpty) 
{
    Stak<int> stack(3);
    ASSERT_TRUE(stack.is_empty());
}

TEST(Stak_IsEmpty, WhenNotEmpty)
{
    Stak<int> stack(3);
    stack.push(1);
    ASSERT_FALSE(stack.is_empty());
}

// Тесты для is_full
TEST(Stak_IsFull, WhenFull)
{
    Stak<int> stack(1);
    stack.push(10);
    ASSERT_TRUE(stack.is_full());
}

TEST(Stak_IsFull, WhenNotFull)
{
    Stak<int> stack(2);
    stack.push(10);
    ASSERT_FALSE(stack.is_full());
}

// Тесты для clear
TEST(Stak_Clear, FromNotEmpty) 
{
    Stak<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.clear();
    ASSERT_TRUE(stack.is_empty());
    ASSERT_FALSE(stack.is_full());
}

TEST(Stak_Clear, FromEmpty) 
{
    Stak<int> stack(3);
    stack.clear();
    ASSERT_TRUE(stack.is_empty());
    ASSERT_FALSE(stack.is_full());
}

// Тест на последовательность операций
TEST(Stak_Integration, ComplexOperations)
{
    Stak<int> stack(3);

    // Push три элемента
    stack.push(1);
    stack.push(2);
    stack.push(3);

    ASSERT_TRUE(stack.is_full());
    ASSERT_EQ(3, stack.top());

    // Pop один элемент
    stack.pop();
    ASSERT_EQ(2, stack.top());
    ASSERT_FALSE(stack.is_full());

    // Push еще один
    stack.push(4);
    ASSERT_EQ(4, stack.top());

    // Clear и проверка
    stack.clear();
    ASSERT_TRUE(stack.is_empty());

    // Push после clear
    stack.push(5);
    ASSERT_EQ(5, stack.top());
}
