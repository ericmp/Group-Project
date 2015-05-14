#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory>
<<<<<<< HEAD
=======
#include <list>
#include <string>
>>>>>>> parent of 367a800... Revert "a"

#define botHalf 0xFFFFFFFF;
#define topHalf 0xFFFFFFFF00000000;

<<<<<<< HEAD
struct Node {
	long long int value;
	std::atomic<Node *> next;
	Node* here;
	Node() {};
	Node(long long int initial) : value(initial) { here = this; }
	~Node() { delete next.load(); }
=======

struct ReturnNode {
	int name;
	long long int currLength;
	bool sentinel;
	int pathCount = 0;

	ReturnNode() { pathCount = 0; };
	ReturnNode(int pass, long long int value, bool isSentinel) : name(pass), currLength(value), sentinel(isSentinel) {pathCount++; }

};


struct QueueNode {
	std::atomic<QueueNode *> next;
	QueueNode* here;
	std::atomic<ReturnNode*> node;
	QueueNode() { here = this;};
	QueueNode(int pass, long long int initial, bool isSentinel) { node.store(new ReturnNode(pass, initial, isSentinel));  here = this; }
>>>>>>> parent of 367a800... Revert "a"
};



class LockFreeQueue
{
public:
	LockFreeQueue() {
<<<<<<< HEAD
		Node* sentinel = new Node(-1);
=======
		count = 0x1;
		QueueNode* sentinel = new QueueNode(-1, -1, true);
>>>>>>> parent of 367a800... Revert "a"
		head.store(sentinel);
		tail.store(sentinel);
	};
	~LockFreeQueue();
<<<<<<< HEAD
	void Enqueue(long long int);
	int Dequeue();
	std::atomic<Node*> head, tail;
	long long int count = 0x1;
=======
	void Enqueue(const std::string,const int);
	bool Dequeue(ReturnNode &pass);
	std::atomic<QueueNode*> head, tail;
	long long int count;
>>>>>>> parent of 367a800... Revert "a"

private:

};



LockFreeQueue::~LockFreeQueue()
{
}

<<<<<<< HEAD
void LockFreeQueue::Enqueue(long long int value) {

	Node lastTmp, *temp;


	//NEED TO PUT AN IF STATEMENT HERE THAT CHECKS IF THE ENITRE THING IS EMPTY OR NOT. USE COMPARE AND EXCHANGE TO CHECK

	do {
		memcpy(&lastTmp, tail.load(), sizeof(Node));
		temp = lastTmp.next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new Node(value | (count++ << 32))));
=======
void LockFreeQueue::Enqueue(const std::string name, const int value) {
	
	QueueNode lastTmp, *temp;


	do {
		memcpy(&lastTmp, tail.load(), sizeof(QueueNode));
		temp = lastTmp.next.load();
	} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new QueueNode(std::stoi(name), value, false)));
	//} while (!std::atomic_compare_exchange_strong(&tail.load()->next, &temp, new QueueNode(std::stoi(name), (value | (count++ << 32)), false)));
>>>>>>> parent of 367a800... Revert "a"
	//The first compare succeeds, and there wasn't an enqueue that happened during this one. 
	//Otherwise, the compare failed, and there was an enqueue that happened during this one...so let's try again!
	


	if (tail.compare_exchange_weak(lastTmp.here, tail.load()->next.load()));
	//make the tail point to what we just enqueued, otherwise don't do anything

	//Check for hanging tail
	while (tail.load()->next.load() != NULL)
		tail = tail.load()->next.load();

	delete(temp);
<<<<<<< HEAD
}

int LockFreeQueue::Dequeue() {

	Node *tmpHold = new Node();
	std::atomic<long long int> tmpNum = -1;

	//swap the values in
	head.load()->next.load()->value = tmpNum.exchange(head.load()->next.load()->value);
	
	//Switch head to the new sentinel node. ABA is solved here thanks to reference bits that we have in the upper bits of the 64 bit int
	while(!head.compare_exchange_weak(tmpHold, head.load()->next));

	free(tmpHold);


	//int node_val = tmp & botHalf;
	//int node_safebits = tmp & topHalf;


	return tmpNum;
=======
	
}

bool LockFreeQueue::Dequeue(ReturnNode &pass) {

	std::atomic<ReturnNode> tmpNode;


	//check if the queue is empty
	if (head.load()->next.load() != NULL){
			tmpNode.store(*head.load()->next.load()->node.load());
			if (tmpNode.load().name > 0) {
				memcpy(&pass, &tmpNode.load(), sizeof(ReturnNode));
				head.store(head.load()->next);
				return true;
			}

		//ABA IS NOT SOLVED, COME BACK TO THIS LATER

	}

	return false;
>>>>>>> parent of 367a800... Revert "a"

}
