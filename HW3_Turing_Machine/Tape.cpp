//Tape.cpp

#include "Tape.h"

Tape::Tape()
{
	// this is the constructor
	// initializes the list
	p = NULL;
	head = NULL;
	length = 0;
}

void Tape::ResetP()
{
	// sets p
	p = NULL;
	return;
}

void Tape::IterateRight()
{
	// sets p to point ot the next node in the list
	// always call ResetP prior to the intial call to IterateRight
	// always call IsPSet after each call to IterateRight
	if (p == NULL)
		p = head;
	else
		p = p->next;
	return;
}

void Tape::IterateLeft()
{
	// sets p to point to the previous node in the list
	// always call IsPSet prior to each call to IterateLeft
	// always call IsPSet after each call to IterateLeft
	p = p->previous;
	return;
}

bool Tape::IsPSet() const
{
	// checks whether p points to a node in the list
	if (p == NULL)
		return false;
	return true;
}

DataType Tape::Read() const
{
	// returns the value of the node pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return p->value;
}

void Tape::Write(DataType x)
{
	// writes a new value into the node pointed to by p
	// p must be set prior to calling Write
	// always call IsPSet prior to calling Write
	// will cause a problem in a sorted list if the key is changed
	p->value = x;
	return;
}

int Tape::Length() const
{
	// returns the number of nodes in the list
	return length;
}

bool Tape::IsEmpty() const
{
	// checks whether the list is empty
	if (length == 0)
		return true;
	return false;
}

bool Tape::IsFull() const
{
	// checks whether the list is full
	//checks whether the list is full
	try
	{
		Node *q = new Node;
		delete q;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}

void Tape::InsertHead(DataType x)
{
	// inserts a new node at the beginning of the list
	// always call IsFull prior to calling InsertHead
	// sets p
	Node* q = new Node;
	q->value = x;
	q->previous = NULL;
	if (head == NULL)
		q->next = NULL;
	else
	{
		head->previous = q;
		q->next = head;
	}
	head = q;
	p = head;
	length++;
	return;
}

void Tape::InsertTail(DataType x)
{
	// inserts a new node at the end of the list
// always call IsFull prior to calling InsertTail
// always call IsEmpty prior to calling InsertTail
// p must be set prior to calling InsertTail
// always call IsPSet prior to calling InsertTail
// starts scanning at the node p is pointing to
// scans from left to right
// sets p
	Node* q = new Node;
	q->value = x;
	q->next = NULL;
	Node* prevP = p->previous;
	while (p != NULL) {
		prevP = p;
		p = p->next;
	};
			
	prevP->next = q;
	q->previous = prevP;
	p = q;
	length++;
	return;
}

Node* Tape::GetP() const
{
	// returns the current value of p
	return p;
}

void Tape::SetP(Node* q)
{
	// always call IsEmpty prior to calling SetP
	// always call IsPSet after each call to SetP
	// sets p
	p = head;
	while (p != NULL and q != p) {
		p = p->next;
	};
			
	return;
}

