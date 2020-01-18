// LinkedList.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstdlib>
#include <iostream>
using namespace std;

typedef int DataType;

struct Node;

struct Node
{
	DataType value;
	Node* next;
};

class LinkedList
{
public:
	void Create();
	void ResetP();
	void Iterate();
	bool IsPSet()const;
	Node* GetP()const;
	void SetP(Node* q);
	DataType Read()const;
	void Write(DataType x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertHead(DataType x);
	void InsertSorted(DataType x);
	void InsertTail(DataType x);
	bool Find(DataType x);
	void DeleteHead();
	void Delete();
	void DeleteTail();
	void Clear();

	void DisplayLinkedListValues(string descr)const;


private:
	Node* head;
	int length;
	Node* p;
	Node* prevP;
};


#endif
