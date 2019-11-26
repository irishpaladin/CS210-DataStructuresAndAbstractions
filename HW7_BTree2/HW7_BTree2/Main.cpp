#include "Main.h"


int main() {
	string file = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework7\\censusdata.txt";
	Main main(file);
	if (!main.isValid) {
		cout << "File Not Found" << endl;
		return EXIT_FAILURE;
	}
	else {
		cout << "kinda works";
	}
	return 0;
}

Main::Main(string file)
{
	IOFile.open(file, fstream::ate | fstream::in | fstream::out);
	if (!IOFile)
		isValid = false;
	else {
		insertData();
		isValid = true;
	}
		
}

void Main::insertData()
{
	size_t characterCtr = 0;
	string line;
	int key;

	IOFile.seekg(0, fstream::beg); //reposition the inputstream marker to 0 distance from beg //marker that reads the file

	//get the first line in the file
	getline(IOFile, line);
	istringstream iss1(line);
	iss1 >> key;
	tree.InsertRoot(key, 0); //insert first value
	characterCtr = characterCtr + line.length() + 1;
	cout << endl;
	display();
	cout << endl;


	while (getline(IOFile, line)) {
		istringstream iss(line);
		iss >> key;
		
		tree.Insert(key, characterCtr);
		characterCtr = characterCtr + line.length() + 1;
		cout << endl;
		display();
		cout << endl;
	}
	
}

void Main::display()
{
	if (tree.IsEmpty())
		cout << "Tree is Empty" << endl;
	else {
		tree.ResetP();
		display(tree.GetP());
	}
}

void Main::display(BTreeNode* q)
{
	for (int i = 0; i < q->n; i++) {
		if (q->leaf) {
			cout << "(" << q->page[i].value << ", " << q->page[i].offset << ")";
			if (i == q->n - 1)
				cout << " | ";
		}
		else {
			display(q->page[i].next);
		}
	}
}

void Main::closeFile()
{
	IOFile.close();
}
