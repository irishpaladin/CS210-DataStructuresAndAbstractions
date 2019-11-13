//occurenceTYype.h

#ifndef OCCURENCETYPE_H
#define OCCURENCETYPE_H
#include <cstdlib>
#include <iostream>
using namespace std;


const int MAX_LENGTH = 10;

struct occurenceLocation;
struct occurenceLocation {
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
	occurenceLocation Read()const;
	void Write(occurenceLocation x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertUnsorted(occurenceLocation x);
	bool FindUnsorted(occurenceLocation x);
	void DeleteUnsorted();
	void Clear();

private:
	int p;
	int length;
	occurenceLocation occurence[MAX_LENGTH];
};

#endif

