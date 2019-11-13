//occurenceType.cpp

// Note: This implementation of LinkedList is based on 
// Chapter 4 of Bruno R. Preiss's Textbook: 
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#include <cstdlib>
#include <cassert>
#include "occurenceType.h"
using namespace std;


//---------------------------------------------------
//List Element Members
//---------------------------------------------------
//ListElement::ListElement(int _datum, ListElement * _next):
//   datum (_datum), next (_next)
//{}


occurenceType::occurenceType() {
	// this is the constructor
	// initializes the list
	length = 0;
	p = -1;
}

void occurenceType::ResetP() {
	// sets p
	p = -1;
	return;
}

//not too sure
void occurenceType::Iterate() {
	// sets p to point to the next element in the list
	// always call ResetP prior to the initial call to Iterate
	// always call IsPSet after each call to Iterate
	p++;
	return;
}


bool occurenceType::IsPSet()const {
	// checks whether p points to an element in the list
	if (p < 0 || p > length - 1)
		return false;
	else return true;
}

int occurenceType::GetP()const {
	// returns the current value of p
	return p;
}

void occurenceType::SetP(int q) {
	// always call IsPSet after each call to SetP
	// sets p
	p = q;
	return;
}
occurenceLocation occurenceType::Read()const {
	// returns the value of the element pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return occurence[p];
}

void occurenceType::Write(occurenceLocation x) {
	// writes a new value into the element pointed to by p
	// p must be set prior to calling Write
	// always call IsPSet prior to calling Write
	// could cause a problem in a sorted list if the key is changed
	occurence[p].page = x.page;
	occurence[p].position = x.position;
	return;
}

int occurenceType::Length()const {
	// returns the number of elements in the list
	return length;
}

bool occurenceType::IsEmpty()const {
	// checks whether the list is empty
	if (length == 0)
		return true;
	else return false;
}

bool occurenceType::IsFull()const {
	// checks whether the list is full
	if (length == MAX_LENGTH)
		return true;
	else return false;
}

void occurenceType::InsertUnsorted(occurenceLocation x) {
	// inserts a new element at the end of the list
	// always call IsFull prior to calling InsertUnsorted
	// sets p
	p = length;
	occurence[p].page = x.page;
	occurence[p].position = x.position;
	length++;
	return;
}

bool occurenceType::FindUnsorted(occurenceLocation x) {
	// always call IsEmpty prior to calling FindUnsorted
	// sets p
	p = 0;
	while (p < length) {
		if (x.page == occurence[p].page && x.position == occurence[p].position) {
			return true;
		}
		p++;
	}
	return false;

}
void occurenceType::DeleteUnsorted() {
	// deletes element pointed to by p
	// p must be set prior to calling DeleteUnsorted
	// always call IsPSet prior to calling DeleteUnsorted
	// moves the last element into the element pointed to by p
	occurence[p] = a[length - 1];
	length--;
	return;
}

void occurenceType::Clear() {
	// reinitializes the list
	length = 0;
	p = -1;
	return;
}



