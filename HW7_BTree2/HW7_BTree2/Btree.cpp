#include "BTree.h"
#include <new>
#include <iostream>
using namespace std;

BTree::BTree()
{
	// this is the constructor
	// initializes the btree
	root = nullptr;
	p = nullptr;
	i = -1;
}

bool BTree::IsPSet() const
{
	// checks whether p points to a node in the tree
	if (p == nullptr)
		return false;
	return true;
}

bool BTree::IsISet() const
{
	// checks whether i points to a value in the page pointed to by p
	if (i == -1)
		return false;
	return true;
}

void BTree::ResetP()
{
	//need for accessing root outside the class
	//set p to root
	p = root;
}

Keys BTree::Read() const
{
	// returns the i-th value from the page pointed to by p
	// p must be set prior to calling Read
	// always call IsPSet prior to calling Read
	// i must be set prior to calling Read
	// always call IsISet prior to calling Read
	return p->page[i];
}

BTreeNode* BTree::GetP() const
{
	//need for accessing root node outside class
	//returns p
	return p;
}

void BTree::Write(Keys x)
{
	// writes the i-th value into the page pointed to by p
	// p must be set prior to calling Write
	// always call IsPSet prior to calling Write
	// i must be set prior to calling Write
	// always call IsISet prior to calling Write
	// will cause a problem if the key is changed
	p->page[i].value = x.value;
	p->page[i].offset = x.offset;
	return;
}

bool BTree::IsEmpty() const
{
	// checks whether the tree is empty
	if (root == nullptr)
		return true;
	return false;
}

bool BTree::IsFull() const
{
	try
	{
		BTreeNode* q = new BTreeNode;
		delete q;
		return false;
	}
	catch (std::bad_alloc e)
	{
		return true;
	}
}

void BTree::Find(int value)
{
	Find(value, root);
}

void BTree::InsertRoot(int value, int offset)
{
	// always call IsEmpty prior to calling InsertRoot
	// always call IsFull prior to calling InsertRoot
	// sets p
	root = new BTreeNode;
	root->root = true;
	root->leaf = true;
	for (int j = 0; j <= PAGE_SIZE - 1; j++) {
		root->page[j].value = 0;
		root->page[j].offset = 0;
		root->page[j].next = NULL;
	}

	root->page[0].value = value;
	root->page[0].offset = offset;
	root->n = 1;
	p = root;
	i = 0;
}

void BTree::Find(int x, BTreeNode* q)
{
	// assumes q is passed-by-value
	// always call IsEmpty prior to calling Find
	// sets p
	// sets i
	if (q->leaf) {
		int j = q->n - 1;
		for (; j >= 0; j--) {
			if (x == q->page[j].value)
			{
				p = q;
				i = j;
				return;
			}
		}
		if (j == -1) {
			p = NULL;
			i = -1;
		}

	}
	else {
		int j = q->n - 1;
		while (j > 0 && x < q->page[j].value) {
			j--;
		}
		Find(x, q->page[j].next);
	}
	return;
}

void BTree::Insert(int value, int offset)
{
	Insert(value, offset, root);
}

void BTree::Insert(int value, int offset, BTreeNode*& q)
{
	// assumes q is passed-by-reference
	// always call IsEmpty prior to calling to Insert
	// sets p
	if (q->n == PAGE_SIZE && q->root == true) //root and full
		if (SplitRoot())

			Insert(value, offset, root);
		else {
			p = NULL;
			i = -1;
		}
	else if (q->leaf == true) {//if leaf and not full
		int j = q->n - 1;
		while (j >= 0 && value < q->page[j].value) {
			q->page[j + 1].value = q->page[j].value;
			q->page[j + 1].offset = q->page[j].offset;
			j--;
		}

		j++;
		q->page[j].value = value;
		q->page[j].offset = offset;
		q->n++;
		p = q;
		i = j;
	}
	else {
		int j = q->n - 1;
		while (j > 0 && value < q->page[j].value) {
			j--;
		}

		if (q->page[j].next->n == PAGE_SIZE) {
			if (SplitChild(q, j)) {
				Insert(value, offset, q);
			}
			else {
				p = NULL;
				i = -1;
			}

		}

		else {
			Insert(value, offset, q->page[j].next);
			q->page[j].value = q->page[j].next->page[0].value;
			q->page[j].offset = q->page[j].next->page[0].offset;
		}

	}
	return;
}

