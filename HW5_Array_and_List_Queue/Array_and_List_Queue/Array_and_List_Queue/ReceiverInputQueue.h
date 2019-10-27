//ReceiverInputQueue.h

#ifndef RECEIVERINPUTQUEUE_H
#define RECEIVERINPUTQUEUE_H

const int RECEIVER_INPUT_QUEUE_SIZE = 8;

struct ReceiverDataMessage;
struct ReceiverDataMessage {
	int message_number;
	char char_data;
	ReceiverDataMessage* next;
};

class ReceiverInputQueue
{
private:
	ReceiverDataMessage* front;
	ReceiverDataMessage* back;
	int length;

public:
	ReceiverInputQueue();
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void Enqueue(ReceiverDataMessage x);
	ReceiverDataMessage Dequeue();
	void Clear();
};

#endif