#include<iostream>
#include<string>
#include"ArrayList.h"
#include"LinkedList.h"
using namespace std;

DataType readInt(string descr); //getting user input
void LinkedListMenu();			//for LinkedList Menu
void ArrayListMenu();			//for ArrayList Menu
void DisplayEndl();				//displays 2 endl for formatting
string BoolStringValue(bool value); //displays ht estring value of given bool


int main()
{

	char choice;

	cout << "\n*** List Program ***" << endl;

	choice = 'z';

	while (choice != 'q')
	{
		cout << "\n\nLONG MENU AHEAD. PLEASE FULLSCREEN OR VERTICALLY INCREASE THE WINDOW\n";
		cout << "*******************************************************" << endl;
		cout << "1: ArrayList\n";
		cout << "2: LinkedList\n";
		cout << "q: Quit   (Quit the program)\n";
		cout << "*******************************************************" << endl << endl;
		cout << "\n   Please enter your choice here:";
		cin >> choice;

		switch (choice)
		{
		case '1':
			ArrayListMenu();
			break;

		case '2':
			LinkedListMenu();
			break;

		case 'q':
			break;

		default:
			cout << "\n Invalid choice. Please try again.\n";
			break;
		}
	}
	cout << "\n Bye\n";
	return 0;
}


void LinkedListMenu()
{
	char choice;
	DataType item;
	LinkedList linked_list;

	DisplayEndl();
	cout << "This program demonstrates the linked list. " << endl;

	linked_list.Create();
	DisplayEndl();
	cout << "Linked List has been created" << endl;
	linked_list.DisplayLinkedListValues("Initial Values");

	choice = 'z';

	while (choice != 'x')
	{
		DisplayEndl();
		cout << "*******************************************************" << endl;
		cout << "1: Insert       (Start of the list)\n";
		cout << "2: Insert       (End of the List)\n";
		cout << "3: Insert       (Sorted List)\n";
		cout << "4: Delete       (Delete a node with the given value)\n";
		cout << "5: Delete(head) (Delete the first node)\n";
		cout << "6: Delete(tail) (Delete the last node)\n";
		cout << "p: Print        (Display all list element)\n";
		cout << "x: Back         (Return to the Main Menu)\n\n";

		cout << "   *** Check Other Member Functions ***\n";
		cout << "a: ResetP    (sets p to to point to null)\n";
		cout << "b: Iterate   (p is pointed to the next value)\n";
		cout << "c: IsPSet    (outputs true if p is not pointing to nullptr)\n";
		cout << "d: GetP      (outputs the value of p)\n";
		cout << "e: Read      (outputs the value of element pointed by p)\n";
		cout << "f: Write     (writes new value into element pointed by p)\n";
		cout << "g: Length    (displays the length of the array)\n";
		cout << "h: IsEmpty   (displays true if length is 0)\n";
		cout << "i: IsFull    (displays true if length is 10\n";
		cout << "j: Find      (displays true if an item is found in the array)\n";
		cout << "k: Clear()	  (reinitialize the list)\n";
		cout << "*******************************************************" << endl << endl;

		cout << "   Please enter your choice here:";
		cin >> choice;

		switch (choice)
		{
			//Insert item at the start of LinkedList
		case '1':
			item = readInt("to insert(Start):");
			if (linked_list.IsFull()) {
				cout << "\n  Storage is Full. Please delete Nodes and try again." << endl;
			}
			else {
				linked_list.InsertHead(item);
			}
			break;

			//Insert item at the end of the LinkedList
		case '2':
			item = readInt("to insert(End):");
			if (linked_list.IsFull()) {
				cout << "\n  Storage is Full. Please delete Nodes and try again." << endl;
			}
			else {
				linked_list.InsertTail(item);
			}
			break;

			//insert item in Sorted Linkedlist
		case '3':
			item = readInt("to insert(Sorted):");
			if (linked_list.IsFull()) {
				cout << "\n  Storage is Full. Please delete Nodes and try again." << endl;
			}
			else {
				linked_list.InsertSorted(item);
			}
			break;

			//Delete item in LinkedList
		case '4':
			item = readInt("to delete:");
			if (linked_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				if (linked_list.Find(item) && linked_list.IsPSet()) {
					linked_list.Delete();
				}
				else {
					cout << "   No such element is found." << endl << endl;
				}
			}
			break;

			//Delete the head node
		case '5':
			if (linked_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}else {
				linked_list.DeleteHead();
			}
			break;

			//Delete the tail node
		case '6':
			if (linked_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				linked_list.DeleteTail();
			}
			break;


			//Prints all elements in the LinkedList
		case 'p':
			if (linked_list.IsEmpty()) {
				cout << "   There is no item in the list yet." << endl;
			}
			else {
				cout << "   The content of the current list is: " << endl;
				linked_list.ResetP();
				for (int i = 0; i < linked_list.Length(); i++) {
					linked_list.Iterate();
					if (linked_list.IsPSet())
						cout << "   " << linked_list.Read() << endl;
				}
			}
			break;


			//Checking of Member functions
			//ResetP Member Function
		case 'a':
			linked_list.DisplayLinkedListValues("Before ResetP");
			linked_list.ResetP();
			linked_list.DisplayLinkedListValues("After ResetP");
			DisplayEndl();
			break;

			//Iterate Member Function
		case 'b':
			linked_list.DisplayLinkedListValues("Before Iterate");
			linked_list.Iterate();
			linked_list.DisplayLinkedListValues("After Iterate");
			DisplayEndl();
			break;

			//IsPSet Member Function
		case 'c':
			linked_list.DisplayLinkedListValues("Values");
			cout << "   IsPSet: " << BoolStringValue(linked_list.IsPSet());
			DisplayEndl();
			break;

			//GetP Member Function
		case 'd':
			cout << "\n   Value of P is " << linked_list.GetP();
			DisplayEndl();
			break;


			//Read Member Function
		case 'e':
			if (linked_list.IsPSet()) {
				cout << "\n   The value of element pointed by p is " << linked_list.Read();
			}
			else {
				cout << "\n   Invalid value of P" << endl;
			}
			linked_list.DisplayLinkedListValues("Values");
			DisplayEndl();
			break;

			//Write Member Function 
		case 'f':
			if (linked_list.IsPSet()) {
				linked_list.DisplayLinkedListValues("Before Write");
				cout << "\n   Enter new value pointed by p: ";
				int x;
				cin >> x;
				linked_list.Write(x);
				linked_list.DisplayLinkedListValues("After Write");
			}
			else {
				cout << "\n   P is invalid" << endl;
			}
			DisplayEndl();
			break;

			//Length Member Function
		case 'g':
			cout << "\n   Value of Length is " << linked_list.Length();
			DisplayEndl();
			break;

			//IsEmpty Member Function
		case 'h':
			linked_list.DisplayLinkedListValues("Values");
			cout << "\n   IsEmpty: " << BoolStringValue(linked_list.IsEmpty());
			DisplayEndl();
			break;

			//IsFull Member Function
		case 'i':
			linked_list.DisplayLinkedListValues("Values");
			cout << "\n   IsFull: " << BoolStringValue(linked_list.IsFull());
			DisplayEndl();
			break;

			//Find Member Function
		case 'j':
			if (linked_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				cout << "\n   Enter item to find: ";
				int x;
				cin >> x;
				if (linked_list.Find(x)) {
					cout << "\n   Item " << x << " is found!" << endl;

				}
				else {
					cout << "\n   Item " << x << " not found." << endl;
				}
				linked_list.DisplayLinkedListValues("Values");
			}
			DisplayEndl();
			break;

			//Clear Member Function
		case 'k':
			linked_list.DisplayLinkedListValues("Before Clear");
			linked_list.Clear();
			linked_list.DisplayLinkedListValues("After Clear");
			DisplayEndl();
			break;

			//Back
		case 'x':
			break;

			//For Invalid Inputs
		default:
			cout << "\n Invalid choice. Please try again.\n";
			break;
		}
	}
}


