//ReceiverOutputQueue.cpp

#include "ReceiverOutputQueue.h"

ReceiverOutputQueue::ReceiverOutputQueue()
{
	// this is the constructor
	// initializes the queue
	// sets front and back
	front = RECEIVER_OUTPUT_QUEUE_SIZE - 1;
	back = front;
	length = 0;
}

int ReceiverOutputQueue::Length() const
{
	// returns the number of items in the queue
	return length;
}

bool ReceiverOutputQueue::IsEmpty() const
{
	// checks whether the queue is empty
	if (length == 0)
		return true;
	return false;
}

bool ReceiverOutputQueue::IsFull() const
{
	// checks whether the queue is full
	if (length == RECEIVER_OUTPUT_QUEUE_SIZE)
		return true;
	return false;
}

bool ReceiverOutputQueue::Enqueue(ReceiverAckMessage x)
{
	// inserts a new item at the back of the queue
	// always call IsFull prior to calling Enqueue
	// sets back
	back = (back + 1) % RECEIVER_OUTPUT_QUEUE_SIZE;
	a[back] = x;
	length++;
	return true;
}

ReceiverAckMessage ReceiverOutputQueue::Dequeue()
{
	// removes the item at the front of the queue
	// always call IsEmpty prior to calling Dequeue
	// sets front
	front = (front + 1) % RECEIVER_OUTPUT_QUEUE_SIZE;
	ReceiverAckMessage x = a[front];
	length--;
	return x;
}

void ReceiverOutputQueue::Clear()
{
	// reinitializes the queue
	// sets front and back
	front = RECEIVER_OUTPUT_QUEUE_SIZE - 1;
	back = front;
	length = 0;
	return;
}
