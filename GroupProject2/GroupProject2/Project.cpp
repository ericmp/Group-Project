#include "LockFreeQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <iomanip>



int main()
{
	LockFreeQueue eric;
	eric.Enqueue(5);
	//std::cout << eric.tail.load()->value;
	//eric.Enqueue(7);

	/*
	int b = 2;
	int* a = &b;;
	std::cout << &b << std::endl;
	std::cout << a << std::endl;
	std::cout << &a << std::endl;
	*(++a);
	std::cout << &a << std::endl;
	std::cout << a << std::endl;
	*/
	//int a = eric.Dequeue();

	//if (eric.sentinel.load().next == NULL)
	//	std::cout << eric.sentinel.load().value;
	//eric.Dequeue();
	getchar();
	return 0;
}