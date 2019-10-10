#include "InstructionClass.h"
#include <cstring>
char null = '\0'; //initial values of operands are pointed in here

InstructionClass::InstructionClass()
{
	//constructor of class
	//initialize values
	length = 0;
	pc = 0;
	for (int i = 0; i < I_MAX_LENGTH; i++) {
		instruction[i].operation = "";
		instruction[i].operand = &null;
	}

}

InstructionClass::~InstructionClass()
{
	//class destructor
	//deletes the allocated values
	for (int i = 0; i < I_MAX_LENGTH; i++) {
		if(instruction[i].operand!=&null)delete instruction[i].operand;
	}
}

void InstructionClass::ResetP() {
	// sets p
	pc = -1;
	return;
}

//not too sure
void InstructionClass::Iterate() {
	// sets p to point to the next element in the list
	// always call ResetP prior to the initial call to Iterate
	// always call IsPSet after each call to Iterate
	pc++;
	return;
}


bool InstructionClass::IsPSet()const {
	// checks whether p points to an element in the list
	if (pc < 0 || pc > length - 1)
		return false;
	else return true;
}

int InstructionClass::GetP()const {
	// returns the current value of p
	return pc;
}

void InstructionClass::SetP(int q) {
	// always call IsPSet after each call to SetP
	// sets p
	pc = q;
	return;
}
Instruction InstructionClass::Read() const {
	// returns the operand pointed to by pc
	// pc must be set prior to calling Read
	// always call IsPSet prior to calling Read
	return instruction[pc];
}

int InstructionClass::Length()const {
	// returns the number of elements in the list
	return length;
}

bool InstructionClass::IsEmpty()const {
	// checks whether the list is empty
	if (length == 0)
		return true;
	else return false;
}

bool InstructionClass::IsFull()const {
	// checks whether the list is full
	if (length == I_MAX_LENGTH)
		return true;
	else return false;
}


void InstructionClass::InsertUnsorted(int index, string operation1, string operand1)
{
	// inserts a new element in the list
	// always call IsFull prior to calling InsertUnsorted
	// sets the operation and operand of instruction in index 'index'
	instruction[index].operation = operation1; 

	if (operand1.length() != 0) {
		int size = operand1.length() + 1; //number of characters in string +1 for '\0'
		instruction[index].operand = new char[size]; //allocating memory for the pointer
		strcpy(instruction[index].operand, operand1.c_str()); //copy the operand1 to the memory of instruction[index]
	}
	length++;
	return;
}

