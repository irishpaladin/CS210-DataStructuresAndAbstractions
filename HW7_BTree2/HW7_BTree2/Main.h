#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include "BTree.h"

using namespace std;

//modes for displaying
const int MODE_DATAONLY = 1;
const int MODE_DATAINFO = 2;
const int MODE_FINDDATA = 3;

class Main {
private:
	BTree tree;
	std::fstream IOFile;
public:
	bool isValid; //true of the file is created successfully
	Main(string file);
	void insertData();
	void display(int mode);
	void displayDataOnly(BTreeNode* q);
	void displayDataInfo(BTreeNode* q);
	void displayFindData();
	void closeFile();

};

#endif // !MAIN_H



