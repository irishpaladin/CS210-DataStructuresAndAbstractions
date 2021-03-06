#include "indexType.h"
#include <algorithm>

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

indexNode indexType::Read() const
{
	// returns the value of the node pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read

	return { p->entry,p->height,p->left,p->right };
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
		return false;
	}
	catch (std::bad_alloc e)
	{
		return true;
	}
}

void indexType::Find(string word, indexNode* q)
{
		// assumes q is passed-by-value
		// sets p
	if (q == NULL || word == q->entry.word)
		p=q;
	else if (word < q->entry.word)
		Find(word, q->left);
	else
		Find(word, q->right);
	return;
}

void indexType::Insert(indexEntry& x)
{
	if (root == NULL) 
	{
		//if tree is empty
		indexNode* q = new indexNode;
		q->entry = x;
		q->height = 0;
		q->left = NULL;
		q->right = NULL;
		p = q;
		root = q;
	}
	else {
		insertHelper(x, root);
	}
}

void indexType::insertHelper(indexEntry &x, indexNode* &q)
{
	// assumes q is passed-by-reference
	// always call IsFull prior to calling Insert
	// always call IsPSet after calling Insert
	// sets p
	if (q == NULL) {
		q = new indexNode;
		q->entry = x;
		q->height = 0;
		q->left = NULL;
		q->right = NULL;
		p = q;
	}
	else if (x.word < q->entry.word) {
		insertHelper(x, q->left);
		if (p != NULL) {
			if (Height(q->left) - Height(q->right) == 2) {
				if (x.word < q->left->entry.word)
					LL(q);
				else
					LR(q);
			}
		}
	}
	else if (x.word > q->entry.word) {
		insertHelper(x, q->right);
		if (p != NULL) {
			if (Height(q->right) - Height(q->left) == 2) {
				if (x.word > q->right->entry.word)
					RR(q);
				else
					RL(q);
			}
		}
	}
	else {
		p = NULL; // assumes duplicates are not allowed
	}
	if (p != NULL)
		q->height = max(Height(q->left), Height(q->right)) + 1;
	return;
}

indexNode* indexType::getP() const
{
	//added to be able to access root
	return p;
}

void indexType::resetP()
{
	//sets P to root
	//added to be able to access the root
	p = root;
}

void indexType::LL(indexNode*& q)
{
	// assumes p is passed-by-reference
	indexNode* r = q->left;
	q->left = r->right;
	r->right = q;
	q->height = max(Height(q->left), Height(q->right)) + 1;
	r->height = max(Height(r->left), Height(r->right)) + 1;
	q = r;

	return;
}

void indexType::RR(indexNode*& q)
{
	// assumes q is passed-by-reference
	indexNode* r = q->right;
	q->right = r->left;
	r->left = q;
	q->height = max(Height(q->left), Height(q->right)) + 1;
	r->height = max(Height(r->left), Height(r->right)) + 1;
	q = r;
	
	return;
}

void indexType::LR(indexNode*& q)
{
		// assumes q is passed-by-reference
	RR(q->left);
	LL(q);
	return;
}

void indexType::RL(indexNode*& q)
{
	// assumes q is passed-by-reference
	LL(q->right);
	RR(q);
	return;
}

int indexType::Height(indexNode* q)
{
	if (q == NULL)
		return -1;
	else
		return q->height;
}

