

// DO NOT change anything in this file. Your code must compile and give the
// correct output with this main on the linux machines.

// Make sure the file containing the member function source is: poly.cpp
// Use all lowercase in the file names.

// This main does not do a thorough job of testing.  When testing arrays,
// be sure to test the middle and also all the boundary conditions.  Test
// values on the boundary and outside the boundaries, i.e., too big/small.

#include "poly.h"
#include <iostream>
using namespace std;

//two tests, one is yours with preset values, other is mine (modified of yours to test memory leaks)


int main() {
	Poly A = Poly(-2, 0);
	A.setCoeff(5, 7);
	A.setCoeff(-4, 3);
	A.setCoeff(10, 1);

	Poly B = Poly(1, 3);
	B.setCoeff(3, 4);

	Poly  C(2), D(A), X, Y;
	Poly A2, B2, Z1, Z2;



	// or use a bunch of setCoeff

// outputs exactly what is in quotes: "A = +5x^7 -4x^3 +10x -2"
	cout << "A =" << A << endl;
	// outputs exactly what is in quotes: "B = +3x^4 +1x^3"
	cout << "B =" << B << endl << endl;


	A2 = A;
	B2 = B;
	C = A + B;
	cout << "Compute C = A + B: " << C << endl << endl;

	cout << ((A == B) ? "A == B" : "A is not == B") << endl;
	cout << ((A != B) ? "A is not == B" : "A == B") << endl << endl;

	Z1 = A2 - B2;
	cout << "Compute  Z1 = A2 - B2: " << Z1 << endl;
	Z2 = B2 - A2;
	cout << "Compute  Z2 = B2 - A2: " << Z2 << endl << endl;

	cout << "Compute  D = A * B - 15" << endl;
	cout << "Before: D =" << D << endl;
	D = A * B - 15;
	cout << "After:  D =" << D << endl << endl;

	cout << "Test assignment operators" << endl;
	X = C = D = D;
	Y += A -= B *= A;

	cout << "X =" << X << endl;
	cout << "Y =" << Y << endl << endl;

	cout << "Get and Set coefficient" << endl;
	int coeff = D.getCoeff(0);
	cout << "coeff of subscript 0 of D is: " << coeff << endl;
	cout << "Doing getCoeff for term -20000" << endl;
	coeff = D.getCoeff(-20000);              // handle value out of range
	D.setCoeff(50, 0);                        // set x^0 coeff to 50
	D.setCoeff(50, 20000);                    // set x^20000 coeff to 50
	cout << "D =" << D << endl << endl;

	return 0;
}


/*
int main() {

	while (true) {
		Poly A = Poly(-2, 0);
		A.setCoeff(5, 7);
		A.setCoeff(-4, 3);
		A.setCoeff(10, 1);

		Poly B = Poly(1, 3);
		B.setCoeff(3, 4);

		Poly C = A + B;

		cout << "Polynomial A =" << A << endl;
		cout << "Polynomial B =" << B << endl;
		cout << "\n" << endl;

		cout << "Polynomial C = A + B =" << C << endl;
		cout << "\tCurrent Answer = +5x^7 +3x^4 -3x^3 +10x -2\n\n" << endl;

		cout << "Polynomial A is";
		if (A == B) {
			cout << " equal to B\n\n" << endl;
		}
		if (A != B) {
			cout << " not equal to B\n\n" << endl;
		}

		Poly Z1 = Poly();
		Z1 = A - B;

		cout << "Polynomial Z1 = A - B =" << Z1 << endl;
		cout << "\tCurrent Answer = +5x^7 -3x^4 -5x^3 +10x -2\n\n" << endl;

		Poly Z2 = Poly();
		Z2 = B - A;

		cout << "Polynomial Z2 = B - A =" << Z2 << endl;
		cout << "\tCurrent Answer = -5x^7 +3x^4 +5x^3 -10x +2\n\n" << endl;

		Poly D = A * B - 15;
		cout << "Polynomial D = A * B - 15 =" << D << endl;
		cout << "\tCurrent Answer = +15x^11 +5x^10 -12x^7 -4x^6 +30x^5 +4x^4 -2x^3 -15\n\n" << endl;

		cout << "coeff of subscript 0 of D is:" << D.getCoeff(0) << endl;
		cout << "\n" << endl;

		cout << "set coeff of subscript -2000 to 50:";
		D.setCoeff(50, -2000);
		cout << D << endl;
		cout << "\n" << endl;

		cout << "coeff of subscript -2000 of D is:" << D.getCoeff(-2000) << endl;
		cout << "\n" << endl;

	}
}
*/