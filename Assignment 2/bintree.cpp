#include "bintree.h"
/*
Author: Ben Khabazan
*/

//empty constuctor initilizing variables
BinTree::BinTree()
{
	this->size = 0;
	this->root = NULL;
}

//destructor calling delete root (modified delete for struct Node)
BinTree::~BinTree()
{
	delete root; //custom destructor created for the Node in .h file
}

//a deep copy constructor
BinTree::BinTree(const BinTree& other)
{
	delete root; //empty the tree first
	root = NULL;
	size = 0;
	queue <Node*> myQ;
	myQ.push(other.root); //start the Queue with root
	while (!myQ.empty()) { //empty the Queue
		if (myQ.front() != NULL) {
			insert(myQ.front()->value); //insert value 
			myQ.push(myQ.front()->leftChild); //add children
			myQ.push(myQ.front()->rightChild);
			
		}
		myQ.pop();
	}
	this->size = other.size;
}

//insert is where a NodeData object is inputted into the correct position of a tree
//boolean return indicates if item was inserted or not
bool BinTree::insert(NodeData* input)
{
	if (this->isEmpty()) { //if empty make it the root
		Node* temp = new Node; //creating a new node
		temp->value = input;
		this->root = temp;
		this->size++;
		return true;
	}
	Node* currentNode = this->root;
	while (currentNode != NULL) {

		if (*input == *currentNode->value) { //false when data already exists
			return false;
			
		}
		else if (*input < *currentNode->value) { //left child is less
			if (currentNode->leftChild == NULL) { //if empty set it
				Node* temp = new Node; //creating a new node
				temp->value = input;
				currentNode->leftChild = temp;
				break;
			}
			else {
				currentNode = currentNode->leftChild;
			}
		}
		else { //right child is more and the only thing left
			if (currentNode->rightChild == NULL) {//if empty set
				Node* temp = new Node; //creating a new node
				temp->value = input;
				currentNode->rightChild = temp;
				break;
			}
			else {
				currentNode = currentNode->rightChild;
			}
		}
	}

	this->size++; //increase size
	return true;
}


//retrieve takes in a key value and finds it within the tree and uses the second variable as output
//boolean return indicates if item was found within the tree or not
bool BinTree::retrieve(const NodeData& key, NodeData*& output)
{
	Node* currentNode = this->root;
	while (currentNode != NULL) {
		if (*(currentNode->value) == key) {

			output = currentNode->value;

			return true;
		}
		if (*currentNode->value > key) {
			currentNode = currentNode->leftChild;
		}
		else {
			currentNode = currentNode->rightChild;
		}
	}
	return false;
}

//returns if array is empty or not
bool BinTree::isEmpty() const
{
	return (this->size == 0 && this->root == NULL);
}

//returns the size of the array
int BinTree::getSize()
{
	return this->size;
}

//returns the int for the height of the NodeData. if doesnt exist its 0
int BinTree::getHeight(const NodeData& key) 
{
	if (root == NULL) { //empty tree is size 0
		return 0;
	}
	return getHeightHelper(root, key);
}

//helper method that recursively finds the value for height
int BinTree::getHeightHelper(Node*& other, const NodeData& key)
{
	if (other == NULL) { //item not found
		return 0;
	}
	if (*other->value == key) { //found item

		return HeightCalc(other); //helper method
	}
	int leftHeight = getHeightHelper(other->leftChild, key);
	int rightHeight = getHeightHelper(other->rightChild, key);

	if (leftHeight > rightHeight) { //returns bigger item as others should be 0
		return leftHeight;
	}
	if (rightHeight > leftHeight) {
		return rightHeight;
	}
	return 0;
}

//calculates height of the node given
int BinTree::HeightCalc(Node*& other)
{
	if (other == NULL) { //reched 0
		return 0;
	}
	int rightH = HeightCalc(other->rightChild); //tries left 
	int leftH = HeightCalc(other->leftChild); //tries right 
	if (leftH > rightH) { //compares value
		return leftH + 1; //adds 1 per layer to the value that is found
	}
	return rightH + 1;
	
}

//transforms the tree to an array
void BinTree::bstreeToArray(NodeData *output[])
{
	BTAHelper(output, root, 0); //calls helper method
	delete root;
	root = NULL;
	size = 0;
}

