#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix_1)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_2)
{
	string tmp = "1+2";
	ASSERT_NO_THROW(TPostfix p(tmp));
}
TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}

TEST(TPostfix, can_create_postfix_from_infix1)
{
	TPostfix p("a+b");
	p.ToPostfix();
	EXPECT_EQ("a,b,+,", p.GetPostfix());
}
TEST(TPostfix, can_not_start_infix_with_an_operation)
{
	TPostfix p("+a+1");
	EXPECT_FALSE(p.CheckInfix());
}

TEST(TPostfix, invalid_brackets)
{
	TPostfix p("(a+1))");
	EXPECT_FALSE(p.CheckInfix());
}
TEST(TPostfix, CheckInfix_return_true_when_infix_is_correct)
{
	TPostfix p("a+b");
	EXPECT_TRUE(p.CheckInfix());
}
TEST(TPostfix, can_create_postfix_from_infix)
{
	TPostfix p("a+b");
	EXPECT_EQ("a,b,+,", p.ToPostfix());
}


TEST(TPostfix, can_calculate_expression)
{
	TPostfix p("(3+4)*(9-4)");
	p.ToPostfix();
	EXPECT_EQ(54, p.Calculate());
}