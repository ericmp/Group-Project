#include "LockFreeQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int main()
{
	LockFreeQueue eric;
	eric.Dequeue();
	//if (eric.sentinel.load().next == NULL)
	//	std::cout << eric.sentinel.load().value;
	//eric.Dequeue();
	getchar();
	return 0;
}