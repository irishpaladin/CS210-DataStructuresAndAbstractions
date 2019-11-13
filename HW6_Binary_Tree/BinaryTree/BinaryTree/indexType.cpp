#include "indexType.h"

indexType::indexType()
{
	// this is the constructor
	// initializes the tree
	p = NULL;
	root = NULL;
}

bool indexType::IsPSet() const
{
	// checks whether p points to a node in the tree
	if (p == NULL)
		return false;
	return true;
}

indexEntry indexType::Read() const
{
	// returns the value of the node pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return p->entry;
}

bool indexType::IsEmpty() const
{
	// checks whether the tree is empty
	if (root == NULL)
		return true;
	return false;
}

bool indexType::IsFull() const
{
	// checks whether the tree is full
	try
	{
		indexNode* q = new indexNode;
		delete q;
	}
	catch (std::bad_alloc e)
	{
		return true;
	}
}

