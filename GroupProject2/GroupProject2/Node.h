#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class Node
{

public:
	float value;
	std::atomic<Node*> next;
	Node() {};
	Node(float);
	~Node();

private:

};

Node::Node(float initial)
{
	value = initial;
}

Node::~Node()
{
}