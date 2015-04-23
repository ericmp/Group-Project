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


struct GraphEdge {
	int ID;
	int weight;
	GraphEdge() {};
	GraphEdge(int a, int b) : ID(a), weight(b) {};
};

struct Node {
	int name = -1;
	long long int value;
	bool filled = false;
	std::atomic<Node *> next;
	std::list<GraphEdge> neighbors;
	Node* here;
	Node() {};
	Node(long long int initial) : value(initial) { here = this; }
	void Place(int number, GraphEdge a) { neighbors.push_back(a); filled = true; }
};



class LockFreeQueue
{
public:
	LockFreeQueue() {
		Node* sentinel = new Node(-1);
		head.store(sentinel);
		tail.store(sentinel);
	};
	~LockFreeQueue();
	void Enqueue(const Node *);
	Node* Dequeue();
	std::atomic<Node*> head, tail;
	long long int count = 0x1;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(const Node* data) {
	
	Node lastTmp, *temp;

	
	//NEED TO PUT AN IF STATEMENT HERE THAT CHECKS IF THE ENITRE THING IS EMPTY OR NOT. USE COMPARE AND EXCHANGE TO CHECK

	do {
		memcpy(&lastTmp, tail.load(), sizeof(Node));
		temp = lastTmp.next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new Node((*data).value | (count++ << 32))));
	//The first compare succeeds, and there wasn't an enqueue that happened during this one. 
	//Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
	


	if (tail.compare_exchange_weak(lastTmp.here, tail.load()->next.load()));
	//make the tail point to what we just enqueued, otherwise don't do anything

	//Check for hanging tail
	while (tail.load()->next.load() != NULL)
		tail = tail.load()->next.load();

	delete(temp);
	
}

Node* LockFreeQueue::Dequeue() {
	
	Node *tmpHold = new Node();
	std::atomic<long long int> tmpNum = -1;

	//swap the values in
	head.load()->next.load()->value = tmpNum.exchange(head.load()->next.load()->value);
	Node ret(tmpNum);
	//Switch head to the new sentinel node. ABA is solved here thanks to reference bits that we have in the upper bits of the 64 bit int
	while(!head.compare_exchange_weak(tmpHold, head.load()->next));
	free(tmpHold);


	//int node_val = tmp & botHalf;
	//int node_safebits = tmp & topHalf;
	

	return &ret;

}