//helper method that takes the array and inserts a node at a correct spot
int BinTree::BTAHelper(NodeData* output[], Node* other, int index)
{
	if (other == NULL) {
		return index;
	}
	if (other != NULL && size > 0) {
		int next = BTAHelper(output, other->leftChild, index);
		output[next] = other->value;
		int final = BTAHelper(output, other->rightChild, ++next);
		return final;
	}
}

//assignement operator overload
BinTree& BinTree::operator=(const BinTree& other)
{
	if (&other != this) {
		delete root; //deletes existing tree
		root = NULL;
		size = 0;
		queue <Node*> myQ;
		myQ.push(other.root); //inserts everything using a Queue
		while (!myQ.empty()) {
			if (myQ.front() != NULL) {
				insert(myQ.front()->value);
				myQ.push(myQ.front()->leftChild);
				myQ.push(myQ.front()->rightChild);

			}
			myQ.pop();
		}
		this->size = other.size;
	}
	return *this;
}

//equals operator overload
bool BinTree::operator==(const BinTree& rhs) const
{
	if (root == NULL && rhs.root == NULL) { //if both null: true
		return true;
	}
	if (root != NULL && rhs.root != NULL) { //if both not null: manual check

		queue <Node*> thisQ; //two queues to travers both at the same time
		queue <Node*> otherQ;
		thisQ.push(root);
		otherQ.push(rhs.root);

		while ((!thisQ.empty()) && (!otherQ.empty())) { //empties queues
			if (thisQ.front() != NULL && otherQ.front() != NULL) { //if null: skip
				if (*thisQ.front()->value != *otherQ.front()->value) { //comparing values
					return false;
				}
				thisQ.push(thisQ.front()->leftChild); //add children
				thisQ.push(thisQ.front()->rightChild);
				otherQ.push(otherQ.front()->leftChild);
				otherQ.push(otherQ.front()->rightChild);
			}
			thisQ.pop();
			otherQ.pop();
		}
		return true;
	}
	return false;
}

//not equals operator overload
//code is the same for == check there for comments
bool BinTree::operator!=(const BinTree& rhs) const
{
	if (root == NULL && rhs.root == NULL) { //if both null: false
		return false;
	}
	if (root != NULL && rhs.root != NULL) {

		queue <Node*> thisQ;
		queue <Node*> otherQ;
		thisQ.push(root);
		otherQ.push(rhs.root);

		while ((!thisQ.empty()) && (!otherQ.empty())) {
			if (thisQ.front() != NULL && otherQ.front() != NULL) {
				if (*thisQ.front()->value != *otherQ.front()->value) {
					return true;
				}
				thisQ.push(thisQ.front()->leftChild);
				thisQ.push(thisQ.front()->rightChild);
				otherQ.push(otherQ.front()->leftChild);
				otherQ.push(otherQ.front()->rightChild);
			}
			thisQ.pop();
			otherQ.pop();
		}
		return false;
	}
	return true;
}

//contains method checks to see if NodeData key exists in the tree
bool BinTree::Contains(NodeData& key)
{
	Node* currentNode = this->root; //temp node
	while (currentNode != NULL) {
		if (*(currentNode->value) == key) { //if values are the same
			return true;
		}
		if (*currentNode->value > key) { //if key is smaller check left
			currentNode = currentNode->leftChild;
		}
		else { //check right
			currentNode = currentNode->rightChild;
		}
	}
	return false;
}

// prints all the data in an in order traversal
void BinTree::Display() const
{
	Node* temp = this->root;
	InOrderTraversalPrint(temp);
}

//display sideways prints out the array in a tree format
void BinTree::displaySideways()
{
	this->sideWays(root, 0);
}

//helper method to print out the data in tree format
void BinTree::sideWays(Node* current, int level) const
{
	if (current != NULL && size > 0) {
		level++;
		sideWays(current->rightChild, level);
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}
		cout << *current->value << endl;
		sideWays(current->leftChild, level);
	}
}

//an in order traversal to print the nodes with a space in between
void BinTree::InOrderTraversalPrint(Node* temp) const
{
	if (temp != NULL && size > 0) {
		this->InOrderTraversalPrint(temp->leftChild); //small first 
		cout << *temp->value << " "; //value
		this->InOrderTraversalPrint(temp->rightChild); //right last
	}
}

//empties the tree and sets root to NULL
void BinTree::makeEmpty()
{
	if (root != NULL) {
		delete root;
		root = NULL;
		size = 0;
	}
	return;

}

//printout operator overload that prints the tree in order traversal
ostream& operator<<(ostream& output, const BinTree& temp)
{
	temp.Display();
	cout << endl;
	return output;
}
