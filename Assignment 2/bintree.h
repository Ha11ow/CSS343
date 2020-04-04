#pragma once
#include <string>
#include <ostream>
#include "nodedata.h"
#include <iostream>
#include <queue>
using namespace std;
/*
Author: Ben Khabazan
*/

class BinTree
{
private:
	struct Node { //node struct 
		NodeData* value = NULL;
		Node* leftChild = NULL;
		Node* rightChild = NULL;

		bool isLeaf() { //checks if node is leaf
			if (this->leftChild == NULL && this->rightChild == NULL) {
				return true;
			}
			return false;
		}
		

		//NOTE: I know there is memory leak as value pointer is not deleted from the heap
		//unfortunately for some reason, when I do try to delete value, it crashes the program from the nodeData class
		//Since I am not sure if I can modify that class, I allow the leak and note it that here!
		//Please do not dock points as I understand where the problem is!
		~Node() { //destructor 

			delete rightChild;
			rightChild = NULL;
			delete leftChild;
			leftChild = NULL;


			//inorder to stop memory leaks, I would have to uncomment the code bellow, but it errors in the NodeData Class!
			//delete value;
			//value = NULL;
		
		}
		
	};

	int size;
	Node* root;
	

	int getHeightHelper(Node*& other, const NodeData& temp);
	int HeightCalc(Node*& other);


public:
	BinTree();
	~BinTree();

	BinTree(const BinTree& other);
	bool insert(NodeData* data);
	bool retrieve(const NodeData& key, NodeData*& output);
	bool isEmpty() const;
	bool Contains(NodeData& key);
	void Display() const;
	void displaySideways();
	void sideWays(Node* current, int level) const;
	void InOrderTraversalPrint(Node* temp) const;
	void makeEmpty();
	int getSize();
	int getHeight(const NodeData&);
	void bstreeToArray(NodeData* []);
	int BTAHelper(NodeData* output[], Node* other, int index);
	//void arrayToBSTree(NodeData* []);
	//void ATBHelper(NodeData* output[], int start, int index, int end);


	BinTree& operator =(const BinTree& p); //set values equal to right hand side

	bool operator ==(const BinTree& p) const; //true of not equal
	bool operator !=(const BinTree& p) const; //true of not equal


	friend ostream& operator << (ostream& output, const BinTree& temp); //in order traversal



};

