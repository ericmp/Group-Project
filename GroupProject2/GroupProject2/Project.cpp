#include "LockFreeQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int main()
{
	LockFreeQueue eric;
	Node i(5);
	eric.Enqueue(i);
	//std::cout << eric.tail->load().value;
	//if (eric.sentinel.load().next == NULL)
	//	std::cout << eric.sentinel.load().value;
	//eric.Dequeue();
	getchar();
	return 0;
}