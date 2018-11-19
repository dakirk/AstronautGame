#include <iostream>
#include <cmath>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Person.h"
#include "Alien.h"

using namespace std;

Alien::Alien() : Game_Object('X') {
	attack_strength = 2;
	range = 2.0;
	target = NULL;
	speed = 5;
	cout << "Alien default constructed." << endl;
}

Alien::Alien(int in_id, Cart_Point in_loc) : Game_Object(in_loc, in_id, 'X') {
	attack_strength = 2;
	range = 2.0;
	target = NULL;
	speed = 5;
	cout << "Alien constructed." << endl;
}

void Alien::setup_destination(Cart_Point dest) {
	destination = dest; //soft-copy dest to destination
	Cart_Vector deltaVect = destination - location; //calculate first part of equation
	double unitSpeed = speed/cart_distance(destination, location); //calculate second part of equation
	delta = deltaVect * unitSpeed; //put them together

	//cout << delta << endl;
}

void Alien::start_moving(Cart_Point dest) {

	setup_destination(dest);

	//set state and print it
	state = 'm';
	cout << "Moving " << id_num << " to " << destination << "." << endl;
}

bool Alien::update_location() {

	//cout << location << endl;

	if (destination.x == location.x && destination.y == location.y) { //if already there
		//cout << display_code << id_num << ": I'm there!" << endl;
		return true;
	} else {
		Cart_Vector distanceRemaining = destination - location;

		if (fabs(distanceRemaining.x) <= fabs(delta.x) && fabs(distanceRemaining.y) <= fabs(delta.y)) { //if within one step of destination
			location.x = destination.x; //set x to destination x
			location.y = destination.y; //set y to destination y
			//cout << display_code << id_num << ": I'm there!" << endl;
			return true;
		} else {
			location.x = location.x + delta.x; //increments location's x-coordinate by delta's y-coordinate
			location.y = location.y + delta.y; //increments location's y-coordinate by delta's y-coordinate
			//cout << display_code << id_num << ": step..." << endl;
			return false;
		}
	}
}

void Alien::stop() {
	state = 's';
}

void Alien::start_attack(Person* in_target) {
	
	if (cart_distance(in_target->get_location(), location) <= 2) {
		cout << "Smash!" << endl;
		target = in_target;
		state = 'a';
	} else {
		cout << "Target out of range." << endl;
	}
}

void Alien::show_status() {
	cout << "Alien status: " << display_code << id_num << " at (" << location.x << ", " << location.y << ")" << endl;
}

bool Alien::update() {

	bool returnVal = false;
	switch(state) {
		case 's': {
			break;
		}
		case 'm': {
			bool arrived = update_location();
			if (arrived) {
				state = 's';
			}
			break;
		}
		case 'a': {
			if (cart_distance(target->get_location(), location) <= 2) {
				if (target->is_alive()) {
					cout << "Destroy!" << endl;
					target->take_hit(attack_strength);
				} else {
					cout << "I triumph!" << endl;
					state = 's';
					returnVal = true;
				}
			} else {
				state = 's';
			}
		}
	}

	return returnVal;
}

Alien::~Alien() {
	cout << "Alien destructed." << endl;
}