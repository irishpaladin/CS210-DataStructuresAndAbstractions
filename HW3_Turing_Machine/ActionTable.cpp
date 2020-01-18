//ActionTable.cpp

#include "ActionTable.h"


ActionTable::ActionTable(int x)
{
	//constructor of the class
	curr_action_index = -1;
	at_index = 0;
    num_command = x;
	actiontable = new Action[x];
	
}

void ActionTable::SetValues(string line)
{
	//stores the action commands
	actiontable[at_index].curr_state = line[0] - '0';
	actiontable[at_index].sym_read = line[1];
	actiontable[at_index].next_state = line[2] - '0';					
	actiontable[at_index].sym_write = line[3];				
	actiontable[at_index].direction = line[4];
	at_index++;
	return;
}

void ActionTable::FindAction(int curr_state, char sym_read)
{
	//sets curr_action_index
	for (int i = 0; i < num_command; i++) {
		if (actiontable[i].curr_state == curr_state && actiontable[i].sym_read == sym_read) {
			curr_action_index = i;
		}
	}
}

int ActionTable::GetNextState() const
{
	//returns the next state value based on the curr_action_index
	return actiontable[curr_action_index].next_state;
}

char ActionTable::GetSymbolWrite() const
{
	//returns the symbol to write based on curr_action_index
	return actiontable[curr_action_index].sym_write;
}

char ActionTable::GetDirection() const
{
	//returns the direction of action based on curr_action_index
	return actiontable[curr_action_index].direction;
}

void ActionTable::DeleteActionTable()
{
	//delete actiontable that was made using new keyword
	delete[] actiontable;
}


