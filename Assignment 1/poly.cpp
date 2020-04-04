#include "poly.h"

/*
Author: Ben Khabazan
*/

Poly::Poly()
{
	storage = new int[1];
	storage[0] = 0;
	size = 1;
}

Poly::Poly(int coefficient)
{
	storage = new int[1];
	storage[0] = coefficient; //only one item needed
	size = 1;
}

Poly::Poly(int coefficient, int exponent)
{
	if (exponent >= 0) { //cant be negative


		storage = new int[exponent + 1];
		size = exponent + 1;
		for (int i = 0; i < exponent; i++) { //setting values to 0
			storage[i] = 0;
		}
		storage[exponent] = coefficient;
	}
	else {
		//throw "Exponent cannot be smaller than 0";
		return;
	}
}

Poly::Poly(const Poly& p) //copy constructor
{
	this->size = p.size;
	this->storage = new int[size];
	for (int i = 0; i < size; i++) { //deep copy
		this->storage[i] = p.storage[i];
	}
}

Poly::~Poly()
{
	size = 0;
	delete[] storage; //delete then set to null
	storage = NULL;
}

int Poly::display() //persoanl usage, not required
{
	int temp = 0;
	for (int i = 0; i < size; i++) {
		cout << "index: " << i << " coef: " << storage[i] << endl;
	}
	return temp;
}

int Poly::getCoeff(int exponent)//returns a coeff by getting expo
{
	if (exponent >= 0 && exponent < size) { //invarients checked
		return storage[exponent];
	}
	else {
		//throw "Index out of bounds, Exponent does not exist.";
		return 0;
	}
}

void Poly::setCoeff(int coefficient, int exponent)
{
	if (exponent >= 0 && exponent < size) { //replacing a coeff
		storage[exponent] = coefficient;
	}
	else if (exponent >= size) { //adding a coeff
		int* newArray = new int[exponent + 1];
		
		
		for (int i = 0; i < size; i++)
		{
			newArray[i] = storage[i];
		}
		

		for (int i = size; i < exponent; i++) {
			newArray[i] = 0;
		}
		newArray[exponent] = coefficient;
		delete[] storage;
		size = exponent + 1;
		storage = newArray;
	}
	else { //invarients check
		//throw "Exponent must be bigger than 0";
		return;
	}
}

bool Poly::operator==(const Poly& p) const //matching if equal
{
	if (this->size != p.size) { //size must be the same
		return false;
	}
	for (int i = 0; i < size; i++) { //check every index
		if (p.storage[i] != this->storage[i]) {
			return false;
		}
	}
	return true;
}

bool Poly::operator!=(const Poly& p) const
{
	if (this->size != p.size) { //size must not be the same
		return true;
	}
	for (int i = 0; i < size; i++) { //one index must be different
		if (p.storage[i] != this->storage[i]) {
			return true;
		}
	}
	return false;
}

Poly& Poly::operator=(const Poly& p)
{
	if (*this == p) {
		return *this;
	}
	delete[] storage; //delete current storage
	this->size = p.size; //resize
	this->storage = new int[size]; //new storage
	for (int i = 0; i < size; i++) { //insert every element
		this->storage[i] = p.storage[i];
	}
	return *this;
}

Poly Poly::operator+(const Poly& p) const
{
	Poly temp = Poly(0, this->size - 1); //new temp to return
	for (int i = 0; i < min(size, p.size); i++) {
		temp.setCoeff(storage[i] + p.storage[i], i); //copy everything till one array is done

	}
	if (this->size > p.size) { //if first array is bigger
		for (int i = min(size, p.size); i < max(size, p.size); i++) {
			temp.setCoeff(storage[i], i);
		}
	}
	else { //if second array is bigger
		for (int i = min(size, p.size); i < max(size, p.size); i++) {
			temp.setCoeff(p.storage[i], i);
		}
	}
	return temp;
}

Poly Poly::operator-(const Poly& p) const
{
	Poly temp = Poly(0, this->size - 1); 
	for (int i = 0; i < min(size, p.size); i++) { //copy everything till one array runs out
		temp.setCoeff(storage[i] - p.storage[i], i);

	}
	if (this->size > p.size) { //if this array is bigger
		for (int i = min(size, p.size); i < max(size, p.size); i++) {
			temp.setCoeff(storage[i], i); //set values 
		}
	}
	else {
		for (int i = min(size, p.size); i < max(size, p.size); i++) { //if other is bigger
			temp.setCoeff(-(p.storage[i]), i); //set negative values
		}
	}
	return temp;
}

Poly Poly::operator*(const Poly& p) const
{
	Poly retVal = Poly(0, (size + p.size - 2)); //this will be the returning value 
	Poly temp = Poly(0, (size + p.size - 2)); //this is to help calculate the multi
	for (int i = 0; i < size; i++) { //this is set to go through all elements of first array
		for (int j = 0; j < p.size; j++) { //this will go through all elements of second array
			temp.setCoeff(storage[i] * p.storage[j], i + j); //fills temp with multiplication at correct spots
		}
		retVal = retVal + temp; //sends a copy of every multiplication to the retVal 
		temp.clearArray(); //sets all elements to 0
	}
	return retVal; //returns retVal
}

Poly& Poly::operator+=(const Poly& p)
{
	for (int i = 0; i < min(size, p.size); i++) {
		storage[i] += p.storage[i];
	}
	if (this->size < p.size) {
		for (int i = min(size, p.size); i < max(size, p.size); i++) {
			setCoeff(p.storage[i], i);
		}
	}
	return *this;
}

Poly& Poly::operator-=(const Poly& p)
{
	for (int i = 0; i < min(size, p.size); i++) {
		storage[i] -= p.storage[i];

	}
	if (this->size < p.size) {
		for (int i = min(size, p.size); i < max(size, p.size); i++) {
			setCoeff(-(p.storage[i]), i);
		}
	}
	return *this;
}

Poly& Poly::operator*=(const Poly& p)
{
	Poly retVal = Poly(0, (size + p.size - 2));
	Poly temp = Poly(0, (size + p.size - 2));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < p.size; j++) {
			temp.setCoeff(storage[i] * p.storage[j], i + j);
		}
		retVal = retVal + temp;
		temp.clearArray();
	}
	
	this->clearArray();
	for (int i = 0; i < retVal.size; i++) {
		this->setCoeff(retVal.storage[i], i);
	}
	
	return *this;
	
	/*
	* this = *this * p;
	return *this;
	*/

}

void Poly::clearArray()
{
	for (int i = 0; i < size; i++) {
		storage[i] = 0;
	}
}

