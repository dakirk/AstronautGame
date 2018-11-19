#include <iostream>
#include <cmath>
#include "Cart_Vector.h"

using namespace std;

//overloads multiplication operator to return each coord multiplied by d
Cart_Vector operator * (Cart_Vector &v1, double d) {
	Cart_Vector returnVect( (v1.x * d), (v1.y * d) );
	return returnVect;
}

//overloads division operator to return each coord divided by d
Cart_Vector operator / (Cart_Vector &v1, double d) {
	if (d == 0) { //if dividing by zero
		return v1;
	} else {
		Cart_Vector returnVect( (v1.x / d), (v1.y / d) );
		return returnVect;
	}
}

//overloads output stream operator to return formatted string
ostream& operator << (std::ostream &os, Cart_Vector &vector) {
	os << "<" << vector.x << ", " << vector.y << ">";
	return os;
}

Cart_Vector::Cart_Vector() {
	x = 0;
	y = 0;
}

Cart_Vector::Cart_Vector(double inputx, double inputy) {
	x = inputx;
	y = inputy;
}