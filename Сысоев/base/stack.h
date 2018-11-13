#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
public:
	TStack(int _size = MaxStackSize)
	{
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw size;
		pMem = new T[size];
	}
	~TStack()
	{
		delete[] pMem;
	}
	bool IsEmpty()
	{
		return top == -1;
	}
	bool IsFull()
	{
		return top == size - 1;
	}
	T pop()
	{
		if (IsEmpty())
			throw "Error";
		return pMem[top--];
	}
	void push(T v)
	{
		if (IsFull())
			throw "Error";
		pMem[++top] = v;
	}
	T back()
	{
		if (IsEmpty())
			throw "Error";
		return pMem[top];
	}
};

#endif