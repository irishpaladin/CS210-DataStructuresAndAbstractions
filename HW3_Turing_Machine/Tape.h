//Tape.h

#ifndef TAPE_H
#define TAPE_H
#include <iostream>
using namespace std;

typedef char DataType;

struct Node;

struct Node
{
	Node* previous;
	DataType value;
	Node* next;
};
class Tape {
private:
	Node* head;
	int length;
	Node* p;

public:
	Tape();
	void ResetP();
	void IterateRight();
	void IterateLeft();
	bool IsPSet()const;
	DataType Read()const;
	void Write(DataType x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertHead(DataType x);
	void InsertTail(DataType x);
	Node* GetP() const;
	void SetP(Node* q);
};


#endif
