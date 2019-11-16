//main.cpp

#include<iostream>
#include"main.h"
using namespace std;

int main() {
	Main main;
	indexType index_type;
	string str[] = { "a","b","c","d","e","f","g","h","i","j" };
	
	for (int i = 0; i < 10; i++) {
		cout << "Display " << i << endl;
		indexEntry index;
		index.word = str[i];
		index_type.Insert(index);
		index_type.resetP();
		main.displayTree(index_type.getP());
		cout << endl;
	}

	/*cout << "Display1:" << endl;
	index_type.resetP();
	indexNode* root = index_type.getP();
	if (root == NULL) cout << "root is null\n";
	if (root->right == NULL)cout << "root right is null\n";
	if (root->left == NULL) cout << "root left is null\n";*/

	//cout << "Display2:" << endl;
	//index_type.resetP();
	//main.displayNode(index_type.getP());
	//main.InOrder(index_type.getP());

	return 0;
}

void Main::displayTree(indexNode* q) const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
	if (q == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		displayHelper(q, 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Main::displayHelper(indexNode* p,
	int level) const

	// Recursive helper for showStructure. 
	// Outputs the subtree whose root node is pointed to by p. 
	// Parameter level is the level of this node within the tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		displayHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->entry.word;   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		displayHelper(p->left, level + 1);          // Output left subtree
	}
}