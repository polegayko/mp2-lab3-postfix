#include "postfix.h"
#include "stack.h"

bool TPostfix::IsOperation(char p)
{
	if ((p == '+') || (p == '-') || (p == '*') || (p == '/'))
		return true;
	return false;
}
bool TPostfix::CheckInfix()
{
	int a = 0, ops = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
			ops++;
		else if (!IsOperation(infix[i]) && infix[i] != '(' && infix[i] != ')')
		{
			while (infix[i] != '+' && infix[i] != '-'  && infix[i] != '*'  && infix[i] != '/')
			{
				i++;
				if (i == infix.size())
					break;
			}
			i--;
			a++;
		}
	}
	if (a != ops + 1)
		return false;
	int left = 0, right = 0;
	for (int i = 0; i < infix.size(); i++)
		if (infix[i] == '(')
			left++;
		else if (infix[i] == ')')
			right++;
	if (left != right)
		return false;
	if (infix[0] == ')' || infix[0] == '*' || infix[0] == '/' || infix[0] == '-' || infix[0] == '+')
		return false;
	if (infix[infix.size() - 1] == '(' || infix[infix.size() - 1] == '*' || infix[infix.size() - 1] == '/' || infix[infix.size() - 1] == '-' || infix[infix.size() - 1] == '+')
		return false;
	return true;
}
int TPostfix::Priority(char a, char b)
{
	if ((a == '*' || a == '/') && (b == '*' || b == '/'))
		return 0;
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	if ((a == '+' || a == '-') && (b == '+' || b == '-'))
		return 0;
	throw "not operation";
}
bool TPostfix::Operand(char op)
{
	for (char i = '0'; i <= '9'; i++)
		if (op == i)
			return true;
	return false;
}

string TPostfix::ToPostfix()
{
	if (!CheckInfix())
		throw "Error";
	TStack<char> ops(infix.size());
	for (int i = 0; i < infix.size(); i++)
	{
		if (!IsOperation(infix[i]) && infix[i] != '(' && infix[i] != ')')
		{
			int j = i;
			while (!IsOperation(infix[j]) && j != infix.size() && infix[j] != ')')
			{
				postfix += infix[j];
				j++;
			}
			i = j - 1;
			postfix += ',';
		}
		else if (ops.IsEmpty())
			ops.push(infix[i]);
		else if (ops.back() == '(')
			ops.push(infix[i]);
		else if (infix[i] == '(')
			ops.push(infix[i]);
		else if (infix[i] == ')')
		{
			while (ops.back() != '(')
			{
				postfix += ops.pop();
				postfix += ',';
			}
			ops.pop();
		}
		else if (Priority(infix[i], ops.back()) == 1)
			ops.push(infix[i]);
		else
		{
			while ((ops.back() != '('))
			{
				if (Priority(infix[i], ops.back()) == 1)
					break;
				postfix += ops.pop();
				postfix += ',';
				if (ops.IsEmpty())
					break;
			}
			ops.push(infix[i]);
		}
	}
	while (!ops.IsEmpty())
	{
		postfix += ops.pop();
		postfix += ',';
	}
	return postfix;
}

double TPostfix::Calculate()
{
	TStack<double>stack(postfix.size());
	string TMP = "";
	double tmp1, tmp2;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == ',')
			continue;
		if (Operand(postfix[i]))
		{
			TMP = "";
			TMP += postfix[i];
			while (Operand(postfix[i + 1]) || (postfix[i + 1] == '.'))
			{
				TMP += postfix[i + 1];
				i++;
			}
			stack.push(atof(TMP.c_str()));
		}
		else
		{
			tmp1 = stack.pop();
			tmp2 = stack.pop();
			switch (postfix[i]) {
			case'+':stack.push(tmp1 + tmp2); break;
			case'-':stack.push(tmp2 - tmp1); break;
			case'*':stack.push(tmp1 * tmp2); break;
			case'/':stack.push(tmp2 / tmp1); break;
			default: "Error";
			}
		}
	}
	return stack.pop();
}