bool BTree::SplitRoot()
{
	BTreeNode* q1 = root;

	if (IsFull())
		return false;
	BTreeNode* q2 = new BTreeNode;
	if (IsFull())
		return false;
	root = new BTreeNode;
	//part2
	for (int j = 0; j <= PAGE_SIZE - 1; j++) {
		root->page[j].value = 0;
		root->page[j].offset = 0;
		root->page[j].next = NULL;
		q2->page[j].value = 0;
		q2->page[j].offset = 0;
		q2->page[j].next = NULL;
	}

	for (int j = 0; j <= PAGE_SIZE / 2 - 1; j++) {
		q2->page[j].value = q1->page[(PAGE_SIZE + 1) / 2 + j].value;
		q2->page[j].offset = q1->page[(PAGE_SIZE + 1) / 2 + j].offset;
		q2->page[j].next = q1->page[(PAGE_SIZE + 1) / 2 + j].next;
	}
	
	q1->root = false;
	q2->root = false;
	if (q2->page[0].next == NULL) {
		q1->leaf = true;
		q2->leaf = true;
	}
	else {
		q1->leaf = false;
		q2->leaf = false;
	}
	q1->n = (PAGE_SIZE + 1) / 2;
	q2->n = PAGE_SIZE / 2;
	root->root = true;
	root->leaf = false;
	root->n = 2;
	root->page[0].value = q1->page[0].value;
	root->page[0].offset = q1->page[0].offset;
	root->page[0].next = q1;
	root->page[1].value = q2->page[0].value;
	root->page[1].offset = q2->page[0].offset;
	root->page[1].next = q2;

	//debugging purpose
	/*cout << endl << "rootsplit: ";
	display();
	cout << endl;*/
	return true;
}

bool BTree::SplitChild(BTreeNode* q1, int k)
{
	// assumes q1 is passed-by-value
	if (IsFull())
		return false;
	BTreeNode* q2 = new BTreeNode;
	for (int j = 0; j <= PAGE_SIZE - 1; j++) {
		q2->page[j].value = 0;
		q2->page[j].offset = 0;
		q2->page[j].next = NULL;
	}

	for (int j = 0; j <= PAGE_SIZE / 2 - 1; j++) {
		q2->page[j].value = q1->page[k].next->page[(PAGE_SIZE + 1) / 2 + j].value;
		q2->page[j].offset = q1->page[k].next->page[(PAGE_SIZE + 1) / 2 + j].offset;
		q2->page[j].next = q1->page[k].next->page[(PAGE_SIZE + 1) / 2 + j].next;
	}
	q2->root = false;
	if (q2->page[0].next == NULL)
		q2->leaf = true;
	else
		q2->leaf = false;
	q2->n = PAGE_SIZE / 2;
	q1->page[k].next->n = (PAGE_SIZE + 1) / 2;
	int j = q1->n - 1;
	while (j > k) {
		q1->page[j + 1].value = q1->page[j].value;
		q1->page[j + 1].offset = q1->page[j].offset;
		q1->page[j + 1].next = q1->page[j].next;
		j--;
	}
	j++;
	q1->page[j].value = q2->page[0].value;
	q1->page[j].offset = q2->page[0].offset;
	q1->page[j].next = q2;
	q1->n++;

	//debugging purpose
	/*cout << "splitChild: ";
	display();
	cout << endl;*/

	return true;
}