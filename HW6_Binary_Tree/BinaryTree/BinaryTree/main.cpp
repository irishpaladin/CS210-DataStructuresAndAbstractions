//main.cpp

#include<iostream>
#include"main.h"
#include<fstream>	//file i/o
#include<string>	//string manipulation
#include<cstdio>	//printf
#include<sstream>	//string stream in serch function
using namespace std;

int main() {
	Main main;

	//reading file
	string filename = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework6\\files\\";
	//and till page 14
	for (int page = 1; page <= 20; page++) {
		ifstream file(filename + to_string(page));
		if (file.good()) {
			string word;	//temporary variable of a word read
			int position = 0;	//position of a word
			while (file >> word) {
				position++;
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
					word[i] = tolower(word[i]); //changed the string to lower case characters
				}
				//check for the occurrence of the word
				//inserts Occurence
				if (main.hasOccurence(word)) {
					main.insertOccurence(page, position);
				}
				//create a new AVLNode
				else {
					main.insertNewNode(word, page, position);
				}
			}//end of while
			file.close();
		}//end of if
		else {
			cout << "Error in opening " << filename << page << endl;
		}
	}//end of forloop

	
	//program
	string choice;
	do {
		cout << endl;
		cout << "  T   : Show tree structure" << endl;
		cout << "  I   : Show index with occurences" << endl;
		cout << "  S   : Search word/phrase" << endl;
		cout << "  Q   : Quit" << endl;
		cout << " Enter choice: ";
		getline(cin, choice);
		
		if (choice.length() > 1)
			cout << " !! You entered an invalid choice !! " << endl;
		else {
			switch (choice[0]) {
			case 'T':case 't':
				main.displayTree();
				break;
			case 'I':case'i':
				main.displayIndexEntries();
				break;
			case 'S':case's':
				main.searchOption();
				break;
			default:
				cout << " !! You entered an invalid choice !! " << endl;
				break;
			}
		}

	} while (choice[0] != 'q');
	

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
		for (j = 1; j < level; j++)    // Tab over to level
			cout<<"                ";
		string str = p->entry.word;
		if ((p->left != 0) &&           // add "connector" to the string
			(p->right != 0))
			str += "<";
		else if (p->right != 0)
			str += "/";
		else if (p->left != 0)
			str += "\\";
		printf("%-16s", str.c_str());	// display the string
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
	if (!index_type.getP()->entry.occurrences.IsFull())
		index_type.getP()->entry.occurrences.InsertUnsorted({ page,position });
	else {
		cout << " !! Adding word at [" << page << ", " << position << "] has failed !!\n";
	}
}

void Main::insertNewNode(string word, int page, int position)
{
	
	if (!index_type.IsFull()) {
		indexEntry entry;
		entry.word = word;
		entry.occurrences.InsertUnsorted({ page,position });
		index_type.Insert(entry);
	}
	else {
		cout << " !! Adding node '";
		printf("%10s' at [%2d,%2d]", word.c_str(),page,position);
		cout << " has failed. Memory is full !!" << endl;
	}
}

void Main::searchOption()
{
	string search; //temporary variable for
	do {
		cout << "\n(b for Back) ";
		cout << "Search: ";
		getline(cin, search);
		if (search != "") {//disregards empty inputs
			istringstream str_data(search); //I used this to avoid one or more space between words
			string word; //temp variable of a word in a string
			//counts the number of words in the string
			//remove extra spaces between words
			string new_search="";//string which has no extra spaces between words
			int word_count = 0; //temp variable
			while (str_data >> word) {
				word_count++;
				new_search += word + " ";
			}

			//search for the matches
			for (int i = 0; i < new_search.length() - 1; i++) {
				cout << getNextWord(new_search, i);

				i += getNextWord(new_search, i).length();
			}
		}

	} while (search != "b");
}

bool Main::searchHelper(string original, int word_count, int start)
{
	string word = getNextWord(original, start);
	if (word_count == 0)
		return true;
	else if ()
	else {
		return(searchHelper(original, word_count - 1, start + word.length()));
	}
}

string Main::getNextWord(string str, int start) {
	string ret_str = "";
	for (int i = start; i < str.length(); i++) {
		if (str[i] == ' ')
			return ret_str;
		else
			ret_str += str[i];
	}
}


