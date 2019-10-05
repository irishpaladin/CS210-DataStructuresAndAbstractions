#include <iostream>
#include <string> //for getline
#include <fstream>
#include <sstream> //for stringstream (splitting strings)
#include "InstructionClass.h"
using namespace std;


int main() {




	//initializing elements
	InstructionClass instuction_table;
	
	//input file needed
	//string filename;
	//cout << "Enter Filename: ";
	//getline(cin, filename);

	string filename = "halprogram.txt";

	//read file
	string line;
	ifstream myfile(filename);


	// stores the hal program in the InstructionClass
	string value = ""; //temp variable that stores an element in the line
	int element = 0; //counter on what element is being added [index,operation,operand]
	//temp variables needed
	int index = 0;
	string operation;
	string operand="";

	if (myfile.good())
	{
		while (getline(myfile, line))
		{
			stringstream ssIn(line);
			for (int i = 0; ssIn.good(); i++) {
				string s;
				ssIn >> s;
				if (i == 0) {
					index = stoi(s);
				}
				else if (i == 1) {
					operation = s;
				}
				else if(i>2){
					operand.append(" ");
					operand.append(s);
				}
				else {
					operand += s;
				}
			}
			
			//cout << "line: " << line << endl;
			/*cout << "index: " << index << endl;
			cout << "operation: " << operation << endl;
			cout << "operand: \"" << operand <<"\"" <<endl << endl;*/
			instuction_table.InsertUnsorted(index, operation, operand);
			operand = "";//reinitialize operand as an empty string
		}
		myfile.close();
		instuction_table.Display();

			
	}
	else cout << "Invalid input file!\n";

	return 0;
}