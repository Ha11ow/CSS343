#include "graphl.h"
/*
Author: Ben Khabazan
*/



GraphL::GraphL()
{
	this->size = 0;
	for (int i = 0; i < MAX_NODES; i++) { //initilize everything within the list
		adjList[i].edgeHead = NULL;
		adjList[i].visited = false;
	}
}


GraphL::~GraphL()
{
	if (size > 0) { //invariants
		for (int i = 1; i <= size; i++) { 
			EdgeNode* temp = adjList[i].edgeHead; //temp node to point to the head

			while (temp != NULL) {
				EdgeNode* next = temp->nextEdge;  //simple swap delete
				delete temp;
				temp = next;
			}
			adjList[i].edgeHead = NULL;
			adjList[i].visited = false;
		}
		size = 0;
	}
}

void GraphL::buildGraph(ifstream& infile)
{
	infile >> size; //set size
	if (infile.eof()) {
		return;
	}

	string name;
	int firstNode, secondNode;

	getline(infile, name);
	
	for (int i = 0; i < size; i++) {
		getline(infile, name); //get the name out of file
		adjList[i].data = NodeData(name); //set the name within the data 
	}

	infile >> firstNode >> secondNode;

	while (firstNode != 0) { //if first input is 0, it will stop the loop
		insertEdge(firstNode, secondNode); //adds the cost from firstnode to secondnode 
		infile >> firstNode >> secondNode; //grab next 3 ints
	}
}

void GraphL::displayGraph()
{
	cout << "Graph:" << endl;  
	for (int i = 1; i <= size; i++) {
		cout << "Node " << i << "\t\t" << adjList[i-1].data << endl;  //print name

		EdgeNode* temp = adjList[i].edgeHead; //temp to go through the edges 

		while (temp != NULL) {
			cout << setw(7) << "edge\t" << i << " " << temp->adjGraphNode << endl; //print attribute
			temp = temp->nextEdge; //set to next edge in line
		} //repeat for all edges
	} //repeat for all elements
	cout << endl;
}

void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";
	for (int i = 1; i <= size; i++) {
		if (adjList[i].visited == false) { //if its not visited yet
			searchHelper(i); 
		}
	}
	cout << "\n\n" << endl;
}

void GraphL::searchHelper(int index)
{
	EdgeNode* temp = adjList[index].edgeHead;
	adjList[index].visited = true;
	cout << index << " ";
	while (temp != NULL) { //goes through the nodes
		//if the nodes adjacent edges have not been visited, then go to that edge
		if (adjList[temp->adjGraphNode].visited == false) { 
			searchHelper(temp->adjGraphNode); //recursive call to go deeper
		}
		temp = temp->nextEdge;
	}
}

void GraphL::insertEdge(int firstNode, int secondNode)
{
	EdgeNode* temp = new EdgeNode; //temp new node
	temp->adjGraphNode = secondNode;
	temp->nextEdge = NULL;

	//insert to the head;
	EdgeNode* swap = adjList[firstNode].edgeHead; //holding the value of head
	adjList[firstNode].edgeHead = temp; //set edgehead as temp
	temp->nextEdge = swap; //add held values as nextedge
}




