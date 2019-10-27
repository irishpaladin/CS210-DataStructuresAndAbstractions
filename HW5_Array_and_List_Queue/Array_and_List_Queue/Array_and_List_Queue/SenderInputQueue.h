//SenderInputQueue.h

#ifndef SENDERINPUTQUEUE_H
#define SENDERINPUTQUEUE_H

const int SENDERS_INPUT_QUEUE_SIZE = 4;

struct SenderAckMessage;
struct SenderAckMessage {
	int message_number;
	char char_data;
	SenderAckMessage* next;
};

class SenderInputQueue
{
private:
	SenderAckMessage* front;
	SenderAckMessage* back;
	int length;

public:
	SenderInputQueue();
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void Enqueue(SenderAckMessage x);
	SenderAckMessage Dequeue();
	void Clear();
};

#endif