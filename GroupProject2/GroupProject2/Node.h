#include <iostream>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class Node
{

public:
	float value;
	Node *next, *prev;
	Node();
	Node(float);
	~Node();

private:

};

Node::Node() {

}

Node::Node(float initial)
{
	value = initial;
}

Node::~Node()
{
}