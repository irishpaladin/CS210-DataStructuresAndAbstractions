//main.h

#ifndef MAIN_H
#define MAIN_H
#include"indexType.h"
class Main
{
public:
	void displayTree();
	void displayIndexEntries();
	bool hasOccurence(string word);
	void insertOccurence(int page, int position);
	void insertNewNode(string word, int page, int position);
	void searchOption();

private:
	indexType index_type;
	//helper funtions
	void displayTreeHelper(indexNode* q, int level)const;
	void displayIndexEntriesHelper(indexNode* q)const;
	string getNextWord(string str, int start);
	bool searchHelper(string original, int word_count, int start);
};
#endif
