#pragma once
#include <istream>
#include <string>
#include <ostream>
#include <algorithm>
#include <iostream>
using namespace std;


/*
Author: Ben Khabazan
*/

class Poly
{
public:
	//constructors:
	Poly();  //default no params
	Poly(int coefficient); //only coeff, expo is 0
	Poly(int coefficient, int exponent); //coeff and expo given
	Poly(const Poly& p); //copy constructor
	~Poly(); //destructor

	//getters and setters:
	int getCoeff(int exponent); //returns coeff of the expo
	void setCoeff(int coefficient, int exponent); //sets coeff (resize array if needed)

	//operator overloads:
	bool operator==(const Poly& p) const; //true if equal
	bool operator!=(const Poly& p) const; //true of not equal

	Poly& operator=(const Poly& p); //set values equal to right hand side

	Poly operator+(const Poly& p) const; //addition
	Poly operator-(const Poly& p) const; //subtraction
	Poly operator*(const Poly& p) const; //multiplication 

	Poly& operator+=(const Poly& p);
	Poly& operator-=(const Poly& p);
	Poly& operator*=(const Poly& p);

	//output overload
	friend ostream& operator<< (ostream & output, const Poly & temp) {
		int tempSize = temp.size;
		for (int i = temp.size - 1; i > 1; i--) {
			
			if (temp.storage[i] > 0) {
				output << " +" << temp.storage[i] << "x^" << i;
			}
			else if (temp.storage[i] == 0 ){

			}
			else {
				output << " " << temp.storage[i] << "x^" << i;
			}
		}
		if (temp.size >= 2) {
			if (temp.storage[1] > 0) {
				output << " +" << temp.storage[1] << "x";
			}

			else if (temp.storage[1] < 0) {
				output << " " << temp.storage[1] << "x";
			}
		}
		if (temp.size >= 1) {
			if (temp.storage[0] > 0) {
				output << " +" << temp.storage[0];
			}

			else if (temp.storage[0] < 0) {
				output << " " << temp.storage[0];
			}
		}
		return output;
	}

	//input overload
	friend istream& operator>>(istream& input, Poly& temp) {
		cout << "Enter one coefficient and one exponent repeatedly. Enter -1 for both to stop: ";
		
		while (true) {
			int inCoef = 0;
			int inExpo = 0;
			input >> inCoef;
			input >> inExpo;
			if ((inCoef == -1) && (inExpo == -1)) {
				break;
			}
			temp.setCoeff(inCoef, inExpo);
		}
		return input;
	}


private:
	int* storage; //memory allocated array
	int size = 0; //size of the memory
	void clearArray(); //sets all values of array to 0
	int display(); //personal usage to see all values including 0s
};

