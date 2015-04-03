#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Node.h"

class LockFreeQueue
{
public:
	LockFreeQueue() : sentinel(-1) {
		head = &sentinel;
		tail = &sentinel;
	};
	~LockFreeQueue();
	void Enqueue(Node);
	void Dequeue();
	std::atomic<Node> *head, *tail;
	std::atomic<Node> sentinel;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(Node pass) {
	
	Node *temp = new Node();
	
	while (true) {
		temp = &tail->load();

		if (tail->compare_exchange_strong(*temp->next, pass))
			//The first compare succeeds, and there wasn't an enqueue that happened during this one. Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
			break;
	}
}

void LockFreeQueue::Dequeue() {

}
