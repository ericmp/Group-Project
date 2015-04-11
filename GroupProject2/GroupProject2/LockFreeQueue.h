#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory>



struct Node {
	float value;
	std::atomic<Node *> next;
	Node() {};
	Node(float initial) : value(initial) {}
	~Node() { delete next.load(); }


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
	
	Node *temp = new Node();
	Node *lastTmp = new Node();

	
	do {
		std::memcpy(lastTmp, tail, sizeof(Node));
		temp = lastTmp->next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new Node(value)));
		//The first compare succeeds, and there wasn't an enqueue that happened during this one. 
		//Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
	

	std::atomic<Node*> *ptr = &tail;
	
	//std::atomic_compare_exchange_weak(&tail, &lastTmp, tail.load()->next.load());
	//make the tail point to what we just enqueued, otherwise don't do anything
		
		//Check for hanging tail
		//while (tail.load()->next.load() != NULL)
		//	tail = tail.load()->next.load();

	delete(temp);	
	delete(lastTmp);
}

void LockFreeQueue::Dequeue() {
	//std::



}
