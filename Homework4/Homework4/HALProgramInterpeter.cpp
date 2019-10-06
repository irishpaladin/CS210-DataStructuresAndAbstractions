#include <iostream>
#include <string> //for getline
#include <fstream>
#include <sstream> //for stringstream (splitting strings)
#include "InstructionClass.h"
#include "SymbolTable.h"
#include "StackClass.h"

using namespace std;


int main() {
	




	//initializing elements
	InstructionClass instruction_table;
	SymbolTable symbol_table;
	StackClass stack;
	
	//input file needed
	//string filename;
	//cout << "Enter Filename: ";
	//getline(cin, filename);

	string filename = "halprogram.txt";

	//read file
	string line;
	ifstream myfile(filename);


	// storing  the hal program txt in the InstructionClass
	//temp variables needed
	int index = 0;
	string operation;
	string operand="";

	if (myfile.good())
	{
		while (getline(myfile, line))
		{
			stringstream ssIn(line); // separates the string via spaces
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
			instruction_table.InsertUnsorted(index, operation, operand);
			operand = "";//reinitialize operand as an empty string
		}
		myfile.close();
		//done reading file

		instruction_table.Display();

		//solving problem
		

		//get the initial instruction
		Instruction curr_instruction = instruction_table.Read();
		operation = curr_instruction.operation;

		cout << "instruction index: " << instruction_table.GetP() << endl;

		while (operation != "end") {
			if (operation == "declare") {
				operand = curr_instruction.operand;
				symbol_table.InsertSorted(operand, 0);
			}
			else if (operation == "read") {
				int temp_val;
				cout << "Enter Value: ";
				cin >> temp_val;
				if (!stack.IsFull())
					stack.Push(temp_val);
			}
			else if (operation == "push") {
				operand = curr_instruction.operand;
				int temp_val = stoi(operand);
				if (!stack.IsFull())
					stack.Push(temp_val);
			}
			else if (operation == "get") {
				operand = curr_instruction.operand;
				if (!symbol_table.IsEmpty()&& symbol_table.FindSorted(operand)&& !stack.IsFull()) {
					stack.Push(symbol_table.Read());	
				}
			}
			else if (operation == "add") {
				int temp_val1, temp_val2;
				if (!stack.IsEmpty()) 
					temp_val1 = stack.Pop();
				if(!stack.IsEmpty())
					temp_val2 = stack.Pop();
				if(!stack.IsFull())
					stack.Push(temp_val1 + temp_val2);
			}
			else if (operation == "multiply") {
				int temp_val1, temp_val2;
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				if (!stack.IsFull())
					stack.Push(temp_val1 * temp_val2);
			}
			else if (operation == "subtract") {
				int temp_val1, temp_val2;
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				if (!stack.IsFull())
					stack.Push(temp_val1 - temp_val2);
			}
			else if (operation == "divide") {
				int temp_val1, temp_val2;
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				if (!stack.IsFull())
					stack.Push(temp_val1 / temp_val2);
			}
			else if (operation == "set") {
				operand = curr_instruction.operand;
				int temp_val;
				 if (!stack.IsEmpty())
					temp_val = stack.Pop();
				 if (!symbol_table.IsEmpty() && symbol_table.FindSorted(operand)&&symbol_table.IsPSet()) {
					 symbol_table.Write(temp_val);
				 }
			}
			else if (operation == "write") {
				if (!stack.IsEmpty())
					cout<< stack.Pop();
			}
			else if (operation == "writestring") {
				cout << curr_instruction.operand;
			}
			else if (operation == "writenl") {
				cout << endl;
			}
			else if (operation == "compare") {
				int temp_val1, temp_val2;
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();

			}


			instruction_table.Iterate();
			curr_instruction = instruction_table.Read();
			operation = curr_instruction.operation;
			cout << "instruction index: " << instruction_table.GetP() << endl;
		}
		

		symbol_table.Display();
		
	}
	else cout << "Invalid input file!\n";


	return 0;
}