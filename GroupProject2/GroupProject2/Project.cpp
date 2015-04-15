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


using namespace std;

struct NodeThread {

};

struct GraphNode {
	vector<GraphEdge> neighbors;
};

struct GraphEdge {
	int ID;
	int weight;
	GraphEdge(int a, int b) : ID(a), weight(b) {};
};


int main()
{
	ifstream input;
	int numNodes, numEdges, edge1, edge2, weight;


	//Open the file
	input.open("input.txt");

	//Get number of nodes and number of edges
	input >> numNodes >> numEdges;

	GraphNode* nodes = new GraphNode[numNodes];

	//Place all nodes in the array
	while (input >> edge1 >> edge2 >> weight) {
		GraphEdge temp1(edge2, weight), temp2(edge1, weight);
		nodes[edge1].neighbors.push_back(temp1);
		nodes[edge2].neighbors.push_back(temp2);
	}



	getchar();
	return 0;
}