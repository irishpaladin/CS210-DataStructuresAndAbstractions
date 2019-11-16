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
		cout << "Insert root " << x.word << endl;
		indexNode* q = new indexNode;
		q->entry = x;
		q->height = 0;
		q->left = NULL;
		q->right = NULL;
		p = q;
		root = q;
	}
	else {
		cout << "Insert helper " << x.word << endl;
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
		cout << "Inserted " << x.word << endl << endl;
		p = q;
	}
	else if (x.word < q->entry.word) {
		cout << "left > ";
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
		cout << "right > ";
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
	return p;
}

void indexType::resetP()
{
	//sets P to root
	p = root;
}

void indexType::LL(indexNode* q)
{
	// assumes p is passed-by-reference
	cout << " LL > " +q->entry.word << endl << endl;
	if (q == root)
		root = q->left;
	indexNode* r = q->left;
	q->left = r->right;
	r->right = q;
	q->height = max(Height(q->left), Height(q->right)) + 1;
	r->height = max(Height(r->left), Height(r->right)) + 1;
	q = r;
	cout << "After RR: " + q->left->entry.word + " <- " + q->entry.word + " -> " + q->right->entry.word;
	return;
}

void indexType::RR(indexNode* q)
{
	// assumes q is passed-by-reference
	cout << " RR > " + q->entry.word << endl;
	if (q == root)
		root = q->right;
	indexNode* r = q->right;
	q->right = r->left;
	r->left = q;
	q->height = max(Height(q->left), Height(q->right)) + 1;
	r->height = max(Height(r->left), Height(r->right)) + 1;
	q = r;

	cout << "After RR: " + q->left->entry.word + " <- " + q->entry.word + " -> " + q->right->entry.word << endl << endl;
	return;
}

void indexType::LR(indexNode* q)
{
	cout << "LR > ";
		// assumes q is passed-by-reference
	RR(q->left);
	LL(q);
	return;
}

void indexType::RL(indexNode* q)
{
	// assumes q is passed-by-reference
	cout << "RL > ";
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

