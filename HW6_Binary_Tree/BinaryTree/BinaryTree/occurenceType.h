//occurenceTYype.h

#ifndef OCCURENCETYPE_H
#define OCCURENCETYPE_H
#include <cstdlib>
#include <iostream>
using namespace std;


const int MAX_LENGTH = 10;

struct Occurence;
struct Occurence {
	int page;
	int position;
};

class occurenceType
{
public:
	//methods
	occurenceType();
	void ResetP();
	void Iterate();
	bool IsPSet()const;
	int GetP()const;
	void SetP(int q);
	Occurence Read()const;
	void Write(Occurence x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertUnsorted(Occurence x);
	bool FindUnsorted(Occurence x);
	void DeleteUnsorted();
	void Clear();

private:
	int p;
	int length;
	Occurence a[MAX_LENGTH];
};

#endif

