#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory>

#define botHalf 0xFFFFFFFF;
#define topHalf 0xFFFFFFFF00000000;

struct Node {
	long long int value;
	std::atomic<Node *> next;
	Node* here;
	Node() {};
	Node(long long int initial) : value(initial) { here = this; }
	~Node() { delete next.load(); }


};



class LockFreeQueue
{
public:
	LockFreeQueue() : sentinel(-1) {
		head.store(new Node(-1));
		tail.store(new Node(-1));
	};
	~LockFreeQueue();
	void Enqueue(long long int);
	int Dequeue();
	std::atomic<Node*> head, tail;
	Node sentinel;
	long int count = 0x1;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(long long int value) {

	Node lastTmp, *temp;


	//NEED TO PUT AN IF STATEMENT HERE THAT CHECKS IF THE ENITRE THING IS EMPTY OR NOT. USE COMPARE AND EXCHANGE TO CHECK

	do {
		memcpy(&lastTmp, tail.load(), sizeof(Node));
		temp = lastTmp.next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new Node(value | (count++ << 32))));
	//The first compare succeeds, and there wasn't an enqueue that happened during this one. 
	//Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
	


	if (tail.compare_exchange_weak(lastTmp.here, tail.load()->next.load()));
	//make the tail point to what we just enqueued, otherwise don't do anything

	//Check for hanging tail
	while (tail.load()->next.load() != NULL)
		tail = tail.load()->next.load();

	delete(temp);
}

int LockFreeQueue::Dequeue() {

	Node tmpHold;
	long long int tmp;
	std::atomic<long long int> tmpNum;
	tmpNum.store(-1);

	tmpNum.store(tmpNum.exchange(head.load()->next.load()->value));


	//delete()


	//int node_val = tmp & botHalf;
	//int node_safebits = tmp & topHalf;


	return tmp;

}
