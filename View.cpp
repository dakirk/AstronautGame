#include <iostream>
#include "Cart_Point.h"
//#include "Cart_Vector.h"
#include "Game_Object.h"
#include "View.h"

using namespace std;

View::View() {
	size = 11;
	scale = 2;
	//origin should default to (0,0)
	//cout << "view constructed" << endl;
}

void View::clear() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			grid[i][j][0] = '.';
			grid[i][j][1] = ' ';
		}
	}
}

void View::draw() {

	int scaleCount = (size*2); //counter for the vertical scale

	for (int i = 0; i < size; i++) { //draw contents
		scaleCount -= scale;

		//if scaleCount is divisible by 4, draw it
		if (i % (int)scale == 0) {
			cout << scaleCount;
			if (scaleCount < 10) {
				cout << " ";
			}
		} else cout << "  "; //else, draw spaces

		//draw elements of this row
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < scale; k++) {
				cout << grid[i][j][k];
			}
		}
		cout << endl;
	}

	//draw horizontal scale at bottom
	cout << "  ";
	for (int i = 0; i < size; i++) {

		if (i % (int)scale == 0) {
			cout << scaleCount;
			if (scaleCount < 10) cout << " ";
		} else {
			cout << "  ";
		}

		scaleCount += scale;
		
	}
	cout << endl;
}

void View::plot(Game_Object* ptr) {
	Cart_Point objLocation = ptr->get_location();
	int x, y;
	bool inView = get_subscripts(x, y, objLocation);
	//cout << x << y << endl;
	char objRep[2];
	if (inView) { //if on board
		ptr->drawself(objRep);
		
		if (grid[(size-1)-y][x][0] != '.') { //if 2 objects on same spot
			grid[(size-1)-y][x][0] = '*';
			grid[(size-1)-y][x][1] = ' ';
			//cout << "overlap" << endl;
		} else { //adds object to correct spot in matrix
			grid[(size-1)-y][x][0] = objRep[0];
			grid[(size-1)-y][x][1] = objRep[1];
		}
	}
}

bool View::get_subscripts(int &ix, int &iy, Cart_Point location) {
	// Cart_Vector diff;
	// Cart_Vector subscript;
	// diff = location-origin; //origin is 0,0, so subtracting it from location is pointless
	// subscript = diff/scale;

	//workaround to avoid using Cart_Vectors
	double diffX = location.x - origin.x;
	double diffY = location.y - origin.y;

	Cart_Point subscript(diffX/scale, diffY/scale);
	ix = (int)subscript.x;
	iy = (int)subscript.y;
	if (ix < size && iy < size) {
		return true;
	} else {
		cout << "An object is outside the display" << endl;
		return false;
	}
}