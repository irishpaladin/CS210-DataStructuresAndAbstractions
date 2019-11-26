#include "Main.h"


int main() {
	string file = "C:\\Users\\Irish Paladin\\Google Drive\\2Year1Term\\CS210\\Lecture\\Homework7\\censusdata.txt";
	Main main(file);
	if (!main.isValid) {
		cout << "File Not Found" << endl;
		return EXIT_FAILURE;
	}
	else {
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
	main.closeFile();
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
	/*cout << endl;
	display();
	cout << endl;*/


	while (getline(IOFile, line)) {
		istringstream iss(line);
		iss >> key;
		
		tree.Insert(key, characterCtr);
		characterCtr = characterCtr + line.length() + 1;
		/*cout << endl;
		display();
		cout << endl;*/
	}
	
}

void Main::display(int mode)
{
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
	if (IOFile.good())
		cout << "good";
	else
		cout << "bad";
	int offset;
	string line;

	IOFile.clear();
	IOFile.seekg(12170);
	getline(IOFile, line);
	cout << "offset: " << 12170 << " -> " << line << endl;
	IOFile.clear();
	IOFile.seekg(12275);
	getline(IOFile, line);
	cout << "offset: " << 12275 << " -> " << line << endl;


	cout << "Enter Offset: ";
	cin >> offset;
	IOFile.clear();
	IOFile.seekg(offset);
	getline(IOFile, line);
	cout << "offset: " << offset << " -> " << line << endl;

	cout << "Enter Offset: ";
	cin >> offset;
	IOFile.clear();
	IOFile.seekg(offset);
	getline(IOFile, line);
	cout << "offset: " << offset << " -> " << line<<endl;
}

void Main::closeFile()
{
	IOFile.close();
}
