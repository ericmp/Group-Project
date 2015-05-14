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

struct TableEntry {
	std::atomic<int*> currLowestValue;
	std::string path;
	TableEntry() {};
	TableEntry(const TableEntry& origin);
};


TableEntry::TableEntry(const TableEntry& origin) {

	currLowestValue.store(new int(-1));
}


struct GraphEdge {
	int ID;
	int weight;
	GraphEdge() {};
	GraphEdge(int a, int b) : ID(a), weight(b) {};
};

struct Node {
	int name;
	long long int value;
	bool filled = false;
	std::atomic<Node *> next;
	std::list<GraphEdge> neighbors;
	Node* here;
	Node(const Node& origin);
	Node() { name = -1; value = 0; next.store(new Node(-1, name)); };
	Node(long long int initial, int n) : value(initial), name(n) { name = -1; here = this; value = 0;  }
	void Place(int number, GraphEdge a) { neighbors.push_back(a); filled = true; }
};
Node* a = new Node(-1, -1);

Node::Node(const Node& origin) {
	next.store(a);
}


class LockFreeQueue
{
public:
	LockFreeQueue() {
		count = 0x1;
		Node* sentinel = new Node(-1, -1);
		head.store(sentinel);
		tail.store(sentinel);
	};
	~LockFreeQueue();
	void Enqueue(const Node *);
	Node* Dequeue();
	std::atomic<Node*> head, tail;
	long long int count;

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

void LockFreeQueue::Enqueue(const Node* data) {
	
	Node lastTmp, *temp;

	//put iff state ment if sentinel node aciddentally is gone?
	do {
		memcpy(&lastTmp, tail.load(), sizeof(Node));
		temp = lastTmp.next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new Node((*data).value | (count++ << 32), (*data).name)));
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
	int ret;


	//check if the queue is empty
	if (head.load()->next.load() != NULL) {

		//swap the values in
		head.load()->next.load()->value = tmpNum.exchange(head.load()->next.load()->value);
		ret = tmpNum;
		int r = head.load()->next.load()->name;
		//Switch head to the new sentinel node. ABA is solved here thanks to reference bits that we have in the upper bits of the 64 bit int
		while (!head.compare_exchange_weak(tmpHold, head.load()->next));
		free(tmpHold);
		//int node_val = tmp & botHalf;
		//int node_safebits = tmp & topHalf;



		return new Node(ret, r);
	}
	return new Node(-1, -1);

}
