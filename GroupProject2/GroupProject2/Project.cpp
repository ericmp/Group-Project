#include "LockFreeQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>



int main()
{
	LockFreeQueue eric;
	eric.Enqueue(5);
	eric.Enqueue(7);
	/*
	std::shared_ptr<int> p = std::make_shared<int>();

	std::thread t1(eric.Dequeue, p), t2(eric.Dequeue, p), t3(eric.Dequeue, p);
	//eric.Dequeue();
	//if (eric.sentinel.load().next == NULL)
	//	std::cout << eric.sentinel.load().value;
	//eric.Dequeue();
	*/
	getchar();
	return 0;
}