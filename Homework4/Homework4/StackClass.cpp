#include "StackClass.h"

StackClass::StackClass()
{
	// this is the constructor
	// initializes the stack
	// sets top
	top = -1;	
}

int StackClass::Height() const
{
	// returns the number of items on the stack
	return top+1;
}

bool StackClass::IsEmpty() const
{
	// checks whether the stack is empty
	if (top == -1)
		return true;
	else return false;
}

bool StackClass::IsFull() const
{
	// checks whether the stack is full
	if (top == MAX_HEIGHT - 1)
		return true;
	else
		return false;
}

void StackClass::Push(int x)
{
	// inserts a new item on the top of the stack
	// always call IsFull prior to calling Push
	// sets top
	top++;
	a[top] = x;
	return;
}

DataType StackClass::Pop()
{
	// removes the item on the top of the stack and returns the value it contained
	// always call IsEmpty prior to calling Pop
	// sets top
	int x = a[top];
	top--;
	return x;
}

int StackClass::Top() const
{
	// returns the value of the item on the top of the stack
	// always call IsEmppty prior to calling Top
	return a[top];
}

void StackClass::Clear()
{
	// reinitializes the stack
	// sets top
	top = -1;
	return;
}
