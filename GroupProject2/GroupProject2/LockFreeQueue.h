#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory>
#include <list>
#include <string>

#define botHalf 0xFFFFFFFF;
#define topHalf 0xFFFFFFFF00000000;


struct ReturnNode {
	int name;
	long long int currLength;
	bool sentinel;

	ReturnNode() {};
	ReturnNode(int pass, long long int value, bool isSentinel) : name(pass), currLength(value), sentinel(isSentinel) {};

};


struct QueueNode {
	std::atomic<QueueNode *> next;
	QueueNode* here;
	std::atomic<ReturnNode*> node;
	QueueNode() { here = this;};
	QueueNode(int pass, long long int initial, bool isSentinel) { node.store(new ReturnNode(pass, initial, isSentinel));  here = this; }
};



class LockFreeQueue
{
public:
	LockFreeQueue() {
		count = 0x1;
		QueueNode* sentinel = new QueueNode(-1, -1, true);
		head.store(sentinel);
		tail.store(sentinel);
	};
	~LockFreeQueue();
	void Enqueue(const std::string,const int);
	void Dequeue(ReturnNode &pass);
	std::atomic<QueueNode*> head, tail;
	long long int count;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(const std::string name, const int value) {
	
	QueueNode lastTmp, *temp;


	do {
		memcpy(&lastTmp, tail.load(), sizeof(QueueNode));
		temp = lastTmp.next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new QueueNode(std::stoi(name), value, false)));
	//} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new QueueNode(std::stoi(name), (value | (count++ << 32)), false)));
	//The first compare succeeds, and there wasn't an enqueue that happened during this one. 
	//Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
	


	if (tail.compare_exchange_weak(lastTmp.here, tail.load()->next.load()));
	//make the tail point to what we just enqueued, otherwise don't do anything

	//Check for hanging tail
	while (tail.load()->next.load() != NULL)
		tail = tail.load()->next.load();

	delete(temp);
	
}

void LockFreeQueue::Dequeue(ReturnNode &pass) {

	QueueNode *tmpHold;

	//check if the queue is empty
	if (head.load()->next.load() != NULL){
		//Atomic swap the value of next with a -1, as it will become the new sentinel. also, pass the value onto the calling thread
		memcpy(&pass, head.load()->next.load()->node.exchange(new ReturnNode(-1, -1, true)), sizeof(ReturnNode));
		//Advances the head pointer
		while (!head.compare_exchange_weak(tmpHold, head.load()->next));
	}
	//ABA IS NOT SOLVED, COME BACK TO THIS LATER

	free(tmpHold->node);
	free(tmpHold);

	//int node_val = tmp & botHalf;
	//int node_safebits = tmp & topHalf;

}
