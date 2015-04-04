#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

class NodePtr {
public:
	Node* ptr;
	NodePtr(){};
	NodePtr(Node);
	~NodePtr();

private:

	};

	NodePtr::NodePtr(Node inc)
	{
		ptr = &inc;
	}

	NodePtr::~NodePtr()
	{
	}