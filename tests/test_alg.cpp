#include <gtest/gtest.h>
#include "Alg.h"
#include "DSV.h"

TEST(TestBreckets, SimpleCorrectSequences)
{
	EXPECT_TRUE(check_breckets("()"));
	EXPECT_TRUE(check_breckets("[]"));
	EXPECT_TRUE(check_breckets("{}"));
}

TEST(TestBreckets, MixedCorrectSequences)
{
	EXPECT_TRUE(check_breckets("()[]{}"));
	EXPECT_TRUE(check_breckets("({[]})"));
	EXPECT_TRUE(check_breckets("[({})]"));
	EXPECT_TRUE(check_breckets("{([])}"));
}

TEST(TestBreckets, NestedCorrectSequences)
{

	EXPECT_TRUE(check_breckets("((()))"));
	EXPECT_TRUE(check_breckets("[[[]]]"));
	EXPECT_TRUE(check_breckets("{{{}}}"));
	EXPECT_TRUE(check_breckets("({[()]})"));
}

TEST(TestBreckets, LongCorrectSequences)
{
	EXPECT_TRUE(check_breckets("((([[[{{{}}}]]])))"));
	EXPECT_TRUE(check_breckets("()()()()[][][]{}{}{}"));
	EXPECT_TRUE(check_breckets("({[{()}]})"));
}
TEST(TestBreckets, SimpleIncorrectSequences)
{
	EXPECT_FALSE(check_breckets("("));
	EXPECT_FALSE(check_breckets(")"));
	EXPECT_FALSE(check_breckets("["));
	EXPECT_FALSE(check_breckets("]"));
	EXPECT_FALSE(check_breckets("{"));
	EXPECT_FALSE(check_breckets("}"));
}

TEST(TestBreckets, MismatchedBracketTypes)
{
	EXPECT_FALSE(check_breckets("(]"));
	EXPECT_FALSE(check_breckets("{)"));
	EXPECT_FALSE(check_breckets("[}"));
	EXPECT_FALSE(check_breckets("([)]"));
	EXPECT_FALSE(check_breckets("{(})"));
}

TEST(TestBreckets, UnbalancedSequences)
{
	EXPECT_FALSE(check_breckets("(()"));
	EXPECT_FALSE(check_breckets("())"));
	EXPECT_FALSE(check_breckets("[[[]]"));
	EXPECT_FALSE(check_breckets("{}[]()("));
}
TEST(TestBreckets, ComplexIncorrectCases)
{
	
	EXPECT_FALSE(check_breckets("((())"));
	EXPECT_FALSE(check_breckets("{[}]"));
	EXPECT_FALSE(check_breckets("({[}])"));
	EXPECT_FALSE(check_breckets("){"));
}

TEST(IslandCountTest, can_count_single_island)
{

	std::vector<std::vector<int>> grid =
	{
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};
	ASSERT_NO_THROW(countIslands(grid));
	assert(countIslands(grid) == 1);
}

TEST(IslandCountTest, can_count_multiple_islands)
{
	std::vector<std::vector<int>> grid =
	{
		{1, 0, 1},
		{0, 0, 0},
		{1, 0, 1}
	};
	ASSERT_NO_THROW(countIslands(grid));
	assert(countIslands(grid) == 4);
}
