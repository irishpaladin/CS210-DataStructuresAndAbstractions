#include <iostream>
#include <string> //for getline
#include <fstream> //for reading file input
#include <sstream> //for stringstream (splitting strings)
#include <cstdlib> //atoi
#include "InstructionClass.h"
#include "SymbolTable.h"
#include "StackClass.h"

using namespace std;

void ErrorNeedToTerminate(string error_type, string error);
bool isValidVariable(string var);

int main() {

	//initializing elements
	InstructionClass instruction_table;
	SymbolTable symbol_table;
	StackClass stack;
	
	//input file needed
	string filename;
	cout << "Enter Filename: ";
	getline(cin, filename);

	//reading file
	string line; //temp variable that stores each line in the file
	ifstream myfile(filename.c_str());

	// storing  the hal program txt in the InstructionClass
	//temp variables needed for adding into the instuction class
	int index = 0; //index of the instruction
	string operation; 
	string operand="";

	if (myfile.good())
	{
		while (getline(myfile, line))
		{
			stringstream ssIn(line); // separates the string via spaces
			for (int i = 0; ssIn.good(); i++) {
				string s; //temp variable for the "word"
				ssIn >> s;
				if (i == 0) { //storing index
					index = atoi(s.c_str());
					if (index < 0 || index >= 100) {
						ErrorNeedToTerminate("invalid", "index");
					}
				}
				else if (i == 1) { //storing operation
					operation = s;
				}
				else if(i>2){ //storing operand
					operand.append(" ");
					operand.append(s);
				}
				else {
					operand += s;
				}
			}
			//will terminate the program if given hal program has 100+ instruction
			if (!instruction_table.IsFull())
				instruction_table.InsertUnsorted(index, operation, operand);
			else {
				ErrorNeedToTerminate("toomuch", "instruction");
			}
			operand = "";//reinitialize operand as an empty string
		}
		myfile.close(); //done reading file

		//interpreting HAL program
		//get the initial instruction
		Instruction curr_instruction; //instruction that will be used
		int status = -1;
		int temp_val1 = 0;
		int temp_val2 = 0;
		instruction_table.ResetP();		

		do{
			//storing instruction that will be used
			instruction_table.Iterate();
			if (instruction_table.IsPSet()) {
				curr_instruction = instruction_table.Read();
				operation = curr_instruction.operation;
			}
			else {
				operation = "invalid";
			}

			//displays the index of the instruction that will be used
			cout << " " << instruction_table.GetP();

			//do the operation
			if (operation == "declare") {
				operand = curr_instruction.operand;
				if (!isValidVariable(operand))ErrorNeedToTerminate("invalid", "variable");
				if (!symbol_table.IsFull())
					symbol_table.InsertSorted(operand, 0);
				else {
					ErrorNeedToTerminate("toomuch", "variables");
				}
			}
			else if (operation == "read") {
				
				cout << " Enter Value: ";
				cin >> temp_val1;
				if (!stack.IsFull())
					stack.Push(temp_val1);
				else
					ErrorNeedToTerminate("toomuch", "value in stack");

			}
			else if (operation == "push") {
				operand = curr_instruction.operand;
				temp_val1 = atoi(operand.c_str());
				if (!stack.IsFull())
					stack.Push(temp_val1);
				else
					ErrorNeedToTerminate("toomuch", "value in stack");
			}
			else if (operation == "get") {
				operand = curr_instruction.operand;
				if (!symbol_table.IsEmpty()&& symbol_table.FindSorted(operand)) {
					if (!stack.IsFull())
						stack.Push(symbol_table.Read());
					else
						ErrorNeedToTerminate("toomuch", "value in stack");
				}
				else
					ErrorNeedToTerminate("invalidhal", "");
			}
			else if (operation == "add") {
				if (!stack.IsEmpty()) 
					temp_val1 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if(!stack.IsEmpty())
					temp_val2 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if(!stack.IsFull())
					stack.Push(temp_val1 + temp_val2);
				else ErrorNeedToTerminate("toomuch", "value in stack");
			}
			else if (operation == "multiply") {
				
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				else ErrorNeedToTerminate("invalid", "");
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				else ErrorNeedToTerminate("invalid", "");
				if (!stack.IsFull())
					stack.Push(temp_val1 * temp_val2);
				else ErrorNeedToTerminate("toomuch", "value in stack");
			}
			else if (operation == "subtract") {
				
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if (!stack.IsFull())
					stack.Push(temp_val1 - temp_val2);
				else ErrorNeedToTerminate("toomuch", "value in stack");
			}
			else if (operation == "divide") {
			
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if (!stack.IsFull())
					stack.Push(temp_val1 / temp_val2);
				else ErrorNeedToTerminate("toomuch", "value in stack");
			}
			else if (operation == "set") {
				operand = curr_instruction.operand;
			
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if (!symbol_table.IsEmpty() && symbol_table.FindSorted(operand) && symbol_table.IsPSet()) {
					symbol_table.Write(temp_val1);
				}
				else ErrorNeedToTerminate("invalidhal", "");
			}
			else if (operation == "write") {
				if (!stack.IsEmpty())
					cout<< stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
			}
			else if (operation == "writestring") {
				cout << curr_instruction.operand;
			}
			else if (operation == "writenl") {
				cout << endl;
			}
			else if (operation == "compare") {
				
				if (!stack.IsEmpty())
					temp_val1 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				if (!stack.IsEmpty())
					temp_val2 = stack.Pop();
				else ErrorNeedToTerminate("invalidhal", "");
				status = temp_val1 == temp_val2 ? 1 : 0;
			}
			else if (operation == "jumpequal") {
				operand = curr_instruction.operand;
				if (status == 1)
					instruction_table.SetP(atoi(operand.c_str())-1);//-1 to compensate for the iterate at the end
				status = -1;
			}
			else if (operation == "jump") {
				operand = curr_instruction.operand;
				instruction_table.SetP(atoi(operand.c_str()) - 1);//-1 to compensate for the iterate at the end
			}
			else if (operation == "end") {
			// dont do anything. leaving it to while condition
			}
			else {
			ErrorNeedToTerminate("invalidhal", "");
			}
	
		}
		while (operation != "end");
		
	}
	else cout << "Invalid input file!\n";


	return 0;
}

void ErrorNeedToTerminate(string error_type, string error) {
	if (error_type == "toomuch") {
		cout << "\nHAL program has too many " << error << ". I can't take it!\n";
	}
	else if (error_type == "invalidhal") {
		cout << "\nSomething is wrong with your hal program not me!\n";
	}
	else if (error_type == "invalid") {
		cout << "\n HAL program has invalid " << error << ". I don't accept such thing.\n";
	}
	exit(1);
}
bool isValidVariable(string var) {
	if (var == "") return false;
	if (!isalpha(var[0])) return false;
	for (int i = 1; i < var.length(); i++) {
		if (!isalpha(var[i]) && !isdigit(var[i]))return false;
	}
	return true;
}