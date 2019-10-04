#include "InstructionClass.h"
char null = '\0'; //initial values of operands are pointed in here

InstructionClass::InstructionClass()
{
	//constructor of class
	//initialize values
	pc = 0;
	for (int i = 0; i < MAX_LENGTH; i++) {
		instruction[i].operation = "";
		instruction[i].operand = &null;
	}

}

InstructionClass::~InstructionClass()
{
	//class destructor
	//deletes the allocated values
	for (int i = 0; i < MAX_LENGTH; i++) {
		if(instruction[i].operand!=&null)delete instruction[i].operand;
	}
}


void InstructionClass::setInstructionElement(int index, string operation1, string operand1)
{
	//sets the operation and operand of instruction in index 'index'
	instruction[index].operation = operation1; 

	if (operand1.length() != 0) {
		int size = operand1.length() + 1; //number of characters in string +1 for '\0'
		instruction[index].operand = new char[size]; //allocating memory for the pointer
		strcpy_s(instruction[index].operand, sizeof(char) * size, &operand1[0]); //copy the operand1 to the memory of instruction[index]
	}
	
	return;
}

void InstructionClass::Display() const
{
	cout << endl << endl;
	for (int i = 0; i < 23; i++) {
		cout << i << " : " << instruction[i].operation
			<< " : ";
		string s = instruction[i].operand;
		cout <<"\'"<< s<<"\'" << endl << endl;
	}
}
