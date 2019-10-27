//ReceiverOutputQueue.h

#ifndef RECEIVEROUTPUTQUEUE_H
#define RECEIVEROUTPUTQUEUE_H

const int RECEIVER_OUTPUT_QUEUE_SIZE = 16;

struct ReceiverAckMessage;
struct ReceiverAckMessage {
	int message_number;
	char char_data;
};

class ReceiverOutputQueue
{
private:
	int front;
	int back;
	ReceiverAckMessage a[RECEIVER_OUTPUT_QUEUE_SIZE];
	int length;
public:
	ReceiverOutputQueue();
	int Length()const;
	bool IsEmpty()const;
	bool IsFull()const;
	bool Enqueue(ReceiverAckMessage x);
	ReceiverAckMessage Dequeue();
	void Clear();
};

#endif

