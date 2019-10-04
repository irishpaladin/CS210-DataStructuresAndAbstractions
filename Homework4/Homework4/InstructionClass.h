#ifndef INSTRUCTIONCLASS_H
#define INSTUCTIONCLASS_H

#include <iostream>
using namespace std;

const int MAX_LENGTH = 100;

struct Instruction;
struct Instruction {
	string operation;
	char operand;
};

class InstructionClass
{
private:
	Instruction instruction[MAX_LENGTH];
	int pc;//program counter

public:
	InstructionClass();
	void setInstructionElement(int index, string operation, char operand);

	void Display() const;
};
#endif // !INSTRUCTIONCLASS_H



