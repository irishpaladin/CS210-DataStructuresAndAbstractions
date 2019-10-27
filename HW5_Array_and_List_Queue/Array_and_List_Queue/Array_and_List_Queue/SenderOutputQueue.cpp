//SenderOutputQueue.cpp

#include "SenderOutputQueue.h"

SenderOutputQueue::SenderOutputQueue()
{
	// this is the constructor
	// initializes the queue
	// sets front and back
	front = SENDERS_OUTPUT_QUEUE_SIZE - 1;
	back = front;
	length = 0;
}

int SenderOutputQueue::Length() const
{
	// returns the number of items in the queue
	return length;
}

bool SenderOutputQueue::IsEmpty() const
{
	// checks whether the queue is empty
	if (length == 0)
		return true;
	return false;
}

bool SenderOutputQueue::IsFull() const
{
	// checks whether the queue is full
	if (length == SENDERS_OUTPUT_QUEUE_SIZE)
		return true;
	return false;
}

bool SenderOutputQueue::Enqueue(SenderDataMessage x)
{
	// inserts a new item at the back of the queue
	// always call IsFull prior to calling Enqueue
	// sets back
	back = (back + 1) % SENDERS_OUTPUT_QUEUE_SIZE;
	a[back] = x;
	length++;
	return true;
}

SenderDataMessage SenderOutputQueue::Dequeue()
{
	// removes the item at the front of the queue
	// always call IsEmpty prior to calling Dequeue
	// sets front
	front = (front + 1) % SENDERS_OUTPUT_QUEUE_SIZE;
	SenderDataMessage x = a[front];
	length--;
	return x;
}

void SenderOutputQueue::Clear()
{
	// reinitializes the queue
	// sets front and back
	front = SENDERS_OUTPUT_QUEUE_SIZE - 1;
	back = front;
	length = 0;
	return;
}
