#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, can_create_stack_with_negativ_length)
{
	ASSERT_ANY_THROW(TStack<int>st(-1));
}
TEST(TStack, cant_create_too_large_length)
{
	ASSERT_ANY_THROW(TStack<int>st(MaxStackSize + 1));
}
TEST(TStack, check_IsEmpty_with_empty_stack)
{
	TStack<int> st(5);
	EXPECT_EQ(true, st.IsEmpty());
}
TEST(TStack, check_IsEmpty_with_not_empty_stack)
{
	TStack<int> st(5);
	st.push(2);
	EXPECT_EQ(false, st.IsEmpty());
}
TEST(TStack, check_IsFull_with_full_stack)
{
	TStack<int> st(2);
	st.push(1);
	st.push(2);
	EXPECT_EQ(true, st.IsFull());
}
TEST(TStack, check_IsFull_with_not_full_stack)
{
	TStack<int> st(5);
	st.push(2);
	EXPECT_EQ(false, st.IsFull());
}
TEST(TStack, throws_when_Pop_stack_IsEmty)
{
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.pop());
}
TEST(TStack, throws_when_Push_stack_IsFull)
{
	TStack<int> st(2);
	st.push(1);
	st.push(2);
	ASSERT_ANY_THROW(st.push(2));
}
TEST(TStack, can_add_value_to_stack_and_view_top_value)
{
	TStack<int> st(1);
	st.push(1);
	EXPECT_EQ(1, st.back());
}

TEST(TStack, can_delete_value_from_stack)
{
	TStack<int> st(2);
	st.push(1);
	st.push(2);
	st.pop();
	EXPECT_TRUE(st.back(), 1);
}
TEST(TStack, throw_when_take_value_from_empty_stack)
{
	TStack<int> st(1);
	ASSERT_ANY_THROW(st.pop());
}
TEST(TStack, can_take_value_from_stack)
{
	TStack<int> st(2);
	st.push(1);
	st.push(2);
	EXPECT_EQ(2, st.pop());
}