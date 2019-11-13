//indexType.h 

#ifndef INDEXTYPE_H
#define INDEXTYPE_H
#include <iostream>
#include "occurenceType.h"

using namespace std;

struct indexEntry;
struct indexEntry {
	string word;
	occurenceType occurences;
};

//AVL Node structure
struct indexNode;
struct indexNode {
	indexEntry entry;
	int height;
	indexNode* left;
	indexNode* right;
};

class indexType
{
public:
	indexType();
	bool IsPSet()const;
	indexEntry Read()const; //i might need height
	//void Write(indexEntry);	no need for write we wont change the data in the file
	bool IsEmpty()const;
	bool IsFull()const;
	//void Find() dunno what to do


private:
	indexNode* root;
	indexNode* p;
};
#endif

