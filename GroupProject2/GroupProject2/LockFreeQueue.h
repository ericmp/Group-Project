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
		head.store(&sentinel);
		tail.store(&sentinel);
	};
	~LockFreeQueue();
	void Enqueue(Node);
	void Dequeue();
	std::atomic<Node*> head, tail;
	Node sentinel;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(Node pass) {

	Node *temp = tail.load();
	Node temp2 = *temp;
	temp2.next = new Node(pass);

	do {
		Node *temp = tail.load();
		Node temp2 = *temp;
		temp2.next = new Node(pass);
	} while (!tail.compare_exchange_strong(temp, &temp2));
	//The first compare succeeds, and there wasn't an enqueue that happened during this one. Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
	
	std::atomic<Node*> *ptr = &tail;
	temp = &temp2;

	if (!ptr->compare_exchange_weak(temp, temp2.next));
		//do nothing if the tail no longer points to what we just enqueued

	if (tail.load()->next == NULL);




		//std::atomic_compare_exchange_strong(tail, temp, &temp2);


}

void LockFreeQueue::Dequeue() {



}
