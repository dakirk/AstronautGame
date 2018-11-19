#ifndef CART_POINT_H
#define CART_POINT_H
#include "Cart_Vector.h"



class Cart_Point {
	public:
		double x;
		double y;
		Cart_Point();
		Cart_Point(double inputx, double inputy);
};

double cart_distance(Cart_Point p1, Cart_Point p2);
Cart_Point operator + (Cart_Point &p1, Cart_Vector &v2);
Cart_Vector operator - (Cart_Point &p1, Cart_Point &p2);
std::ostream& operator << (std::ostream &os, Cart_Point &point);
#endif