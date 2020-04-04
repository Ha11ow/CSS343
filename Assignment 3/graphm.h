#pragma once
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip>
#include <sstream>
/*
Author: Ben Khabazan
*/

using namespace std;


class GraphM
{
public:
	GraphM();

	void buildGraph(ifstream& infile);
	void insertEdge(int firstNode, int secondNode, int distance);
	void removeEdge(int firstNode, int secondNode);
	void findShortestPath();
	void displayAll();
	void display(int start, int end);

private:

	struct TableType {
		bool visited;
		int dist;
		int path;
	};

	const static int MAX_NODES = 101;
	TableType table[MAX_NODES][MAX_NODES];
	NodeData data[MAX_NODES];
	int cost[MAX_NODES][MAX_NODES];
	int size;

	int findNext(TableType data[]);
	void printPath(int firstNode, int secondNode);
	void printPathName(int firstNode, int secondNode);
};

