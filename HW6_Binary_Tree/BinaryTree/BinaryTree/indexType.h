//indexType.h 

#ifndef INDEXTYPE_H
#define INDEXTYPE_H
#include <iostream>
#include "occurrenceType.h"

using namespace std;

struct indexEntry;
struct indexEntry {
	string word;
	occurrenceType occurrences;
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
	indexNode Read()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void Find(string word, indexNode* q);// dunno what to do
	void Insert(indexEntry& new_entry);//kind of complicated
	indexNode* getP() const; //method for traversing the tree
	void resetP();	//method needed for traversing the tree

private:
	indexNode* root;
	indexNode* p;
	//methods
	//its not changing the root
	void insertHelper(indexEntry &new_entry, indexNode* &q);//kind of complicated
	void LL(indexNode*& q);
	void RR(indexNode*& q);
	void LR(indexNode*& q);
	void RL(indexNode*& q);
	int Height(indexNode* q);
};
#endif

