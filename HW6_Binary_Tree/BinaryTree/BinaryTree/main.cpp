//main.cpp

#include<iostream>
#include"main.h"
#include<fstream>	//file i/o
#include<string>	//string manipulation
#include<cstdio>	//printf
#include<sstream>	//string stream in serch function
using namespace std;

int main() {
	int page_number = 20;
	Main main;

	//reading file
	string filename = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework6\\files\\";
	//and till page 14
	for (int page = 1; page <= page_number; page++) {
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
					if (word[i] == '-')continue;
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
			case 'Q':case'q':
				break;
			default:
				cout << " !! You entered an invalid choice !! " << endl;
				break;
			}
		}

	} while (choice[0] != 'q');
	

	return 0;
}

Main::Main()
{
	p = NULL;
	head = NULL;
}

void Main::displayTree()

// Outputs the index without the occurrences in AVL tree format. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. 

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

void Main::displayTreeHelper(indexNode* p, int level) const

	// Recursive helper for displayTree. 
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

// Outputs the index, with the occurrences, in list format
// orientation using an inorder traversal.

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

void Main::displayIndexEntriesHelper(indexNode* p) const
// Inorder traversal implementation
// Recursive helper for displayIndexEntries. 
// Outputs the index in the subtree whose root node is pointed to by p. 
{
	if (p != 0)
	{
		displayIndexEntriesHelper(p->left);         // Output right subtree
		//display occurences
		printf("%-16s", p->entry.word.c_str());
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
	// inserts occurence
	// always call IsFull prior to calling InsertOccurence
	if (!index_type.getP()->entry.occurrences.IsFull())
		index_type.getP()->entry.occurrences.InsertUnsorted({ page,position });
	else {
		cout << " !! Adding word at [" << page << ", " << position << "] has failed !!\n";
	}
}

void Main::insertNewNode(string word, int page, int position)
{
	// inserts new node to the tree
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
	//look for occurence of a word or phrase
	//sets p
	string search; // variable for user input
	do {
		cout << "\n(b for Back) ";
		cout << "Search: ";
		getline(cin, search);
		if (search == "b")return;	// back
		if (search != "") {		// disregards empty inputs
			istringstream str_data(search); // I used this to avoid one or more space between words
			string word; // temp variable of a word in a string
			string new_search = "";//string which has no extra spaces between words
			int word_count = 0; // counter for number of word in the phrase

			// counts the number of words in the string
			// remove extra spaces between words
			while (str_data >> word) {
				word_count++;
				new_search += word + " ";
			}

			// search for the matches
			if (word_count == 1) {
				//search for 1 word
				if (hasOccurence(getNextWord(new_search, 0))) {
					cout << endl << search << "  ";
					index_type.getP()->entry.occurrences.ResetP();
					index_type.getP()->entry.occurrences.Iterate();
					while (index_type.getP()->entry.occurrences.IsPSet()) {
						cout << "(" << index_type.getP()->entry.occurrences.Read().page << ",";
						cout << index_type.getP()->entry.occurrences.Read().position << ")\t";
						index_type.getP()->entry.occurrences.Iterate();
					}
					cout << endl;
				}
				else {
					displayResultNotFound(search);
				}
			}
			else {
				//search for phrase
				string word = getNextWord(new_search, 0);
				//iterate through all occurences of the first word
				if (hasOccurence(word)) {
					bool found = false;	//true if phrase has one or more occurence
					bool displayed = false; //true if the phrase as been displayed
					index_type.getP()->entry.occurrences.ResetP();
					index_type.getP()->entry.occurrences.Iterate();
					while (index_type.getP()->entry.occurrences.IsPSet()) {
						int page = index_type.getP()->entry.occurrences.Read().page;
						int position = index_type.getP()->entry.occurrences.Read().position;
						string result = searchHelper(new_search, word_count - 1, word.length() + 1, page, position + 1);
						if (result!="  ") {
							if (!displayed) {
								cout << endl << search << "\t";
								displayed = true;
							}
							cout << "((" << page << "," << position << ")";
							cout << result<<"\t";
							found = true;
						}
						hasOccurence(word);//point the p to the 1st word in search
						index_type.getP()->entry.occurrences.Iterate();
					}//endl of while loop
					//found occurence of the word but not the phrase 
					if (!found)displayResultNotFound(search);
					else cout << endl;
				}
				else {
					displayResultNotFound(search);
				}
			}
		}

	} while (search != "b");
}

string Main::searchHelper(string original, int word_count, int start, int page, int position)
{
	// recursive function of searchOption
	// parameter original is the user entered phrase
	// parameter word_cound is the number of remaining word to iterate
	// parameter start: original[start] is the 1st char of the word that is looking for
	// parameter page& position is th epage and position the word supposed to be in
	// sets p
	
	if (word_count == 0) {
		//end of string
		return ")";
	}
	else {
		string word = getNextWord(original, start);
		if (hasOccurence(word)) {//set p
			indexNode* p = index_type.getP();
			p->entry.occurrences.ResetP();
			p->entry.occurrences.Iterate();
			while (p->entry.occurrences.IsPSet()) {
				int o_page = p->entry.occurrences.Read().page;
				int o_position = p->entry.occurrences.Read().position;
				//searchhelper
				if (o_page > page) {
					//occurence not found
					return "  ";
				}
				else if (o_page == page && o_position == position) {
					//return recursive call
					string returned = searchHelper(original, word_count - 1, start + word.length() + 1, page, position+1);
					//not found
					if (returned == "  ") {
						return "  ";
					}
					else
						return "(" + to_string(o_page) + "," + to_string(o_position) + ")" + returned;
				}
				else {
					p->entry.occurrences.Iterate();
				}
			}

			// found word but not occurrence
			return "  ";
		}
		else {
			// word not found
			return "  ";
		}
	}
}

string Main::getNextWord(string str, int start) {
	//returns string word from str[start] till single space
	if (start == str.length() - 1)
		return " ";
	string ret_str = "";
	for (int i = start; i < str.length(); i++) {
		if (str[i] == ' ')
			return ret_str;
		else
			ret_str += str[i];
	}
}

void Main::displayResultNotFound(string str) {
	cout << "\nThere are no results for \"" << str <<"\""<< endl;
	cout << "Check your spelling or try different keywords" << endl;
}
