#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(TestQueue, can_create_queue) 
{
	// Arrange & Act & Assert
	ASSERT_NO_THROW(Queue<int> q(5));
}

TEST(TestQueue, created_queue_is_empty) 
{
	// Arrange
	Queue<int> q(5);

	// Act & Assert
	EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, can_push_element)
{
	// Arrange
	Queue<int> q(3);

	// Act & Assert
	ASSERT_NO_THROW(q.push(10));
}

TEST(TestQueue, push_changes_empty_status) 
{
	// Arrange
	Queue<int> q(3);

	// Act
	q.push(10);

	// Assert
	EXPECT_FALSE(q.is_empty());
}

TEST(TestQueue, can_pop_element)
{
	// Arrange
	Queue<int> q(3);
	q.push(10);

	// Act & Assert
	ASSERT_NO_THROW(q.pop());
}

TEST(TestQueue, can_get_front_element) 
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	// Act & Assert
	ASSERT_NO_THROW(q.front());
}

TEST(TestQueue, front_returns_correct_element)
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	// Act
	int result = q.front();

	// Assert
	int expected = 10;
	EXPECT_EQ(expected, result);
}

TEST(TestQueue, can_get_back_element)
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	// Act & Assert
	ASSERT_NO_THROW(q.back());
}

TEST(TestQueue, back_returns_correct_element)
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	// Act
	int result = q.back();

	// Assert
	int expected = 20;
	EXPECT_EQ(expected, result);
}

TEST(TestQueue, pop_removes_front_element)
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);
	q.push(30);

	// Act
	q.pop();

	// Assert
	EXPECT_EQ(20, q.front());
}

TEST(TestQueue, can_detect_full_queue) 
{
	// Arrange
	Queue<int> q(2);
	q.push(10);
	q.push(20);

	// Act & Assert
	EXPECT_TRUE(q.is_full());
}

TEST(TestQueue, can_clear_queue) 
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);

	// Act
	q.clear();

	// Assert
	EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, push_after_clear_works) 
{
	// Arrange
	Queue<int> q(3);
	q.push(10);
	q.push(20);
	q.clear();

	// Act
	q.push(30);

	// Assert
	EXPECT_EQ(30, q.front());
	EXPECT_EQ(30, q.back());
}

TEST(TestQueue, circular_buffer_works_correctly)
{
	// Arrange
	Queue<int> q(3);
	q.push(1);
	q.push(2);
	q.push(3);
	q.pop(); // Remove 1
	q.pop(); // Remove 2

	// Act
	q.push(4);
	q.push(5);

	// Assert
	EXPECT_EQ(3, q.front());
	EXPECT_EQ(5, q.back());
}

TEST(TestQueue, throws_when_pop_empty) 
{
	// Arrange
	Queue<int> q(3);

	// Act & Assert
	ASSERT_THROW(q.pop(), std::invalid_argument);
}

TEST(TestQueue, throws_when_front_empty)
{
	// Arrange
	Queue<int> q(3);

	// Act & Assert
	ASSERT_THROW(q.front(), std::invalid_argument);
}

TEST(TestQueue, throws_when_back_empty)
{
	// Arrange
	Queue<int> q(3);

	// Act & Assert
	ASSERT_THROW(q.back(), std::invalid_argument);
}

TEST(TestQueue, throws_when_push_full) 
{
	// Arrange
	Queue<int> q(2);
	q.push(1);
	q.push(2);

	// Act & Assert
	ASSERT_THROW(q.push(3), std::invalid_argument);
}

TEST(TestQueue, copy_constructor_works) 
{
	// Arrange
	Queue<int> original(3);
	original.push(1);
	original.push(2);

	// Act
	Queue<int> copy(original);

	// Assert
	EXPECT_EQ(original.front(), copy.front());
	original.pop();
	copy.pop();
	EXPECT_EQ(original.front(), copy.front());
}

TEST(TestQueue, copied_queue_is_independent) 
{
	// Arrange
	Queue<int> original(3);
	original.push(1);
	original.push(2);

	// Act
	Queue<int> copy(original);
	original.pop();

	// Assert
	EXPECT_EQ(2, original.front());
	EXPECT_EQ(1, copy.front());
}