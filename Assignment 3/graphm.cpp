#include "graphm.h"
/*
Author: Ben Khabazan
*/

GraphM::GraphM()
{
	size = 0;
	for (int y = 0; y < MAX_NODES; y++) { //first node indexing
		for (int x = 0; x < MAX_NODES; x++) { //second node indexing
			table[y][x].dist = INT_MAX; //initilize all distance to max int
			table[y][x].path = 0; //set all paths to 0
			table[y][x].visited = false; //make every node unvisited

			cost[y][x] = INT_MAX; //make all costs max value
		}
	}
}

//takes in an ifstream file and disects its data out to build the graph
void GraphM::buildGraph(ifstream& infile)
{
	infile >> size; //first line is the size
	string name; 
	
	if (infile.eof()) {
		return;
	}
	getline(infile, name);
	for (int i = 0; i < size; i++) {
			//get the name out of file
		data[i].setData(infile); //set the name within the data 
	}

	int firstNode, secondNode, distance; //three inputs in a start
	infile >> firstNode >> secondNode >> distance;

	while (firstNode != 0) { //if first input is 0, it will stop the loop
		insertEdge(firstNode, secondNode, distance); //adds the cost from firstnode to secondnode 
		infile >> firstNode >> secondNode >> distance; //grab next 3 ints
	}	
}

//assuming correct inputs for inputs (smaller than size, bigger than 0)
void GraphM::insertEdge(int firstNode, int secondNode, int distance)
{
	if (firstNode > size) {
		return;
	}
	if (secondNode > size) {
		return;
	}
	if (firstNode != 0 && secondNode != 0) { //if either the first or second node are not 0
		cost[firstNode][secondNode] = distance; //set the distance 
	}
}

//assuming correct inputs for all inputs (smaller than size, bigger than 0)
void GraphM::removeEdge(int firstNode, int secondNode)
{
	cost[firstNode][secondNode] = INT_MAX; //removes the edge by setting it to max int (unreachable)
}

//finds the shortest path for the nodes within the map using djistras algorithm
void GraphM::findShortestPath()
{
	int shortPath = 0;
	for (int i = 1; i <= size; i++) { //i is the starting node
		table[i][i].dist = 0; //distance from i to itself is 0

		for (int j = 1; j <= size; j++) { //j loops to reach every child
			shortPath = findNext(table[i]); //finding the next smallest cost for path

			if (shortPath == -1) //if a shorter path was not found exit
				break;

			table[i][shortPath].visited = true; //visiting the path

			for (int k = 1; k <= size; k++) { //k is every possible node that can is linked

				//if node has not been visited and it is reachable 
				if (cost[shortPath][k] < INT_MAX && table[i][k].visited == false) {

					//if the distance from current node and upcoming node is smaller than the adjacent node
					if (table[i][shortPath].dist + cost[shortPath][k] < table[i][k].dist) {  

						table[i][k].dist = table[i][shortPath].dist + cost[shortPath][k]; //replace with smaller distance
						table[i][k].path = shortPath; //set as new path
					}
				}
			}
		}
	}

}

void GraphM::displayAll()
{
	if (size > 0) {
		cout << "Description\t From node   To node    Dijkstra's   Path\n";

		// prints out all the nodes and the needed data
		for (int start = 1; start <= size; start++)
		{
			// prints description, which is the source
			cout << data[start-1] << endl;

			// prints out the node number, distance, and paths
			for (int end = 1; end <= size; end++)
			{
				// distance will not print if its zero
				if (table[start][end].dist != 0) {
					// prints the from and to nodes
					cout << setw(23) << start << "." << setw(9) << end;

					// when distance is infinity
					if (table[start][end].dist == INT_MAX)
						cout << setw(13) << "----" << endl;

					// print in the correct alignment to the description, etc.
					else {
						cout << setw(13) << table[start][end].dist << setw(8);
						printPath(start, end);
						cout << endl;
					}
				}
			}
		}
		cout << "\n" << endl; //spacing for what comes after
	}
}

//assuming all inputs are correct (bigger than 0 and smaller than max size)
void GraphM::display(int start, int end)
{
	cout << setw(5) << start << "." << setw(5) << end; //print the selected nodes

	if (table[start][end].dist == INT_MAX) { //if the distance is not set
		cout << setw(9) << "----" << endl; //unreachable
		
	}
	// print in the correct alignment to the description, etc.
	else {
		cout << setw(9) << table[start][end].dist << setw(5); //dijkstras shortest dist and path
		printPath(start, end); //prints paths from the start to end
		cout << endl;
		printPathName(start, end); //prints the name of paths 
	}
	cout << endl;
}

int GraphM::findNext(TableType data[])
{
	int retVal = -1; //index for the next node initilized to -1 
	int shortestPath = INT_MAX; 

	for (int i = 1; i <= size; i++) {
		//if the node isnt visited next dist is smaller than current shortest
		if (data[i].visited == false && data[i].dist < shortestPath) { 
			shortestPath = data[i].dist; //set as new shortest path
			retVal = i; //keep track of the shortest path 
		}
	}
	return retVal;
}

void GraphM::printPath(int firstNode, int secondNode)
{
	//if the nodes arent the same, and path is not empty
	if (firstNode != secondNode && table[firstNode][secondNode].path > 0) { 
		printPath(firstNode, table[firstNode][secondNode].path); //recursive call down the path
	}
	cout << " " << secondNode; 
}

void GraphM::printPathName(int firstNode, int secondNode)
{
	//if the nodes arent the same, and path is not empty
	if (firstNode != secondNode && table[firstNode][secondNode].path > 0) {
		printPathName(firstNode, table[firstNode][secondNode].path); //recursive call down the path
	}
	cout << data[secondNode - 1] << endl;
}
