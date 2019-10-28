//AsynchronousFTPSimulation.cpp

#include <iostream>
#include <string>	//for getline()
#include <fstream>	//for reading and writting a file
#include <cstdlib>	//for generating random number
#include <ctime>	//for srand seed
#include "ReceiverInputQueue.h"
#include "SenderInputQueue.h"
#include "ReceiverOutputQueue.h"
#include "SenderOutputQueue.h"

using namespace std;

void FileTransferSimulation(ifstream& inputFile, ofstream& outputFile);
int GenerateTimeToNextEvent();

//struct foo {
//	int foo1;
//	string foo2;
//};

int main() {

	//initializing the files
	string filename;
	cout << "Enter output file: ";
	getline(cin, filename);
	ofstream outputFile(filename);
	cout << "Enter input file: ";
	getline(cin, filename);
	ifstream inputFile(filename);

	if (inputFile.good())
	{
		//starts Simulation
		srand(time(0)); //adds seed to random number generator
		FileTransferSimulation(inputFile, outputFile);
		inputFile.close();
		outputFile.close();
	}
	else
		//file not found
		cout << "Invalid Input File!" << endl;
	return 0;
}

void FileTransferSimulation(ifstream& inputFile, ofstream& outputFile)
{
	const bool NO_SEND = false;
	const bool NO_RECEIVE = false;
	const bool SEND = true;
	const bool RECEIVE = true;

	//initialize queues
	ReceiverInputQueue receiverInputQueue;
	ReceiverOutputQueue receiverOutputQueue;
	SenderInputQueue senderInputQueue;
	SenderOutputQueue senderOutputQueue;

	// Initialize the global clock.
	int globalClock = 0;

	// Generate the times for the next send and receive events.
	int senderTimeToSend = GenerateTimeToNextEvent();
	int senderTimeToReceive = GenerateTimeToNextEvent();
	int receiverTimeToReceive = GenerateTimeToNextEvent();
	int receiverTimeToSend = GenerateTimeToNextEvent();

	// Initialize flags.
	bool senderSendStatus = NO_SEND;
	bool senderReceiveStatus = NO_RECEIVE;
	bool receiverReceiveStatus = NO_RECEIVE;
	bool receiverSendStatus = NO_SEND;

	int char_index = 0; //counter for the index of char
	bool displayGlobalClk = false; //for displaying 

	// This loop will continue until the file has been transferred.
	// If the end of the input file has been reached and all
	// queues are empty, the file has been transferred, so quit.
	while (inputFile.good() || !(senderInputQueue.IsEmpty() && senderOutputQueue.IsEmpty()
		&& receiverInputQueue.IsEmpty() && receiverOutputQueue.IsEmpty()))
	{
		// The global clock ticks once.
		globalClock++;

		// Determine whether any send/receive events are scheduled.
		// If so, set the appropriate flag and generate the time for
		// the next event.
		if (globalClock == senderTimeToSend) {
			senderSendStatus = SEND;
			senderTimeToSend = globalClock + GenerateTimeToNextEvent();
		}
		if (globalClock == senderTimeToReceive) {
			senderReceiveStatus = RECEIVE;
			senderTimeToReceive = globalClock + GenerateTimeToNextEvent();
		}	
		if (globalClock == receiverTimeToReceive) {
			receiverReceiveStatus = RECEIVE;
			receiverTimeToReceive = globalClock + GenerateTimeToNextEvent();
		}		
		if (globalClock == receiverTimeToSend) {
			receiverSendStatus = SEND;
			receiverTimeToSend = globalClock + GenerateTimeToNextEvent();
		}

		// The simulation needs to ensure that messages are not received
		// before they are sent. So, we assume that if a message is sent
		// at time t, then it cannot be received until, at a minimum,
		// time t+1. That is, we assume that sending and receiving a
		// message does not happen instantaneously. Consequently, all
		// receive events are processed before any send events.

		// Step 1: We dequeue a data message from the receiver’s input queue.
		// Notice that we don’t enqueue the acknowledgement message yet. That
		// will be done in Step 5.
		ReceiverDataMessage receiverDataMsg;
		if (receiverReceiveStatus == RECEIVE) {
			if (!receiverInputQueue.IsEmpty()) {
				if (displayGlobalClk) {
					cout << "\nGlobal Clock: " << globalClock << endl;
					displayGlobalClk = false;
				}
				receiverDataMsg = receiverInputQueue.Dequeue();
				outputFile << receiverDataMsg.char_data;
			}
			else
				receiverReceiveStatus = NO_RECEIVE;
		}
		
		// Step 2: We dequeue an ack message from the sender’s input queue.
		// This step and Step 1 could be interchanged because they don’t
		// affect each other in any way. 
		if (senderReceiveStatus == RECEIVE) {
			if (!senderInputQueue.IsEmpty()) {
				if (displayGlobalClk) {
					cout << "\nGlobal Clock: " << globalClock << endl;
					displayGlobalClk = false;
				}	
				SenderAckMessage senderAckMsg = senderInputQueue.Dequeue();
				senderReceiveStatus = NO_RECEIVE;
				cout << "Sender: Received ["<< senderAckMsg.message_number
					<< ", " << senderAckMsg.char_data << "]" << endl;
			}
		}
			
		// Step 3: We read a character from the input file and enqueue a
		// data message in the sender’s output queue. Then, the sender tries
		// to enqueue as many data messages as it can in the receiver’s
		// input queue.
		if (senderSendStatus == SEND) {
			//read char in file anf enqueue in senderOQ  
			char ch;
			if (!senderOutputQueue.IsFull() && inputFile >> noskipws >> ch) {
				SenderDataMessage senderDataMsg = { char_index++,ch };
				senderOutputQueue.Enqueue(senderDataMsg);
			}
			while (!senderOutputQueue.IsEmpty() && !receiverInputQueue.IsFull()) {
				if (displayGlobalClk) {
					cout << "\nGlobal Clock: " << globalClock << endl;
					displayGlobalClk = false;
				}
				SenderDataMessage senderDataMsg = senderOutputQueue.Dequeue();
				ReceiverDataMessage receiverDataMsg1 = { senderDataMsg.message_number,senderDataMsg.char_data };
				receiverInputQueue.Enqueue(receiverDataMsg1);
				cout << "Sender: Sent [" << senderDataMsg.message_number << ", "
					<< senderDataMsg.char_data << "] " << endl;
			}
			senderSendStatus = NO_SEND;
		}
		
		// Step 4: The receiver tries to enqueue as many ack messages as
		// it can in the sender’s input queue. This step and Step 3 could be
		// interchanged.
		if (receiverSendStatus == SEND) {
			while (!receiverOutputQueue.IsEmpty() && !senderInputQueue.IsFull()) {
				if (displayGlobalClk) {
					cout << "\nGlobal Clock: " << globalClock << endl;
					displayGlobalClk = false;
				}
				ReceiverAckMessage receiverAckMsg = receiverOutputQueue.Dequeue();
				SenderAckMessage senderAckMessage = { receiverAckMsg.message_number,receiverAckMsg.char_data };
				senderInputQueue.Enqueue(senderAckMessage);
				receiverSendStatus = NO_SEND;
				cout << "Receiver: Sent [" << receiverAckMsg.message_number << ", "
					<< receiverAckMsg.char_data << "] " << endl;
			}		
		}
		// Step 5: If a data message was received in Step 1, enqueue an
		// acknowledgement in the receiver’s output queue.
		if (receiverReceiveStatus == RECEIVE) {
			if (displayGlobalClk) {
				cout << "\nGlobal Clock: " << globalClock << endl;
				displayGlobalClk = false;
			}
			ReceiverAckMessage receiverAckMsg = { receiverDataMsg.message_number,receiverDataMsg.char_data };
			receiverOutputQueue.Enqueue(receiverAckMsg);
			receiverReceiveStatus = NO_RECEIVE;
			cout << "Receiver: Received [" << receiverAckMsg.message_number << ", "
				<< receiverAckMsg.char_data << "] " << endl;
		}
		displayGlobalClk = true;
	}
}

//generates number 1-100
int GenerateTimeToNextEvent()
{
	return (1 + rand() % 100);
}

