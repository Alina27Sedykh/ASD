
#include <gtest/gtest.h>
#include "../lib_alg/alg.h"
#include <gtest/gtest.h>
#include "Alg.h"

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
