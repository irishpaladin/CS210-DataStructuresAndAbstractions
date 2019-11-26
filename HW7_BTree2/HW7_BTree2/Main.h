#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include "BTree.h"

using namespace std;

class Main {
private:
	BTree tree;
	std::fstream IOFile;
public:
	bool isValid;
	Main(string file);
	void insertData();
	void display();
	void display(BTreeNode* q);
	void closeFile();

};

#endif // !MAIN_H



