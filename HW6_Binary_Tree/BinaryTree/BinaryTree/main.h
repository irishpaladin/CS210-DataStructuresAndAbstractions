//main.h

#ifndef MAIN_H
#define MAIN_H
#include"indexType.h"

struct Phrase {
	string word;
	Phrase* next;
};

class Main
{
public:
	Main();
	void displayTree();
	void displayIndexEntries();
	bool hasOccurence(string word);
	void insertOccurence(int page, int position);
	void insertNewNode(string word, int page, int position);
	void searchOption();
	
	//Linkedlist methods
	/*void ResetP();
	void Iterate();
	bool IsPSet()const;
	Phrase* GetP()const;
	void SetP(Phrase* q);
	string Read()const;
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertTail(string x);
	bool Find(DataType x);
	void DeleteHead();
	void Delete();
	void DeleteTail();
	void Clear();*/

private:
	indexType index_type;
	//helper funtions
	void displayTreeHelper(indexNode* q, int level)const;
	void displayIndexEntriesHelper(indexNode* q)const;
	string getNextWord(string str, int start);
	bool searchHelper(string original, int word_count, int start, int page, int position);
	string searchHelper2(string original, int word_count, int start, int page, int position);
	string searchHelper3(string original, int word_count, int start, int page, int position);
	void displayResultNotFound(string str);
	int occurrenceCount(string word);
	//linkedlistPrivate variables/methods
	Phrase* p;
	Phrase* head;
};
#endif
