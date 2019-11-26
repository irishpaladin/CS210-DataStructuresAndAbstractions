#ifndef BTREE_H
#define BTREE_H

const int PAGE_SIZE = 16; //m value
struct BTreeNode;
struct Keys;

struct Keys {
	int value;
	int offset;
	BTreeNode* next;
};
struct BTreeNode {
	bool root;
	bool leaf;
	int n;
	Keys page[PAGE_SIZE];
};
class BTree
{
public:
	BTree();
	bool IsPSet()const;
	bool IsISet()const;
	void ResetP();
	Keys Read()const;
	BTreeNode* GetP()const;
	void Write(Keys x);
	bool IsEmpty()const;
	bool IsFull()const;
	void Find(int value);
	void InsertRoot(int value, int offset);
	void Insert(int value, int offset);

private:
	BTreeNode* root;
	BTreeNode* p;
	int i;
	//private methods
	void Find(int x, BTreeNode* q); //recursive method for find
	void Insert(int value, int offset, BTreeNode*& q); //recursive method for insert
	bool SplitRoot(); //called by insert
	bool SplitChild(BTreeNode* q1, int k); //called by insert
};
#endif



