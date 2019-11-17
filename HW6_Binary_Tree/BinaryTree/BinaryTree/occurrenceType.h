//occurrenceTYype.h

#ifndef occurrenceTYPE_H
#define occurrenceTYPE_H
#include <cstdlib>
#include <iostream>
using namespace std;


const int MAX_LENGTH = 65;

struct occurrenceLocation;
struct occurrenceLocation {
	int page;
	int position;
};

class occurrenceType
{
public:
	//methods
	occurrenceType();
	void ResetP();
	void Iterate();
	bool IsPSet()const;
	int GetP()const;
	void SetP(int q);
	occurrenceLocation Read()const;
	void Write(occurrenceLocation x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertUnsorted(occurrenceLocation x);
	bool FindUnsorted(occurrenceLocation x);
	//void DeleteUnsorted(); dont need to delete data
	void Clear();

private:
	int p;
	int length;
	occurrenceLocation occurrence[MAX_LENGTH];
};

#endif

