//ReceiverInputQueue.cpp

#include "ReceiverInputQueue.h"
#include <iostream>

ReceiverInputQueue::ReceiverInputQueue()
{
	// this is the constructor
	// initializes the queue
	// sets front and back
	front = NULL;
	back = front;
	length = 0;
}

int ReceiverInputQueue::Length() const
{
	// returns the number of items in the queue
	return length;
}

bool ReceiverInputQueue::IsEmpty() const
{
	// checks whether the queue is empty
	if (length == 0)
		return true;
	return false;
}

bool ReceiverInputQueue::IsFull() const
{
	// checks whether the queue is full
	try
	{
		ReceiverDataMessage* q = new ReceiverDataMessage;
		delete q;
		if (length == RECEIVER_INPUT_QUEUE_SIZE)
			return true;
		return false;
	}
	catch (std::bad_alloc e)
	{
		return true;
	}
}

void ReceiverInputQueue::Enqueue(ReceiverDataMessage x)
{
	// inserts a new item at the back of the queue
	// always call IsFull prior to calling Enqueue
	// sets front and back
	ReceiverDataMessage* q = new ReceiverDataMessage;
	q->message_number = x.message_number;
	q->char_data = x.char_data;
	q->next = NULL;
	if (front == NULL)
		front = q;
	else 
		back->next = q;
	back = q;
	length++;
	return;
}

ReceiverDataMessage ReceiverInputQueue::Dequeue()
{
	// removes the item from the front of the queue
	// always call IsEmpty prior to calling Dequeue
	// sets front and back
	ReceiverDataMessage* q = front;
	ReceiverDataMessage x; //storage of the data returned
	x.message_number = front->message_number;
	x.char_data = front->char_data;
	front = front->next;
	if (front == NULL)
		back = front;
	delete q;
	length--;
	return x;
}

void ReceiverInputQueue::Clear()
{
	// reinitializes the queue
	// sets front and back
	while (front != NULL) {
		ReceiverDataMessage* q = front;
		front = front->next;
		delete q;
	}

	back = front;
	length = 0;
	return;
}
