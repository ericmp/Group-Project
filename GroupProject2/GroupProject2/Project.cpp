#include "LockFreeQueue.h"
#include <pthread.h>
#include <thread>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>


struct TableEntry {
	std::atomic<int> currLowestValue = 0;
	std::string path;
};

std::atomic<TableEntry> *table;
LockFreeQueue queue;
int target;
std::vector<Node> nodes;


void solvePath() {
	Node *currNode = new Node();

	do {
		memcpy(currNode, queue.Dequeue(), sizeof(Node*));
		if (currNode->value < table[currNode->name].load().currLowestValue)
			table[currNode->name].load().currLowestValue.store(currNode->value);
		if (!currNode->neighbors.empty()) {
			for each (GraphEdge x in currNode->neighbors) {
				queue.Enqueue(new Node(nodes[x.ID].value + x.weight));
			}
		}
	} while (currNode->name != target);

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
	table = new std::atomic<TableEntry>[numNodes + 1];

	nodes.reserve(numNodes + 1);

	//Place all nodes in the array
	while (input >> edge1 >> edge2 >> weight) {
		//Get the next set of nodes and edge
		GraphEdge temp1(edge2, weight), temp2(edge1, weight);
		nodes[edge1].Place(edge1, temp1);
		nodes[edge2].Place(edge2, temp2);


	}

	//Sort each node, except for those where there is no value
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].name = i;
		if (nodes[i].filled)
			nodes[i].neighbors.sort(lessThanNeighbor());
	}

	//At this point, we have a vector of graphs, who each have a list of neighbors sorted from least distance to greatest distance
	//so let's get started with the path finding

	//Enqueue starting node
	queue.Enqueue(&nodes[start]);

	std::thread *threads[8];
	//for (int i = 0; i < 8; i++) {
	//	threads[i] = new std::thread(solvePath);
	//}
	threads[0] = new std::thread(solvePath);

	getchar();
	return 0;
}