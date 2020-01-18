//LinkedList.cpp

// Note: This implementation of LinkedList is based on 
// Chapter 4 of Bruno R. Preiss's Textbook: 
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#include <cstdlib>
#include <cassert>
#include "ArrayList.h"
using namespace std;

//---------------------------------------------------
//List Element Members
//---------------------------------------------------
//ListElement::ListElement(int _datum, ListElement * _next):
//   datum (_datum), next (_next)
//{}


void ArrayList::Create() {
	// this is the constructor
	// initializes the list
	length = 0;
	p = -1;
}

void ArrayList::ResetP() {
	// sets p
	p = -1;
	return;
}

//not too sure
void ArrayList::Iterate() {
	// sets p to point to the next element in the list
	// always call ResetP prior to the initial call to Iterate
	// always call IsPSet after each call to Iterate
	p++;
	return;
}


bool ArrayList::IsPSet()const {
	// checks whether p points to an element in the list
	if (p < 0 || p > length - 1)
		return false;
	else return true;
}

int ArrayList::GetP()const {
	// returns the current value of p
	return p;
}

void ArrayList::SetP(int q) {
	// always call IsPSet after each call to SetP
	// sets p
	p = q;
	return;
}
DataType ArrayList::Read()const {
	// returns the value of the element pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return a[p];
}

void ArrayList::Write(DataType x) {
	// writes a new value into the element pointed to by p
	// p must be set prior to calling Write
	// always call IsPSet prior to calling Write
	// could cause a problem in a sorted list if the key is changed
	a[p] = x;
	return;
}

int ArrayList::Length()const {
	// returns the number of elements in the list
	return length;
}

bool ArrayList::IsEmpty()const {
	// checks whether the list is empty
	if (length == 0)
		return true;
	else return false;
}

bool ArrayList::IsFull()const {
	// checks whether the list is full
	if (length == MAX_LENGTH)
		return true;
	else return false;
}

void ArrayList::InsertUnsorted(DataType x) {
	// inserts a new element at the end of the list
	// always call IsFull prior to calling InsertUnsorted
	// sets p
	p = length;
	a[p] = x;
	length++;
	return;
}

bool ArrayList::FindUnsorted(DataType x) {
	// always call IsEmpty prior to calling FindUnsorted
	// sets p
	p = 0;
	while (p < length) {
		if (x == a[p]) {
			return true;
		}
		p++;
	}
	return false;
			
}
void ArrayList::DeleteUnsorted() {
	// deletes element pointed to by p
	// p must be set prior to calling DeleteUnsorted
	// always call IsPSet prior to calling DeleteUnsorted
	// moves the last element into the element pointed to by p
	a[p] = a[length - 1];
	length--;
	return;
}
void ArrayList::InsertSorted(DataType x) {
	// inserts a new element into the list in sorted order
	// always call IsFull prior to calling InsertSorted
	// p will point to where the new element should be inserted
	// moves all elements to the right of p one element to the right to make space for the new element
	// sets p
	p = 0;
	while (p < length && x > a[p]) {
		p++;
	}
	int q = length;
	while (q > p) {
		a[q] = a[q - 1];
		q--;
	}
	a[p] = x;
	length++;
	return;
}

bool ArrayList::FindSorted(DataType x) {
	// always call IsEmpty prior to calling FindUnsorted
	// sets p
	p = 0;
	while (p < length) {
		if (x == a[p]) {
			return true;
		}
		p++;			
	}
	return false;
	
			
}
void ArrayList::DeleteSorted() {
	// deletes element pointed to by p
	// p must be set prior to calling DeleteSorted
	// always call IsPSet prior to calling DeleteSorted
	// all elements following the one pointed to by p are moved one element to the left
	// sets p
	int q = p;
	p++;
	while (p < length) {
		a[p - 1] = a[p];
		p++;
	}	
	length--;
	p = q;
	return;
}

void ArrayList::Clear() {
	// reinitializes the list
	length = 0;
	p = -1;
	return;
}

void ArrayList::DisplayArrayListValues(string descr)const{
	//Displays value of P, Length and items of the array list
	cout << "\n -- ArrayList " << descr << " --" << endl << endl;
	int length = Length();
	cout << "   Value of P     : " << p << endl;
	cout << "   Value of Length: " << length << endl;
	cout << "   The content of the current list is: " << endl;
	if (IsEmpty()) {
		cout << "   There is no element yet." << endl;
	}
	else {
		for (int i = 0; i < length; i++) {
			cout << "   " << a[i];
		}
		cout << endl;
	}
}


