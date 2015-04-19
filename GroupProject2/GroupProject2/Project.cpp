#include "LockFreeQueue.h"
<<<<<<< HEAD
#include <pthread.h>
#include <thread>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <vector>
#include <iostream>



struct GraphEdge {
	std::string ID;
	int weight;
	GraphEdge() {};
	GraphEdge(int a, int b) : ID(std::to_string(a)), weight(b) {};
};


struct Node {
	std::string name;
	std::list<GraphEdge> neighbors;
	bool filled;
	void Place(GraphEdge a) { filled = true; neighbors.push_back(a); }
};

struct Thread {
	ReturnNode *deqNode = new ReturnNode();
};

struct TableEntry {
	std::atomic<int> currLowestValue;
	std::string path;
	TableEntry() {};
	TableEntry(const TableEntry& origin);
};

TableEntry::TableEntry(const TableEntry& origin) {
	currLowestValue.store(-2);
}

TableEntry *table;
LockFreeQueue queue;
int target;
std::vector<Node> nodes;

void solvePath() {
	//variables are local for each thread
	Thread node;
//	std::mem_fn(&std::thread::join);
	//std::cout << &std::thread::joinable;

	/*
	queue.Dequeue(*node.deqNode);

	//if the value is less than the current value in the table (or the table value hasn't been altered yet), set your current value as the new table entry
	if ((table[node.deqNode->name].currLowestValue.load() < 0) || table[node.deqNode->name].currLowestValue.load() > (int)node.deqNode->currLength) {
		table[node.deqNode->name].currLowestValue.store((int)node.deqNode->currLength);
		//if your node was the target node, the thread can exit
		if (node.deqNode->name == target)
			std::mem_fn(&std::thread::join);
	}
	//if your current value is greater than or equal to the table entry, or you have no neighbors, the thread can exit
	if ((table[node.deqNode->name].currLowestValue.load() >= 0) || !nodes[node.deqNode->name].filled)
		std::mem_fn(&std::thread::join);
		*/
	//NEED TO ALSO STORE/UPDATE PATH. DO LATER


	//Enqueue the neighbors, along with their values plus the current path

	


}




struct lessThanNeighbor
{
	inline bool operator() (const GraphEdge& struct1, const GraphEdge& struct2)
	{
		return (struct1.weight > struct2.weight);
	}
};

int main()
{
	
	std::ifstream input;
	int numNodes, numEdges, edge1, edge2, weight, start, end;


	//Open the file
	input.open("input.txt");

	//Get number of nodes and number of edges
	input >> numNodes >> numEdges;
	input >> start >> end;
	target = start;
	
	//Create an atomic table for the lowest weight value entries
	table = new TableEntry[numNodes + 1];

	nodes.resize(numNodes + 1);

	
	//Place all nodes in the array
	while (input >> edge1 >> edge2 >> weight) {
		//Get the next set of nodes and edge
		GraphEdge temp1(edge2, weight), temp2(edge1, weight);
		nodes[edge1].Place(temp1);
		nodes[edge2].Place(temp2);
	}

	//Sort each node, except for those where there is no value
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].name = std::to_string(i);
		if (nodes[i].filled)
			nodes[i].neighbors.sort(lessThanNeighbor());
	}


	//At this point, we have a vector of graphs, who each have a list of neighbors sorted from least distance to greatest distance
	//so let's get started with the path finding

	//Enqueue starting node
	for each (GraphEdge x in nodes[0].neighbors)
		queue.Enqueue(x.ID, x.weight);


	//std::thread *threads[nodes[0].neighbors.size()];

	std::thread thread{ solvePath };

	
	//}

	getchar();

	
=======
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <iomanip>



int main()
{
	LockFreeQueue eric;
	eric.Enqueue(5);
	std::cout << eric.tail.load()->value;
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
>>>>>>> origin/master
	return 0;
}