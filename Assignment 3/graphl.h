#pragma once
#pragma once
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip>
/*
Author: Ben Khabazan
*/

class GraphL
{
public:
	GraphL();
	~GraphL();
	void buildGraph(ifstream& infile);
	void displayGraph();
	void depthFirstSearch();

private:
	const static int MAX_NODES = 101;
	struct EdgeNode {
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};
	struct GraphNode { 
		bool visited;  // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead;  // head of the list of edges
		NodeData data;  // data information about each node
	};
	GraphNode adjList[MAX_NODES]; //list of nodes
	int size;
	void searchHelper(int node);
	void insertEdge(int firstNode, int secondNode);
};

