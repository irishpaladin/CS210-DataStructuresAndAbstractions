#ifndef INSTRUCTIONCLASS_H
#define INSTUCTIONCLASS_H

#include <iostream>
using namespace std;

struct Instruction;
struct Instruction {
	string operation;
	char operand;
};

class InstructionClass
{
private:
	Instruction instruction[100];
	int pc;//program counter

public:
	InstructionClass();
};
#endif // !INSTRUCTIONCLASS_H



