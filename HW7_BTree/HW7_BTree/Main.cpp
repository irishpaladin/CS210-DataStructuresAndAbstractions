

#include "BTree.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

int main() {
	BTree tree;
	size_t eofMarker;
	size_t marker;
	size_t characterCtr = 0;
	string line;
	fstream inOutFile;
	int key;

	// This program modifies censusdata.txt. So, after you run it,
	// you will have to restore censusdata.txt.
	string file = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework7\\";
	inOutFile.open(file + "censusdata.txt", fstream::ate | fstream::in | fstream::out);

	if (!inOutFile)
	{
		cout << "File open error" << endl;
		return false;
	}

	inOutFile.seekg(0, fstream::beg); //reposition the inputstream marker to 0 distance from beg //marker that reads the file

	//get the first line in the file
	getline(inOutFile, line);
	istringstream iss1(line);
	iss1 >> key;
	tree.InsertRoot(key, 0); //insert first value
	//marker = inOutFile.tellg();//initialize marker for the next value to add


	while (getline(inOutFile, line)) {
		characterCtr = characterCtr + line.length() + 1;

		istringstream iss(line);
		iss >> key;
		tree.Insert(key, characterCtr);

		inOutFile.seekg(characterCtr);

	}

	return 0;
}

void displayOne(BTree tree) {
	tree.ResetP();
}
