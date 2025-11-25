#include <gtest/gtest.h>
#include "../lib_stack_list/stack_list.h"



TEST(MyStackTest, EmptyStack)
{
    MyStack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(MyStackTest, PushAndTop)
{
    MyStack<int> stack;
    stack.push(10);
    stack.push(20);

    EXPECT_EQ(stack.top(), 20);
    EXPECT_EQ(stack.size(), 2);
}

TEST(MyStackTest, Pop)
{
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    EXPECT_EQ(stack.size(), 2);
}

TEST(MyStackTest, LIFO_Order)
{
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.top(), 3);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(MyStackTest, ClearStack)
{
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.size(), 3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(MyStackTest, PopEmptyStack)
{
    MyStack<int> stack;
    EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST(MyStackTest, TopEmptyStack)
{
    MyStack<int> stack;
    EXPECT_THROW(stack.top(), std::runtime_error);
}

TEST(MyStackTest, CopyConstructor)
{
    MyStack<int> stack1;
    stack1.push(10);
    stack1.push(20);

    MyStack<int> stack2(stack1);
    EXPECT_EQ(stack2.top(), 20);
    EXPECT_EQ(stack2.size(), 2);
}

TEST(MyStackTest, AssignmentOperator)
{
    MyStack<int> stack1;
    stack1.push(100);
    stack1.push(200);

    MyStack<int> stack2;
    stack2 = stack1;

    EXPECT_EQ(stack2.top(), 200);
    EXPECT_EQ(stack2.size(), 2);
}

TEST(MyStackTest, Swap)
{
    MyStack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    MyStack<int> stack2;
    stack2.push(10);
    stack2.push(20);
    stack2.push(30);

    stack1.swap(stack2);

    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack1.top(), 30);

    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top(), 2);
}

TEST(MyStackTest, MultiplePushPop)
{
    MyStack<int> stack;

    for (int i = 0; i < 5; ++i) {
        stack.push(i);
    }

    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 4);

    for (int i = 4; i >= 0; --i) {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }

    EXPECT_TRUE(stack.empty());
}

TEST(MyStackTest, StringStack)
{
    MyStack<std::string> stack;
    stack.push("hello");
    stack.push("world");

    EXPECT_EQ(stack.top(), "world");
    stack.pop();
    EXPECT_EQ(stack.top(), "hello");
}

TEST(MyStackTest, ModifyTop)
{
    MyStack<int> stack;
    stack.push(5);
    stack.push(10);

    stack.top() = 15;
    EXPECT_EQ(stack.top(), 15);

    stack.pop();
    EXPECT_EQ(stack.top(), 5);
}