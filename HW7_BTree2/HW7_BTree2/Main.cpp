#include "Main.h"


int main() {
	string file = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework7\\censusdata.txt";
	//instantiating class and reads in the data
	Main main(file);
	if (!main.isValid) {
		cout << "File Not Found" << endl;
		return EXIT_FAILURE;
	}
	else {
		//displays the result
		cout<<"Key and Offset" << endl;
		main.display(MODE_DATAONLY);
		cout << endl;
		cout << endl;
		cout << "Data with contents" << endl;
		main.display(MODE_DATAINFO);
		cout << endl;
		cout << endl;
		cout << "(q->quit)Find Data" << endl;
		main.display(MODE_FINDDATA);
	}
	main.closeFile(); //closes file
	return 0;
}

Main::Main(string file)
{
	//constructor
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
	// variable counters
	size_t characterCtr = 0; // reads offset
	string line; // stores the whole line
	int key; // stores the key

	IOFile.seekg(0, fstream::beg); //reposition the inputstream marker to 0 distance from beg //marker that reads the file

	// reads and stores data
	while (getline(IOFile, line)) {
		cout << IOFile.tellg()<<endl;
		istringstream iss(line);
		iss >> key;
		if(tree.IsEmpty())
			tree.InsertRoot(key, 0); //insert first value
		else
			tree.Insert(key, characterCtr);
		characterCtr = characterCtr + line.length() + 1;
	}
	
}

void Main::display(int mode)
{
	//method that calls recurrsive functions of different displays
	if (tree.IsEmpty())
		cout << "Tree is Empty" << endl;
	else {
		tree.ResetP();
		switch (mode) {
		case MODE_DATAONLY:
			displayDataOnly(tree.GetP());
			break;
		case MODE_DATAINFO:
			displayDataInfo(tree.GetP());
			break;
		case MODE_FINDDATA:
			displayFindData();
			break;
		default:
			cout << "ERROR" << endl;
		}

	}
}

void Main::displayDataOnly(BTreeNode* q)
{
	// displays the key and offset only
	for (int i = 0; i < q->n; i++) {
		if (q->leaf) {
			cout << "(" << q->page[i].value << ", " << q->page[i].offset << ") ";
			if (i == q->n - 1)
				cout << "| ";
		}
		else {
			displayDataOnly(q->page[i].next);
		}
	}
}

void Main::displayDataInfo(BTreeNode* q)
{
	// displays the key , offset and the line corresponding the offset
	for (int i = 0; i < q->n; i++) {
		if (q->leaf) {
			string line;
			IOFile.clear();
			IOFile.seekg(q->page[i].offset);
			getline(IOFile, line);
			cout << "(" << q->page[i].value << ", " << q->page[i].offset << ") ";
			cout << line << endl;
		}
		else {
			displayDataInfo(q->page[i].next);
		}
	}
}

void Main::displayFindData()
{
	// displays the data in the file according to the given key
	int find_keys[] = { 1,141, 262, 415, 539, 621, 797, 854, 998 };
	for (int key : find_keys) {
		cout << "Person with "<< key<<" key: " << endl;
		if (tree.IsEmpty()) {
			cout << "Tree is empty" << endl;
			break;
		}
		tree.Find(key);
		if (tree.IsISet() && tree.IsPSet()) {
			IOFile.clear();
			IOFile.seekg(tree.Read().offset);
			string line;
			getline(IOFile, line);
			cout << line << endl;
		}
		else {
			cout << "Data not Found" << endl;
		}
		cout << endl;
	}
	
	

	
}

void Main::closeFile()
{
	//closes the file
	IOFile.close();
}
