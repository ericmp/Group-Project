#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



struct Node {
	float value;
	std::atomic<Node *> next;
	Node(float initial) : value(initial) {}


};




class LockFreeQueue
{
public:
	LockFreeQueue() : sentinel(-1) {
		head.store(&sentinel);
		tail.store(&sentinel);
	};
	~LockFreeQueue();
	void Enqueue(float);
	void Dequeue();
	std::atomic<Node*> head, tail;
	Node sentinel;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(float value) {
	
	Node *temp = new Node(1);
	Node pass(value);
	
	
	do {
		temp = tail.load()->next;
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, &pass));
		//The first compare succeeds, and there wasn't an enqueue that happened during this one. 
		//Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!

	std::atomic<Node*> *ptr = &tail;

		if (!ptr->compare_exchange_weak(temp, temp->next));
	//do nothing if the tail no longer points to what we just enqueued

		//Check for hanging tail
	//while (tail.load()->next != NULL)
	//ptr->exchange(tail.load()->next);
	
}

void LockFreeQueue::Dequeue() {



}
