//TuringMachine.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "Tape.h"
#include "ActionTable.h"
using namespace std;


int main() {
	
	//input file needed
	string filename;
	cout << "Enter Filename: ";
	getline(cin, filename);

	//to set the array of actions
	int num_commands;
	cout << "Enter Number of Commands (count has 6, subtract has 30): ";
	cin >> num_commands;

	//initalize the TuringMachine elements
	ActionTable actiontable(num_commands);
	int state_register = 'B';
	Tape tape;

	//variables used
	int p_position = 0; // placement of element p is pointing at
	Node* head = NULL; //pointing head of tape
	int counter = 0;//what part in the text 'myfile' is reading

	//read file
	string line;
	ifstream myfile(filename);

	if (myfile.good()) 
	{
		while (getline(myfile, line))
		{
			//removing comment
			line.erase(std::find(line.begin(), line.end(), '/'), line.end());
			//removing whitespaces
			line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
			
			switch (counter) {
			//reading state register
			case 0:
				state_register = stoi(line);
				counter++;
				break;
			//reading initial value of tapes
			case 1:
				for (int i = (int)line.size()-1; i >=0 ; i--) {
					if (!tape.IsFull()) {
						tape.InsertHead(line[i]);
					}
					else {
						cout << "Storage is Full... Unable to continue";
						exit(1);
					}					
				}
				head = tape.GetP();
				counter++;
				break;
			//reading actiontable
			case 2:
				if (line == "-1") {
					counter++;
				}
				else {
					actiontable.SetValues(line);
				}
				break;
			//sets initial p pointer
			case 3:
				p_position = stoi(line);
				break;
			default:
				cout << "default" << endl;
				break;
			}
			
		}
		myfile.close();

		//solving problem

		//first display
		tape.ResetP();
		if(!tape.IsEmpty())tape.SetP(head);
		while(tape.IsPSet()) {
			cout << tape.Read()<<" ";
			tape.IterateRight();
		}
		cout << endl;
		for (int i = 0; i < p_position - 1; i++) 
			cout << "  ";
		cout << "^" << endl;


		while (actiontable.GetDirection() != 'H') {
			//sets P
			tape.ResetP();
			for (int i = 0; i < p_position; i++) {
				tape.IterateRight();
				if (!tape.IsPSet()) {
					cout << "\n\nThere is a problem in the txt file.\n\n";
					exit(1);
				}
			}
			//find action to use
			if (tape.IsPSet()) actiontable.FindAction(state_register, tape.Read());
			else cout << "Something went wrong.";
			//set the nextstate
			state_register = actiontable.GetNextState();
			//change the symbol in tape
			tape.Write(actiontable.GetSymbolWrite());
			//set direction
			switch (actiontable.GetDirection()) {
			case 'R':
				tape.IterateRight();
				p_position++;
				break;
			case 'L':
				tape.IterateLeft();
				p_position--;
				break;
			case 'H':
			case '-':
			default:
				break;
			}

			//displays Tape
			if (!tape.IsEmpty())tape.SetP(head);
			while (tape.IsPSet()) {
				cout << tape.Read() << " ";
				tape.IterateRight();
			}
			cout << endl;
			for (int i = 0; i < p_position - 1; i++)
				cout << "  ";
			cout << "^" << endl;		
		}

		//delete the array that was made using 'new'
		actiontable.DeleteActionTable();

	}
	else cout << "Invalid input file!\n";
	

	return 0;
}