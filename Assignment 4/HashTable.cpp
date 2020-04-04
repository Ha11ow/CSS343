#include "HashTable.h"
/*
Author: Ben Khabazan
*/

HashTable::HashTable()
{
	collision = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		holder[i] = NULL;
	}

}

HashTable::~HashTable()
{
	clear();
	cout << collision << endl;
}


/*
//+++++++++++++++++++|| addition hashValue||+++++++++++++++++++++++
int HashTable::hash(string key) 
{
	int hashValue = 0;
	for (int i = 0; i < key.size(); i++) {
		hashValue += int(key[i]);
	}

	return hashValue % TABLE_SIZE;
}
*/

/*
//+++++++++++++++++++|| multiplication hashValue||+++++++++++++++++++++++
int HashTable::hash(string key)
{
	long hashValue = 1;
	int temp = 0;
	for (int i = 0; i < key.size(); i++) {
		temp = int(key[i]);

		if (temp != 0) {
			//cout << temp << " " << hashValue << endl;
			if (hashValue == 2147483647 || hashValue == -2147483648) {
				hashValue /= temp * i;
			}
			else {
					hashValue *= temp;
					hashValue /= i + 2;
			}
		}
		else {
			hashValue += 1;
		}
	}
	hashValue %= TABLE_SIZE;
	hashValue = abs(hashValue);

	return hashValue;
}
*/


//+++++++++++++++++++|| SDBM hashValue||+++++++++++++++++++++++
int HashTable::hash(string key)
{
	unsigned long hash = 0;
	int c = 0;
	while (c != key.size()+1) {
		int temp = int(key[c]);
		temp -= 17;

		hash = temp + (hash << 6) + (hash << 16) - hash;
	
		c++;
	}
	return hash % TABLE_SIZE;
}


void HashTable::insert(string input)
{
	int index = hash(input); //retrieve the hashed index

	Node* ins = new Node; //node to be inserted
	//initilized
	ins->input = input;

	if (holder[index] == NULL) { //if not collided
		holder[index] = ins; //insert at hashed index
	}
	else { //case collision
		collision++; //collision counter ++
		Node* temp = holder[index]; //looper node
		while (temp->next != NULL) { //reach the end of the linked list
			temp = temp->next; 
		}
		temp->next = ins; //insert at the end of list
	}
}

bool HashTable::remove(string key)
{
	int index = hash(key); //find hashed index

	Node* temp = holder[index]; //temp value to go through list
	while (temp != NULL) { //loops till temp = null
		if (temp->input == key) { //if Node is found
			Node* found = temp->next; //keep hold of next item
			delete temp; //delete current item
			temp = found; //set current to next
			return true; //stop the loop
		}
	}
	return false; //not found
}

string HashTable::retrieve(string key)
{
	int index = hash(key); //find the index
	
	Node* temp = holder[index]; //set temp the the first Node
	while (temp != NULL) { //while Node is not empty
		if (temp->input == key) { //if the correct Node
			return holder[index]->input; //return
		}
		temp = temp->next; //select next Node
	}
	return ""; //not found
}

int HashTable::chainLength(int index)
{
	int retVal = 0;
	if (index >= 0 && index < TABLE_SIZE) {
		Node* temp = holder[index];
		while (temp != NULL) {
			retVal++;
			temp = temp->next;
		}
	}
	return retVal;
}

void HashTable::clear()
{
	for (int i = 0; i < TABLE_SIZE; i++) { //go through all indecies
		while (holder[i] != NULL) { //loops through to the end of the list
			Node* temp = holder[i]->next; //keeps hold of the next Node
			delete holder[i]; //deletes current Node
			holder[i] = temp; //sets current to next Node
		}
	}
}

void HashTable::output()
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		cout << "index: " << i << ", Chain: " << this->chainLength(i) << endl;
	}
}

