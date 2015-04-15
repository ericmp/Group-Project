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
#include <vector>


struct NodeThread {

};

struct GraphEdge {
	int ID;
	int weight;
	GraphEdge() {};
	GraphEdge(int a, int b) : ID(a), weight(b) {};
};

struct GraphNode {
	std::vector<GraphEdge> neighbors;
	GraphNode() { neighbors.resize(10); }
};



int main()
{
	std::ifstream input;
	int numNodes, numEdges, edge1, edge2, weight;


	//Open the file
	input.open("input.txt");

	//Get number of nodes and number of edges
	input >> numNodes >> numEdges;

	GraphNode* nodes = new GraphNode[numNodes];

	//Place all nodes in the array
//	while (input >> edge1 >> edge2 >> weight) {
	input >> edge1 >> edge2 >> weight;
	GraphNode first = nodes[edge1];
	GraphNode second = nodes[edge2];
	
		GraphEdge temp1(edge2, weight), temp2(edge1, weight);
		
		if (first.neighbors.size() == first.neighbors.capacity()) {
			first.neighbors.resize(first.neighbors.size() + 10);
		}
		if (second.neighbors.size() == second.neighbors.capacity()) {
			second.neighbors.resize(second.neighbors.size() + 10);
		}

		first.neighbors.push_back(temp1);
		second.neighbors.push_back(temp2);
		std::cout << nodes[5].neighbors[0].ID;
		
	//}
	


	getchar();
	return 0;
}