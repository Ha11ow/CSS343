#pragma once
#include <iostream>;
#include <istream>
#include <cstdlib>
using namespace std;
/*
Author: Ben Khabazan
*/

class HashTable
{
private:
	static const int TABLE_SIZE = 4177;
	int collision;

	struct Node {
		string input;
		Node* next = NULL;
	};
	Node* holder[TABLE_SIZE];

public:
	HashTable();
	~HashTable();

	int hash(string key);
	void insert(string input);
	bool remove(string key);
	string retrieve(string key);
	int chainLength(int index);
	void clear();
	void output();

	friend ostream& operator << (ostream& output, const HashTable& temp) {
		output << "Printing Table Chains:\n";

		int retVal = 0;
		for (int i = 0; i < temp.TABLE_SIZE; i++) {
			Node* indexed = temp.holder[i];
			while (indexed != NULL) {
				retVal++;
				indexed = indexed->next;
			}
			output << "index: " << i << ", chain: " << retVal << endl;
			retVal = 0;
		}
		return output;
	}
};