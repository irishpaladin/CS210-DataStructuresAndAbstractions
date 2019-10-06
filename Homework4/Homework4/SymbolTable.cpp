#include "SymbolTable.h"
#include <cstdlib>
using namespace std;

//---------------------------------------------------
//List Element Members
//---------------------------------------------------
//ListElement::ListElement(int _datum, ListElement * _next):
//   datum (_datum), next (_next)
//{}


SymbolTable::SymbolTable() {
	// this is the constructor
	// initializes the list
	length = 0;
	p = -1;
	for (int i = 0; i < MAX_LENGTH; i++) {
		symbols[i].symbol = "";
		symbols[i].value = 0;
	}
}

void SymbolTable::ResetP() {
	// sets p
	p = -1;
	return;
}

//not too sure
void SymbolTable::Iterate() {
	// sets p to point to the next element in the list
	// always call ResetP prior to the initial call to Iterate
	// always call IsPSet after each call to Iterate
	p++;
	return;
}


bool SymbolTable::IsPSet()const {
	// checks whether p points to an element in the list
	if (p < 0 || p > length - 1)
		return false;
	else return true;
}

int SymbolTable::GetP()const {
	// returns the current value of p
	return p;
}

void SymbolTable::SetP(int q) {
	// always call IsPSet after each call to SetP
	// sets p
	p = q;
	return;
}
int SymbolTable::Read()const {
	// returns the value of the element pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return symbols[p].value;
}

void SymbolTable::Write(int x) {
	// writes a new value into the element pointed to by p
	// p must be set prior to calling Write
	// always call IsPSet prior to calling Write
	// could cause a problem in a sorted list if the key is changed
	symbols[p].value = x;
	return;
}

int SymbolTable::Length()const {
	// returns the number of elements in the list
	return length;
}

bool SymbolTable::IsEmpty()const {
	// checks whether the list is empty
	if (length == 0)
		return true;
	else return false;
}

bool SymbolTable::IsFull()const {
	// checks whether the list is full
	if (length == MAX_LENGTH)
		return true;
	else return false;
}

//void SymbolTable::InsertUnsorted(string s, int x) {
//	// inserts a new element at the end of the list
//	// always call IsFull prior to calling InsertUnsorted
//	// sets p
//	p = length;
//	symbols[p].symbol = s;
//	symbols[p].value = x;
//	length++;
//	return;
//}

//bool SymbolTable::FindUnsorted(string s, int x) {
//	// always call IsEmpty prior to calling FindUnsorted
//	// sets p
//	p = 0;
//	while (p < length) {
//		if (s == symbols[p].symbol && x == symbols[p].value) {
//			return true;
//		}
//		p++;
//	}
//	return false;
//
//}
//void SymbolTable::DeleteUnsorted() {
//	// deletes element pointed to by p
//	// p must be set prior to calling DeleteUnsorted
//	// always call IsPSet prior to calling DeleteUnsorted
//	// moves the last element into the element pointed to by p
//	a[p] = a[length - 1];
//	length--;
//	return;
//}



void SymbolTable::InsertSorted(string s, int x) {
	// inserts a new element into the list in sorted order
	// always call IsFull prior to calling InsertSorted
	// p will point to where the new element should be inserted
	// moves all elements to the right of p one element to the right to make space for the new element
	// sets p
	p = 0;
	while (p < length && s > symbols[p].symbol) {
		p++;
	}
	int q = length;
	while (q > p) {
		symbols[q].symbol = symbols[q - 1].symbol;
		symbols[q].value = symbols[q - 1].value;
		q--;
	}
	symbols[p].symbol = s;
	symbols[p].value = x;
	length++;
	return;
}

bool SymbolTable::FindSorted(string x) {
	// binary search
	// always call IsEmpty prior to calling FindSorted
	// sets p
	int q = 0;
	int r = length - 1;
	while (q <= r){
		p = (q + r) / 2;
		if (x < symbols[p].symbol)
			r = p - 1;
		else if (x > symbols[p].symbol)
			q = p + 1;
		else
			return true;
				
	}	
	return false;
}

void SymbolTable::Clear() {
	// reinitializes the list
	length = 0;
	p = -1;
	return;
}

void SymbolTable::Display()const {
	//Displays value of P, Length and items of the array list
	cout << endl << endl;
	int length = Length();
	cout << "Symbol Table" << endl;
	cout << "   Value of P     : " << p << endl;
	cout << "   Value of Length: " << length << endl;
	cout << "   The content of the current list is: " << endl;
	if (IsEmpty()) {
		cout << "   There is no element yet." << endl;
	}
	else {
		for (int i = 0; i < length; i++) {
			cout <<"["<<i<< "] symbol: " << symbols[i].symbol <<"   value: "<<symbols[i].value<<endl<<endl;
		}
		cout << endl;
	}
}


