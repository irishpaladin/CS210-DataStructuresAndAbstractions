#ifndef INSTRUCTIONCLASS_H
#define INSTRUCTIONCLASS_H

#include <iostream>

using namespace std;

const int I_MAX_LENGTH = 100;


struct Instruction;
struct Instruction {
	string operation;
	char* operand;
};

class InstructionClass
{
public:
	InstructionClass();
	~InstructionClass();
	//void setInstructionElement(int index, string operation1, string operand1);
	void ResetP();
	void Iterate();
	bool IsPSet()const;
	int GetP()const;
	void SetP(int q);
	Instruction Read()const;
	//void Write(string s, int x);
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void InsertUnsorted(int index, string operation1, string operand1);

private:
	int pc; //program counter
	int length;
	Instruction instruction[I_MAX_LENGTH];
	
};
#endif // !INSTRUCTIONCLASS_H



