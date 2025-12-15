#include <gtest/gtest.h>
#include "Alg.h"
#include "DSV.h"
#include "List.h"

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


TEST(HareAndTurtleTest, EmptyListNoCycle)
{
    List<int> list;
    ASSERT_FALSE(has_cycle_hare_and_turtle(list));
}

TEST(HareAndTurtleTest, SingleElementNoCycle)
{
    List<int> list;
    list.push_back(1);
    ASSERT_FALSE(has_cycle_hare_and_turtle(list));
}

TEST(HareAndTurtleTest, MultipleElementsNoCycle)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    ASSERT_FALSE(has_cycle_hare_and_turtle(list));
}
TEST(TestCycleList, has_cycle_hare_and_turtle_work_correctly_in_empty_list) {
    List<int> l1;
    EXPECT_EQ(has_cycle_hare_and_turtle(l1), false);
}

TEST(TestCycleList, has_cycle_hare_and_turtle_work_correctly_in_no_empty_list_without_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    EXPECT_EQ(has_cycle_hare_and_turtle(l1), false);

    List<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);

    EXPECT_EQ(has_cycle_hare_and_turtle(l2), false);
}

TEST(TestCycleList, has_cycle_hare_and_turtle_work_correctly_in_no_empty_list_with_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.tail()->next = l1.head()->next->next;
    EXPECT_EQ(has_cycle_hare_and_turtle(l1), true);
    l1.pop_back();

    List<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);
    l2.tail()->next = l2.head();
    EXPECT_EQ(has_cycle_hare_and_turtle(l2), true);
    l2.pop_back();

    List<int> l3;
    l3.push_back(1);
    l3.push_back(2);
    l3.tail()->next = l3.tail();
    EXPECT_EQ(has_cycle_hare_and_turtle(l3), true);
    l3.pop_back();
}

TEST(TestCycleList, has_cycle_problem_node_work_correctly_in_empty_list) {
    List<int> l1;
    EXPECT_EQ(has_cycle_problem_node(l1), nullptr);
}

TEST(TestCycleList, has_cycle_problem_node_work_correctly_in_no_empty_list_without_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    EXPECT_EQ(has_cycle_problem_node(l1), nullptr);
}

TEST(TestCycleList, has_cycle_problem_node_work_correctly_in_no_empty_list_with_cycles) {
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    Node<int>* cycle_node = l1.head()->next->next; 
    l1.tail()->next = cycle_node;
    Node<int>* result = has_cycle_problem_node(l1);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, cycle_node);
    l1.pop_back();

    List<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);
    l2.tail()->next = l2.head();
    Node<int>* result2 = has_cycle_problem_node(l2);
    EXPECT_NE(result2, nullptr);
    EXPECT_EQ(result2, l2.head());
    l2.pop_back();

    List<int> l3;
    l3.push_back(1);
    l3.push_back(2);
    l3.tail()->next = l3.tail();

    Node<int>* result3 = has_cycle_problem_node(l3);
    EXPECT_NE(result3, nullptr);
    EXPECT_EQ(result3, l3.tail());
    l3.pop_back();
}

TEST(TestCycleList, has_cycle_reverse_pointers_work_correctly_in_no_empty_list_without_cycles)
{
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    EXPECT_EQ(has_cycle_reverse_pointers(l1), false);
}

TEST(TestCycleList, has_cycle_reverse_pointers_work_correctly_in_no_empty_list_with_cycles) 
{
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.tail()->next = l1.head()->next->next;
    EXPECT_EQ(has_cycle_reverse_pointers(l1), true);

    List<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);
    l2.tail()->next = l2.head();
    EXPECT_EQ(has_cycle_reverse_pointers(l2), true);

    List<int> l3;
    l3.push_back(1);
    l3.push_back(2);
    l3.tail()->next = l3.tail();
    EXPECT_EQ(has_cycle_reverse_pointers(l3), true);


}

