#include <iostream>
#include <cmath>
#include "Cart_Point.h"
#include "Cart_Vector.h"

using namespace std;

//calculates and returns distance between two points
double cart_distance(Cart_Point p1, Cart_Point p2) {
	return sqrt( pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) );
}

//overloads addition operator to add x and y coords individually
Cart_Point operator + (Cart_Point &p1, Cart_Vector &v2) {
	Cart_Point p3( (p1.x + v2.x), (p1.y + v2.y) );
	return p3;
}

//overloads subtraction operator to subtract x and y coords individually
Cart_Vector operator - (Cart_Point &p1, Cart_Point &p2) {
	Cart_Vector v3( (p1.x - p2.x), (p1.y - p2.y) );
	return v3;
}

//overloads output stream operator to return formatted string
ostream& operator << (std::ostream &os, Cart_Point &point) {
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

Cart_Point::Cart_Point() {
	x = 0.0;
	y = 0.0;
}

Cart_Point::Cart_Point(double inputx, double inputy) {
	x = inputx;
	y = inputy;
}