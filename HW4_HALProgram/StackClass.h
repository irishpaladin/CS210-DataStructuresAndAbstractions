#ifndef STACKCLASS_H
#define STACKCLASS_H

const int MAX_HEIGHT = 8;
typedef int DataType;

class StackClass
{
public:
	StackClass();
	int Height()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void Push(int x);
	DataType Pop();
	int Top() const;
	void Clear();

private:
	int top;
	DataType a[MAX_HEIGHT];
};


#endif