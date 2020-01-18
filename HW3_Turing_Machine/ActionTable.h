//ActionTable.h

#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H
#include <iostream>
using namespace std;

struct Action;
struct Action {
	int curr_state;
	char sym_read;
	int next_state;
	char sym_write;
	char direction;
};

class ActionTable {
private:
	Action *actiontable;
	int num_command;
	int curr_action_index;
	int at_index;
public:
	ActionTable(int x);
	void SetValues(string s);
	void FindAction(int curr_state, char sym_read);
	int GetNextState()const;
	char GetSymbolWrite()const;
	char GetDirection()const;
	void DeleteActionTable();
};



#endif