void ArrayListMenu()
{

	char choice;
	DataType item;
	ArrayList arr_list;

	DisplayEndl();
	cout << "This program demonstrates the array list. " << endl;
	cout << MAX_LENGTH << " is the maximum number of elements ";

	arr_list.Create();
	DisplayEndl();
	cout<<"Array List has been created"<<endl;
	arr_list.DisplayArrayListValues("Initial Values");

	choice = 'z';

	while (choice != 'x')
	{
		DisplayEndl();
		cout << "*******************************************************" << endl;
		cout << "1: Insert(Unsorted)   (Append an element to the end of the list)\n";
		cout << "2: Delete (Unsorted)  (Delete an element in the unsorted list)\n";
		cout << "3: Insert(Sorted)     (Insert an element and keep the list ordered)\n";
		cout << "4: Delete(Sorted)     (Delete an element in the sorted list)\n";
		cout << "p: Print              (Display all list element)\n";
		cout << "x: Back               (Return to the Main Menu)\n\n";

		cout << "   *** Check Other Member Functions ***\n";
		cout << "a: ResetP       (sets p to -1)\n";
		cout << "b: Iterate      (add 1 to p)\n";
		cout << "c: IsPSet       (outputs true if p has a valid value)\n";
		cout << "d: getP         (outputs the value of p)\n";
		cout << "e: SetP         (sets p to a given value)\n";
		cout << "f: Read         (outputs the value of element at index p)\n";
		cout << "g: Write        (writes new value into element at index p)\n";
		cout << "h: Length       (displays the length of the array)\n";
		cout << "i: IsEmpty      (displays true if length is 0)\n";
		cout << "j: IsFull       (displays true if length is 10\n";
		cout << "k: FindUnsorted (displays true if an item is found in the array)\n";
		cout << "l: Find Sorted  (displays true if item is foung in sorted array)\n";
		cout << "m: Clear()      (reinitialize the list)\n";
		cout << "*******************************************************" << endl << endl;
		
		cout << "   Please enter your choice here:";
		cin >> choice;

		switch (choice)
		{
			//Insert item in Unsorted Arraylist
		case '1':
			item = readInt("to insert(Unsorted):");
			if (arr_list.IsFull()) {
				cout << "\n  Array is Full. Please delete an element and try again." << endl;
			}
			else {
				arr_list.InsertUnsorted(item);
			}
			break;

			//Delete item in Unsorted Arraylist
		case '2':
			item = readInt("to delete(Unsorted):");
			if (arr_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				if (arr_list.FindUnsorted(item) && arr_list.IsPSet()) {
					arr_list.DeleteUnsorted();
				}
				else {
					cout << "   No such element is found." << endl << endl;
				}
			}
			break;

			//insert item in Sorted Arraylist
		case '3':
			item = readInt("to insert(Sorted):");
			if (arr_list.IsFull()) {
				cout << "\n  Array is Full. Please delete an element and try again." << endl;
			}
			else {
				arr_list.InsertSorted(item);
			}
			break;

			//Delete item in Sorted ArrayList
		case '4':
			item = readInt("to delete(Sorted):");
			if (arr_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				if (arr_list.FindSorted(item) && arr_list.IsPSet()) {
					arr_list.DeleteSorted();
				}
				else {
					cout << "   No such element is found." << endl << endl;
				}
			}
			break;

			//Prints all elements in the ArrayList
		case 'p':
			if (arr_list.IsEmpty()) {
				cout << "   There is no element yet." << endl;
			}
			else {
				cout << "   The content of the current ordered list is: " << endl;
				for (int i = 0; i < arr_list.Length(); i++) {
					arr_list.SetP(i);
					if(arr_list.IsPSet())
					cout << "   " << arr_list.Read() << endl;
				}
			}
			break;
		
		
			//Checking of Member functions
			//ResetP Member Function
		case 'a':
			arr_list.DisplayArrayListValues("Before ResetP");
			arr_list.ResetP();
			arr_list.DisplayArrayListValues("After ResetP");
			DisplayEndl();
			break;

			//Iterate Member Function
		case 'b':
			arr_list.DisplayArrayListValues("Before Iterate");
			arr_list.Iterate();
			arr_list.DisplayArrayListValues("After Iterate");
			DisplayEndl();
			break;

			//IsPSet Member Function
		case 'c':
			arr_list.DisplayArrayListValues("Values");
			cout<<"   IsPSet: "<<BoolStringValue(arr_list.IsPSet());
			DisplayEndl();
			break;

			//GetP Member Function
		case 'd':
			cout<<"\n   Value of P is "<<arr_list.GetP();
			DisplayEndl();
			break;

			//SetP Member Function
		case 'e':
			arr_list.DisplayArrayListValues("Before SetP");
			cout<<"\n   Enter new value of p: ";
			int x;
			cin>>x;
			arr_list.SetP(x);
			arr_list.DisplayArrayListValues("After SetP");
			DisplayEndl();
			break;

			//Read Member Function
		case 'f':
			if(arr_list.IsPSet()){
				cout<<"\n   The value of element at index "<<arr_list.GetP()<<" is "<<arr_list.Read();
			}
			else{
				cout<<"\n   Invalid value of P"<<endl;
			}
			arr_list.DisplayArrayListValues("Values");
			DisplayEndl();
			break;

			//Write Member Function 
		case 'g':
			if(arr_list.IsPSet()){
				arr_list.DisplayArrayListValues("Before Write");
				cout<<"\n   Enter new value element at index p: ";
				int x;
				cin>>x;
				arr_list.Write(x);
				arr_list.DisplayArrayListValues("After Write");
			}else{
				cout<<"\n   P is invalid"<<endl;
			}
			DisplayEndl();
			break;

			//Length Member Function
		case 'h':
			cout << "\n   Value of Length is " << arr_list.Length();
			DisplayEndl();
			break;

			//IsEmpty Member Function
		case 'i':
			arr_list.DisplayArrayListValues("Values");
			cout << "\n   IsEmpty: " << BoolStringValue(arr_list.IsEmpty());
			DisplayEndl();
			break;

			//IsFull Member Function
		case 'j':
			arr_list.DisplayArrayListValues("Values");
			cout << "\n   IsFull: " << BoolStringValue(arr_list.IsFull());
			DisplayEndl();
			break;

			//FindUnsorted Member Function
		case 'k':
			if (arr_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				cout << "\n   Enter item to find: ";
				int x;
				cin >> x;
				if (arr_list.FindUnsorted(x)) {
					cout << "\n   Item " << x << " is found!"<<endl;
					
				}
				else {
					cout << "\n   Item " << x << " not found."<<endl;
				}
				arr_list.DisplayArrayListValues("Values");
			}
			DisplayEndl();
			break;

			//FindSorted Member Function
		case 'l':
			if (arr_list.IsEmpty()) {
				cout << "\n   Array is Empty. Please add elements and try again." << endl;
			}
			else {
				cout << "\n   Enter item to find: ";
				int x;
				cin >> x;
				if (arr_list.FindSorted(x)) {
					cout << "\n   Item " << x << " is found!" << endl;

				}
				else {
					cout << "\n   Item " << x << " not found." << endl;
				}
				arr_list.DisplayArrayListValues("Values");
			}
			DisplayEndl();
			break;

			//Clear Member Function
        case 'm':
			arr_list.DisplayArrayListValues("Before Clear");
			arr_list.Clear();
			arr_list.DisplayArrayListValues("After Clear");
			DisplayEndl();
			break;

			//Back
		case 'x':
			break;

			//For Invalid Inputs
		default:
			cout << "\n Invalid choice. Please try again.\n";
			break;
		}
	}

}

//for formatting
void DisplayEndl()
{
	cout<<endl<<endl;
}

//for taking input
DataType readInt(string descr)
{
	DataType intval;
	cout << "\n   Please enter an integer value " << descr;
	cin >> intval;

	return intval;
}

//convert the bool value to a string
string BoolStringValue(bool value) {
	if (value)
		return "true";
	else
		return"false";
}