#include <gtest/gtest.h>
#include "../lib_list/list.h"


TEST(ListTest, DefaultConstructorCreatesEmptyList) 
{
    List<int> list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.size(), 0);
}

TEST(ListTest, PushFrontAddsElementToBeginning) 
{
    List<int> list;
    list.push_front(2);
    list.push_front(1);
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, PushBackAddsElementToEnd)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT_EQ(list.back(), 2);
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, PopFrontRemovesFirstElement) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_front();
    ASSERT_EQ(list.front(), 2);
    ASSERT_EQ(list.size(), 1);
}

TEST(ListTest, PopFrontOnEmptyListThrowsException) 
{
    List<int> list;
    ASSERT_THROW(list.pop_front(), std::runtime_error);
}

TEST(ListTest, PopBackRemovesLastElement) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    ASSERT_EQ(list.back(), 2);
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, PopBackOnEmptyListThrowsException)
{
    List<int> list;

    ASSERT_THROW(list.pop_back(), std::runtime_error);
}

TEST(ListTest, InsertAtBeginningWorksCorrectly) 
{
    List<int> list;
    list.push_back(2);
    list.push_back(3);
    list.insert(0, 1);
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(list.size(), 3);
}

TEST(ListTest, InsertAtEndWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.insert(2, 3);
    ASSERT_EQ(list.back(), 3);
    ASSERT_EQ(list.size(), 3);
}

TEST(ListTest, InsertInMiddleWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.front(), 1);
    list.pop_front();
    ASSERT_EQ(list.front(), 2);
}

TEST(ListTest, InsertAtInvalidPositionThrowsException) 
{
    List<int> list;
    list.push_back(1);
    ASSERT_THROW(list.insert(-1, 0), std::out_of_range);
    ASSERT_THROW(list.insert(5, 0), std::out_of_range);
}

TEST(ListTest, EraseAtBeginningWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(0);
    ASSERT_EQ(list.front(), 2);
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, EraseAtEndWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(2);
    ASSERT_EQ(list.back(), 2);
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, EraseInMiddleWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);

    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(list.back(), 3);
}

TEST(ListTest, EraseAtInvalidPositionThrowsException) 
{

    List<int> list;
    list.push_back(1);

    
    ASSERT_THROW(list.erase(-1), std::out_of_range);
    ASSERT_THROW(list.erase(5), std::out_of_range);
}

TEST(ListTest, FindExistingElementReturnsCorrectNode) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* found = list.find(2);
    ASSERT_NE(found, nullptr);
    ASSERT_EQ(found->value, 2);
}
TEST(ListTest, FindNonExistingElementReturnsNullptr) 
{
    List<int> list;
    list.push_back(1);
    Node<int>* found = list.find(999);
    ASSERT_EQ(found, nullptr);
}

TEST(ListTest, FindInEmptyListReturnsNullptr)
{
    
    List<int> list;
    Node<int>* found = list.find(1);
    ASSERT_EQ(found, nullptr);
}

TEST(ListTest, ClearRemovesAllElements) \
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.size(), 0);
}

TEST(ListTest, ClearOnEmptyListDoesNothing) 
{
    
    List<int> list;

    ASSERT_NO_THROW(list.clear());
    ASSERT_TRUE(list.is_empty());
}

TEST(ListTest, CopyConstructorCreatesDeepCopy)
{
   
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copied(original);

    ASSERT_EQ(copied.size(), 3);

    original.pop_front();
    ASSERT_EQ(copied.size(), 3);
    ASSERT_EQ(copied.front(), 1);
}

TEST(ListTest, AssignmentOperatorCreatesDeepCopy) 
{

    List<int> original;
    original.push_back(1);
    original.push_back(2);
    List<int> assigned;

    assigned = original;

    ASSERT_EQ(assigned.size(), 2);

    original.pop_front();
    ASSERT_EQ(assigned.size(), 2);
}

TEST(ListTest, SelfAssignmentDoesNothing) 
{

    List<int> list;
    list.push_back(1);
    list.push_back(2);

    ASSERT_NO_THROW(list = list);
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, InsertAfterNodeWorksCorrectly)
{
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    Node<int>* first_node = list.find(1);
    list.insert(first_node, 2);

    ASSERT_EQ(list.size(), 3);

    ASSERT_EQ(list.front(), 1);
    list.pop_front();
    ASSERT_EQ(list.front(), 2);
    list.pop_front();
    ASSERT_EQ(list.front(), 3);
}

TEST(ListTest, EraseNodeWorksCorrectly)
{

    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* node_to_erase = list.find(2);
    list.erase(node_to_erase);

    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(list.back(), 3);
}

TEST(ListTest, EraseFirstNodeWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    Node<int>* node_to_erase = list.find(1);
    list.erase(node_to_erase);

    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.front(), 2);
}

TEST(ListTest, EraseLastNodeWorksCorrectly) 
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    Node<int>* node_to_erase = list.find(2);
    list.erase(node_to_erase);

    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.front(), 1);
}

TEST(ListTest, SingleElementListOperations) 
{
    List<int> list;
    list.push_back(42);

    ASSERT_EQ(list.front(), 42);
    ASSERT_EQ(list.back(), 42);
    ASSERT_EQ(list.size(), 1);
    ASSERT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front());
    ASSERT_TRUE(list.is_empty());
}

TEST(ListTest, MultipleOperationsWorkTogether)
{
    
    List<int> list;

    list.push_back(1);
    list.push_front(0);
    list.push_back(2);
    list.insert(1, 999);
    list.erase(1);

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.front(), 0);
    ASSERT_EQ(list.back(), 2);
}

TEST(ListTest, WorksWithStringType)
{
    List<std::string> string_list;

    string_list.push_back("hello");
    string_list.push_back("world");

    ASSERT_EQ(string_list.size(), 2);
    ASSERT_EQ(string_list.front(), "hello");
    ASSERT_EQ(string_list.back(), "world");
}
