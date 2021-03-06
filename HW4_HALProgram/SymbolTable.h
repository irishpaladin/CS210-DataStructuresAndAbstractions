// LinkedList.h

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <iostream>
using namespace std;


const int MAX_LENGTH = 10;

struct SymbolRow {
	string symbol;
	int value;
};

class SymbolTable
{
public:
	//methods
	SymbolTable();
	void ResetP();
	void Iterate();
	bool IsPSet()const;
	int GetP()const;
	void SetP(int q);
	int Read()const;
	void Write(int x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertSorted(string s, int x);
	bool FindSorted(string s);
	void Clear();

private:
	int p;
	int length;
	SymbolRow symbols[MAX_LENGTH];
};



#endif
