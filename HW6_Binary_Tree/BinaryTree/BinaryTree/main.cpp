//main.cpp

#include<iostream>
#include"main.h"
#include<fstream>
#include<string>
#include<cstdio>	//printf
using namespace std;

int main() {
	Main main;
	//indexType index_type;
	/*string str[] = { "a","b","c","d","e","f","g","h","i","j" };
	
	for (int i = 0; i < 10; i++) {
		cout << "Display " << i << endl;
		indexEntry index;
		index.word = str[i];
		index_type.Insert(index);
		index_type.resetP();
		main.displayTree(index_type.getP());
		cout << endl;
	}*/

	string filename = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework6\\files\\";

	for (int page = 1; page <= 2; page++) {
		
		ifstream file(filename + to_string(page));
		if (file.good()) {
			cout << "file" << page << " is good" << endl;
		}
		else {
			cout << "file" << page << " is not good" << endl;
		}
		string word;
		int position = 0;
		while (file >> word) {
			position++;
			//cout << word <<" >> ";
			//transform the word read
			//removes the punctuation
			//change the characters of the word to a lower characters
			for (int i = 0, len = word.size(); i < len; i++)
			{
				if (ispunct(word[i]))
				{
					word.erase(i--, 1);	//removes the punctuation
					len = word.size();
				}
				word[i]=tolower(word[i]); //changed the string to lower case characters
			}
			//cout << "." << word << "."<<endl;

			//check for the occurrence of the word
			//inserts Occurence
			if (main.hasOccurence(word)) {
				main.insertOccurence(page, position);
			}
			//create a new AVLNode
			else {
				main.insertNewNode(word, page, position);
			}
			
			
		}
		file.close();	
	}//end of forloop

	
	//main.displayTree();
	main.displayIndexEntries();
	

	return 0;
}

void Main::displayTree()

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
	index_type.resetP();
	if (index_type.getP() == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		displayTreeHelper(index_type.getP(), 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Main::displayTreeHelper(indexNode* p, int level) const

	// Recursive helper for showStructure. 
	// Outputs the subtree whose root node is pointed to by p. 
	// Parameter level is the level of this node within the tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		displayTreeHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t\t";
		cout << " " << p->entry.word;   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		displayTreeHelper(p->left, level + 1);          // Output left subtree
	}
}

void Main::displayIndexEntries()

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
	index_type.resetP();
	if (index_type.getP() == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		displayIndexEntriesHelper(index_type.getP());
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Main::displayIndexEntriesHelper(indexNode* p) const
// Inorder traversal implementation
// Recursive helper for displayIndexEntries. 
// Outputs the subtree whose root node is pointed to by p. 
{
	if (p != 0)
	{
		displayIndexEntriesHelper(p->left);         // Output right subtree
		
		//display occurences
		printf("%-16s", p->entry.word.c_str());
		//cout << p->entry.word << "\t\t";   // Output word
		p->entry.occurrences.ResetP();
		p->entry.occurrences.Iterate();
		while (p->entry.occurrences.IsPSet()) {
			string occurrence = "(";
			occurrence += to_string(p->entry.occurrences.Read().page) + ",";
			occurrence += to_string(p->entry.occurrences.Read().position)+")";
			printf("%-7s", occurrence.c_str());
			p->entry.occurrences.Iterate();
		}
		cout << endl;

		displayIndexEntriesHelper(p->right);          // Output left subtree
	}
}

bool Main::hasOccurence(string word)
{
	//returns true if there's occurrence of the word
	//sets p
	index_type.resetP();
	index_type.Find(word,index_type.getP());
	return index_type.IsPSet();
}

void Main::insertOccurence(int page, int position)
{
	//inserts occurence
	index_type.getP()->entry.occurrences.InsertUnsorted({ page,position });
}

void Main::insertNewNode(string word, int page, int position)
{
	indexEntry entry;
	entry.word = word;
	entry.occurrences.InsertUnsorted({ page,position });
	index_type.Insert(entry);
}
