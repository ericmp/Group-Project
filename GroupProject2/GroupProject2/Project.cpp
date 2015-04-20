#include "LockFreeQueue.h"
#include <thread>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <vector>
#include <iostream>
#include <list>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>



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
	ReturnNode *deqNode;

	Thread() {
		deqNode = new ReturnNode(-1, -1, true);
	}
};

struct TableEntry {
	std::atomic<int> currLowestValue;
	std::string path;
	TableEntry() { currLowestValue.store(-1); };
	TableEntry(const TableEntry& origin);
};

TableEntry::TableEntry(const TableEntry& origin) {
	currLowestValue.store(-2);
}

TableEntry *table;
LockFreeQueue queue;
int start, end;
std::vector<Node> nodes;
std::list<std::thread*> threads;
std::atomic<int> count(0);
HANDLE mainThread;

void solvePath() {
	//variables are local for each thread
	Thread node;
	int a = 0;

	if (queue.Dequeue(*node.deqNode)) {
	
			//if the value is less than the current value in the table (or the table value hasn't been altered yet), 
			//set your current value as the new table entry
			if ((table[node.deqNode->name].currLowestValue.load() <= 0) || (table[node.deqNode->name].currLowestValue.load() > (int)node.deqNode->currLength)) {
				//Update the table entry value witht the current shortest route
				table[node.deqNode->name].currLowestValue.store((int)node.deqNode->currLength);


				//if your node was the target node or has no neighbors, the thread can exit
				if (node.deqNode->name == end || !nodes[node.deqNode->name].filled) {
					count.fetch_sub(1);
					if (count.compare_exchange_strong(a, count)) {
						std::mem_fn(&std::thread::join);
						ResumeThread(mainThread);
					}
				}

				else {
					//Spawn new threads for each neighbor that will be enqueued
					for each (GraphEdge x in nodes[node.deqNode->name].neighbors)
						if (x.ID != std::to_string(start)) {
						//Enqueue the neighbors and spawn threads for each neighbor
						queue.Enqueue(x.ID, x.weight + node.deqNode->currLength);
						count.fetch_add(1);
						threads.push_back(new std::thread{ solvePath });
						}
				}
			}

			//if your current value is greater than or equal to the table entry, or the node has no neighbors then the thread can exit
			else if (table[node.deqNode->name].currLowestValue.load() <= (int)node.deqNode->currLength || !nodes[node.deqNode->name].filled) {
				count.fetch_sub(1);
				if (count.compare_exchange_strong(a, count)) {
					std::mem_fn(&std::thread::join);
					ResumeThread(mainThread);
				}
			}

		}
	else {
		count.fetch_add(1);
		threads.push_back(new std::thread{ solvePath });

	}

	count.fetch_sub(1);
	if (count.compare_exchange_strong(a, count)) {
		std::mem_fn(&std::thread::join);
		ResumeThread(mainThread);
	}
}


struct lessThanNeighbor
{
	inline bool operator() (const GraphEdge& struct1, const GraphEdge& struct2)
	{
		return (struct1.weight < struct2.weight);
	}
};

int main()
{

	std::ifstream input;
	int numNodes, numEdges, edge1, edge2, weight;


	//Open the file
	input.open("input.txt");

	//Get number of nodes and number of edges
	input >> numNodes >> numEdges;
	input >> start >> end;

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
		table[i].path = std::to_string(i);
		if (nodes[i].filled)
			nodes[i].neighbors.sort(lessThanNeighbor());
	}


	//At this point, we have a vector of graphs, who each have a list of neighbors sorted from least distance to greatest distance
	//so let's get started with the path finding

	//Enqueue starting node
	table[start].currLowestValue.store(0);
	for each (GraphEdge x in nodes[start].neighbors) {
		queue.Enqueue(x.ID, x.weight);
		//Spawn threads for each neighbor
		count.fetch_add(1);
		threads.push_back(new std::thread{ solvePath });
	}

	mainThread = OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId());
	SuspendThread(mainThread);

	if (table[end].currLowestValue.load() < 0)
		std::cout << "Sorry, there is no path between the start and finish nodes.";
	else {
		std::cout << "The shortest length between the start node and finish node is: " << table[end].currLowestValue << std::endl;
		//std::cout << "The path is as follows: " << table[end].path <<std::endl;
	}


	getchar();


	return 0;
}