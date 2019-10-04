#include "InstructionClass.h"

InstructionClass::InstructionClass()
{
	pc = 0;
	
}

void InstructionClass::setInstructionElement(int index, string operation, char operand)
{
	instruction[index].operation = operation;
	instruction[index].operand = operand;
}

void InstructionClass::Display() const
{
	for (int i = 0; i < MAX_LENGTH; i++) {
		cout << "operand" << i << " : " << instruction[i].operand;
		cout << "  operation" << i << " : " << instruction[i].operation << endl;
	}
}
