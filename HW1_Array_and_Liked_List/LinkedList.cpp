//LinkedList.cpp

// Note: This implementation of LinkedList is based on 
// Chapter 4 of Bruno R. Preiss's Textbook: 
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#include <cstdlib>
#include <cassert>
#include "LinkedList.h"
using namespace std;



void LinkedList::Create()
{
	// this is the constructor
	// initializes the list
	p = nullptr;
	head = nullptr;
	length = 0;
}

void LinkedList::ResetP()
{
	//sets p
	p = nullptr;
	return;
}

void LinkedList::Iterate()
{
	// sets p to point to the next element in the list
	// always call ResetP prior to the initial call to Iterate
	// always call IsPSet after each call to Iterate
	if (p == NULL)
	{
		prevP = NULL;
		p = head;
	}	
	else
	{
		prevP = p;
		p = p->next;
	}
	return;
}

bool LinkedList::IsPSet()const
{
	//checks whether p points to a node in the list
	if (p == nullptr)
		return false;
	else
		return true;
}

Node* LinkedList::GetP()const
{
	//return the current value of p
	return p;
}

void LinkedList::SetP(Node* q)
{
	//always call IsEmpty prior to calling SetP
	//always call IsPSet after each call to SetP
	//sets p
	prevP = nullptr;
	while (p != nullptr && q != p) 
	{
		prevP = p;
		p = p->next;
	}
	return;
}

DataType LinkedList::Read() const
{
	// returns the value of the node pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return p->value;
}

void LinkedList::Write(DataType x)
{
	// writes a new value into the node pointed to by p
	// p must be set prior to calling Write
	// always call IsPSet prior to calling Write
	// could cause a problem in a sorted list if the key is changed
	p->value = x;
	return;
}

int LinkedList::Length() const
{
	// returns the number of nodes in the list
	return length;
}

bool LinkedList::IsEmpty() const
{
	// checks whether the list is empty
	if (length == 0)
		return true;
	else
		return false;
}

bool LinkedList::IsFull() const
{
	
	//checks whether the list is full
	Node* q;
	try
	{
		q = new Node;
		delete q;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}

void LinkedList::InsertHead(DataType x)
{
	// inserts a new node at the beginning of the list
	// always call IsFull prior to calling InsertHead
	// sets p
	p = new Node;
	p->value = x;
	p->next = head;
	prevP = NULL;
	head = p;
	length++;
	return;
}

void LinkedList::InsertSorted(DataType x)
{
	// inserts a new node in the list
	// always call IsFull prior to calling InsertSorted
	// sets p
	Node *q = new Node;
	prevP = nullptr;
	p = head;
	
	while (p != nullptr && x >= p->value)
	{
		prevP = p;
		p = p->next;
	}
	q->value = x;
	q->next = p;
	if (prevP == NULL)
		head = q;
	else
	{
		prevP->next = q;
		p = q;
		
	}	
	length++;
	return;
}

void LinkedList::InsertTail(DataType x)
{
	// inserts a new node at the end of the list
	// always call IsFull prior to calling InsertTail
	// always call IsEmpty prior to calling InsertTail
	// p must be set prior to calling InsertTail
	// always call IsPSet prior to calling InsertTail
	// starts scanning at the node p is pointing to
	// sets p
	Node* q = new Node;
	q->value = x;
	q->next = nullptr;
	while (p != nullptr)
	{
		prevP = p;
		p = p->next;
	}
	prevP->next = q;
	p = q;
	length++;
	return;
}

bool LinkedList::Find(DataType x)
{
	// scans the list from left to right
	// always call IsEmpty prior to calling Find
	// sets p
	prevP = nullptr;
	p = head;
	while (p != nullptr) {
		if (x == p->value)
		{
			return true;
		}
		prevP = p;
		p = p->next;
	}
	return false;
}

void LinkedList::DeleteHead()
{
	// deletes the first node in the list
	// always call IsEmpty prior to calling DeleteHead
	// sets p
	prevP = nullptr;
	p = head;
	head = head->next;
	delete p;
	p = head;
	length--;
	return;
}

void LinkedList::Delete()
{
	// deletes a node from the list
	// p must be set prior to calling Delete
	// always call IsPSet prior to calling Delete
	// sets p
	Node* q = nullptr;
	if (prevP == nullptr) {
		head = head->next;
		q = head;
	}
	else
	{
		if (p->next == nullptr)
			prevP->next = nullptr;
		else
		{
			prevP->next = p->next;
			q = p->next;
		}
	}		
	delete p;
	p = q;
	length--;
	return;
}

void LinkedList::DeleteTail()
{
	// deletes the last node in the list
	// always call IsEmpty prior to calling DeleteTail
	// p must be set prior to calling DeleteTail
	// always call IsPSet prior to calling DeleteTail
	// starts scanning at node p is pointing to
	// sets p
	while (p->next != nullptr) 
	{
		prevP = p;
		p = p->next;
	}
	//condition: just 1 node
	if (prevP == nullptr)
		head = nullptr;
	else
		//condition: more than one node
		prevP->next = nullptr;

	delete p;
	p = nullptr;
	length--;
	return;
}

void LinkedList::Clear()
{
	//reinitializes the list
	while (head != nullptr)
	{
		p = head;
		head = head->next;
		delete p;
	}
	p = nullptr;
	length = 0;
	return;
}

void LinkedList::DisplayLinkedListValues(string descr)const {
	//Displays value of P, Length and items of the array list
	cout << "\n -- LinkedList " << descr << " --" << endl << endl;
	int length = Length();
	cout << "   Head points to value  : ";
	if (head == nullptr)cout << "null"<<endl;
	else cout<<head->value << endl;
	cout << "   Value of Length: " << length << endl;
	cout << "   P points to value     : ";
	if (p == nullptr)cout << "null"<<endl;
	else cout<< p->value << endl;
	cout << "   The content of the current list is: " << endl;
	if (IsEmpty()) {
		cout << "   There is no element yet." << endl;
	}
	else {
		Node* q = head;
		while(q!=nullptr){
			cout << "   " << q->value;
			q = q->next;
		}
		cout << endl;
	}
}


