#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(TestQueue, can_create_queue) 
{
	ASSERT_NO_THROW(Queue<int> q(5));
}

TEST(TestQueue, created_queue_is_empty) 
{
	Queue<int> q(5);

	EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, can_push_element)
{

	Queue<int> q(3);
	ASSERT_NO_THROW(q.push(10));
}

TEST(TestQueue, push_changes_empty_status) 
{
	Queue<int> q(3);
	q.push(10);
	EXPECT_FALSE(q.is_empty());
}

TEST(TestQueue, can_pop_element)
{
	Queue<int> q(3);
	q.push(10);
	ASSERT_NO_THROW(q.pop());
}

TEST(TestQueue, can_get_front_element) 
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	ASSERT_NO_THROW(q.front());
}

TEST(TestQueue, front_returns_correct_element)
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);
	int result = q.front();
	int expected = 10;
	EXPECT_EQ(expected, result);
}

TEST(TestQueue, can_get_back_element)
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	ASSERT_NO_THROW(q.back());
}

TEST(TestQueue, back_returns_correct_element)
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	int result = q.back();
	int expected = 20;
	EXPECT_EQ(expected, result);
}

TEST(TestQueue, pop_removes_front_element)
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);
	q.push(30);
	q.pop();

	EXPECT_EQ(20, q.front());
}

TEST(TestQueue, can_detect_full_queue) 
{
	Queue<int> q(2);
	q.push(10);
	q.push(20);

	EXPECT_TRUE(q.is_full());
}

TEST(TestQueue, can_clear_queue) 
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);
	q.clear();

	EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, push_after_clear_works) 
{
	Queue<int> q(3);
	q.push(10);
	q.push(20);
	q.clear();
	q.push(30);

	EXPECT_EQ(30, q.front());
	EXPECT_EQ(30, q.back());
}

TEST(TestQueue, circular_buffer_works_correctly)
{
	Queue<int> q(3);
	q.push(1);
	q.push(2);
	q.push(3);
	q.pop(); 
	q.pop(); 

	q.push(4);
	q.push(5);


	EXPECT_EQ(3, q.front());
	EXPECT_EQ(5, q.back());
}

TEST(TestQueue, throws_when_pop_empty) 
{
	Queue<int> q(3);
	ASSERT_THROW(q.pop(), std::invalid_argument);
}

TEST(TestQueue, throws_when_front_empty)
{
	Queue<int> q(3);

	ASSERT_THROW(q.front(), std::invalid_argument);
}

TEST(TestQueue, throws_when_back_empty)
{
	Queue<int> q(3);
	ASSERT_THROW(q.back(), std::invalid_argument);
}

TEST(TestQueue, throws_when_push_full) 
{
	Queue<int> q(2);
	q.push(1);
	q.push(2);
	ASSERT_THROW(q.push(3), std::invalid_argument);
}

TEST(TestQueue, copy_constructor_works) 
{
	Queue<int> original(3);
	original.push(1);
	original.push(2);
	Queue<int> copy(original);

	EXPECT_EQ(original.front(), copy.front());
	original.pop();
	copy.pop();
	EXPECT_EQ(original.front(), copy.front());
}

TEST(TestQueue, copied_queue_is_independent) 
{
	Queue<int> original(3);
	original.push(1);
	original.push(2);

	Queue<int> copy(original);
	original.pop();

	EXPECT_EQ(2, original.front());
	EXPECT_EQ(1, copy.front());
}