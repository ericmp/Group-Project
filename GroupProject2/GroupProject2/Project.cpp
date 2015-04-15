#include "LockFreeQueue.h"
#include <pthread.h>
#include <thread>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>


LockFreeQueue queue;

struct NodeThread {

};

struct TableEntry {
	int currLowestValue = 0;
	std::string path;


};



struct lessThanNeighbor
{
	inline bool operator() (const GraphEdge& struct1, const GraphEdge& struct2)
	{
		return (struct1.weight > struct2.weight);
	}
};



void solvePath() {

}




int main()
{
	std::ifstream input;
	int numNodes, numEdges, edge1, edge2, weight;


	//Open the file
	input.open("input.txt");

	//Get number of nodes and number of edges
	input >> numNodes >> numEdges;

	//Create an atomic table for the lowest weight value entries
	std::atomic<TableEntry> *table = new std::atomic<TableEntry>[numNodes+1];


	
	std::vector<Node> nodes(numNodes+1);

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
	

	
	getchar();
	return 0;
}