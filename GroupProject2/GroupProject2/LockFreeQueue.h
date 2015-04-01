#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Node.h"

class LockFreeQueue
{
	std::atomic<Node*> head, tail;
public:
	LockFreeQueue();
	~LockFreeQueue();
	void Enqueue(Node);
	Node Dequeue();

private:


};

LockFreeQueue::LockFreeQueue()
{
	std::atomic<Node> sentinel(-1);
	//head.store(&sentinel);
	//tail.store(&sentinel);
	
	

}

LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(Node pass) {
	Node* temp = new Node();
	Node eric;

	if(head.compare_exchange_strong(temp->next, temp));

	
	
		
}
