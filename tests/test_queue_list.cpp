#include <gtest/gtest.h>
#include "../lib_queue_list/queue_list.h"


TEST(MyQueueTest, EmptyQueue)
{
    MyQueue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(MyQueueTest, PushAndFront)
{
    MyQueue<int> queue;
    queue.push(10);
    queue.push(20);

    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.size(), 2);
}

TEST(MyQueueTest, PushAndBack)
{
    MyQueue<int> queue;
    queue.push(10);
    queue.push(20);

    EXPECT_EQ(queue.back(), 20);
    EXPECT_EQ(queue.size(), 2);
}

TEST(MyQueueTest, Pop)
{
    MyQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.size(), 2);
}

TEST(MyQueueTest, FIFO_Order)
{
    MyQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.front(), 1);
    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(MyQueueTest, ClearQueue)
{
    MyQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.size(), 3);
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(MyQueueTest, PopEmptyQueue)
{
    MyQueue<int> queue;
    EXPECT_THROW(queue.pop(), std::runtime_error);
}

TEST(MyQueueTest, FrontEmptyQueue)
{
    MyQueue<int> queue;
    EXPECT_THROW(queue.front(), std::runtime_error);
}

TEST(MyQueueTest, BackEmptyQueue)
{
    MyQueue<int> queue;
    EXPECT_THROW(queue.back(), std::runtime_error);
}

TEST(MyQueueTest, CopyConstructor)
{
    MyQueue<int> queue1;
    queue1.push(10);
    queue1.push(20);

    MyQueue<int> queue2(queue1);
    EXPECT_EQ(queue2.front(), 10);
    EXPECT_EQ(queue2.back(), 20);
    EXPECT_EQ(queue2.size(), 2);
}

TEST(MyQueueTest, AssignmentOperator)
{
    MyQueue<int> queue1;
    queue1.push(100);
    queue1.push(200);

    MyQueue<int> queue2;
    queue2 = queue1;

    EXPECT_EQ(queue2.front(), 100);
    EXPECT_EQ(queue2.back(), 200);
    EXPECT_EQ(queue2.size(), 2);
}

TEST(MyQueueTest, Swap)
{
    MyQueue<int> queue1;
    queue1.push(1);
    queue1.push(2);

    MyQueue<int> queue2;
    queue2.push(10);
    queue2.push(20);
    queue2.push(30);

    queue1.swap(queue2);

    EXPECT_EQ(queue1.size(), 3);
    EXPECT_EQ(queue1.front(), 10);
    EXPECT_EQ(queue1.back(), 30);

    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.front(), 1);
    EXPECT_EQ(queue2.back(), 2);
}

TEST(MyQueueTest, MultiplePushPop)
{
    MyQueue<int> queue;

    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), 4);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
}

TEST(MyQueueTest, StringQueue)
{
    MyQueue<std::string> queue;
    queue.push("hello");
    queue.push("world");

    EXPECT_EQ(queue.front(), "hello");
    EXPECT_EQ(queue.back(), "world");
    queue.pop();
    EXPECT_EQ(queue.front(), "world");
}

TEST(MyQueueTest, ModifyFront)
{
    MyQueue<int> queue;
    queue.push(5);
    queue.push(10);

    queue.front() = 15;
    EXPECT_EQ(queue.front(), 15);

    queue.pop();
    EXPECT_EQ(queue.front(), 10);
}

TEST(MyQueueTest, ModifyBack)
{
    MyQueue<int> queue;
    queue.push(5);
    queue.push(10);

    queue.back() = 25;
    EXPECT_EQ(queue.back(), 25);

    queue.push(30);
    EXPECT_EQ(queue.back(), 30);
}