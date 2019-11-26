#ifndef BTREE_H
#define BTREE_H

const int PAGE_SIZE = 5; //that's m
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
	int n; //how many key
	Keys page[PAGE_SIZE];
};
class BTree
{
public:
	BTree();
	bool IsPSet()const;
	bool IsISet()const;
	Keys Read()const;//might need the offset as well
	void Write(Keys x);//might need to set offset as well
	bool IsEmpty()const;
	bool IsFull()const;
	
	void Find(int value);//
	void InsertRoot(int value, int offset);//
	void Insert(int value, int offset);//might need offset


private:
	BTreeNode* root;
	BTreeNode* p;
	int i;
	//private methods
	void Find(int x, BTreeNode* q); //recursive method for find
	void Insert(int value, int offset, BTreeNode*& q); //might need offset as well
	bool SplitRoot();
	bool SplitChild(BTreeNode* q1, int k);
};
#endif



