#include "LockFreeQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <iomanip>
#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>


struct NodeThread {

};

struct TableEntry {
	int currLowestValue = 0;

};

struct GraphEdge {
	int ID;
	int weight;
	GraphEdge() {};
	GraphEdge(int a, int b) : ID(a), weight(b) {};
};

struct GraphNode {
	int name = -1;
	std::list<GraphEdge> neighbors;
	GraphNode() {}
	void Place(GraphEdge a) { neighbors.push_back(a); }
};


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
	int numNodes, numEdges, edge1, edge2, weight;


	//Open the file
	input.open("input.txt");

	//Get number of nodes and number of edges
	input >> numNodes >> numEdges;

	std::vector<GraphNode> nodes(numNodes);

	//Place all nodes in the array
	while (input >> edge1 >> edge2 >> weight) {
		//Get the next set of nodes and edge
		GraphEdge temp1(edge2, weight), temp2(edge1, weight);

		nodes[edge1].Place(temp1);
		nodes[edge2].Place(temp2);
	}

	//Sort each node, except for those where there is no value
	for each (GraphNode x in nodes)
		if (x.name != -1)
			x.neighbors.sort(lessThanNeighbor());

	//At this point, we have a vector of graphs, who each have a list of neighbors sorted from least distance to greatest distance


	getchar();
	return 0;
}