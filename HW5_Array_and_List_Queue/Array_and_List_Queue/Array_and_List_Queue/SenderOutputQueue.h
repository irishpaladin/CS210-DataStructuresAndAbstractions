//SenderOutputQueue.h

#ifndef SENDEROUTPUTQUEUE_H
#define SENDEROUTPUTQUEUE_H

const int SENDERS_OUTPUT_QUEUE_SIZE = 32;

struct SenderDataMessage;
struct SenderDataMessage {
	int message_number;
	char char_data;
};

class SenderOutputQueue
{
private:
	int front;
	int back;
	SenderDataMessage a[SENDERS_OUTPUT_QUEUE_SIZE];
	int length;
public:
	SenderOutputQueue();
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	bool Enqueue(SenderDataMessage x);
	SenderDataMessage Dequeue();
	void Clear();
};

#endif