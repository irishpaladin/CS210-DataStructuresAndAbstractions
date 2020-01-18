// LinkedList.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <cstdlib>
#include <iostream>
using namespace std;


const int MAX_LENGTH = 10;
typedef int DataType;

class ArrayList
{
public:
	//methods
	void Create();
	void ResetP();
	void Iterate();
	bool IsPSet()const;
	int GetP()const;
	void SetP(int q);
	DataType Read()const;
	void Write(DataType x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertUnsorted(DataType x);
	bool FindUnsorted(DataType x);
	void DeleteUnsorted();
	void InsertSorted(DataType x);
	bool FindSorted(DataType x);
	void DeleteSorted();
	void Clear();
	void DisplayArrayListValues(string descr)const;

private:
	int p;
	int length;
	DataType a[MAX_LENGTH];	
};



#endif
