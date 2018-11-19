#include <iostream>
#include <math.h>
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Person.h"

using namespace std;

int Person::num_live_people = 0;

Person::Person() : Game_Object('P') { //default constructor
	speed = 5.0;
	health = 5;
	num_live_people++;
	cout << "Person default constructed." << endl;
}

Person::Person(char in_code) : Game_Object(in_code) {
	speed = 5.0;
	health = 5;
	num_live_people++;
	cout << "Person constructed." << endl;
}

Person::Person(Cart_Point in_loc, int in_id, char in_code) : Game_Object(in_loc, in_id, in_code) {
	speed = 5.0;
	health = 5;
	num_live_people++;
	cout << "Person constructed." << endl;
}

void Person::start_moving(Cart_Point dest) {

	if (state != 'l' && state != 'x') { //only moves if not locked
		setup_destination(dest);

		//set state and print it
		state = 'm';
		cout << "Moving " << id_num << " to " << destination << "." << endl;
		cout << display_code << id_num << ": On my way." << endl;
	} else if (state == 'l') {
		cout << display_code << id_num << ": I'm locked." << endl;
	} else {
		cout << display_code << id_num << " is dead." << endl;
	}

}

void Person::stop() {
	if (state != 'l') { //only stops if not locked
		state = 's';
		cout << "Stopping " << id_num << "." << endl;
		cout << display_code << id_num << ": All right." << endl;
	} else {
		cout << "Cannot stop once locked." << endl;
	}
}

void Person::show_status() {
	Game_Object::show_status();
	if (state == 's') cout << " is stopped";
	if (state == 'l') cout << " is locked";
	if (state == 'm' || state == 'o' || state == 'i') {
		cout << " is moving at a speed of " << speed << " towards " << destination << " at each step of " << delta;
	}
	if (state == 'x') cout << " is dead.";
}

//following 3 functions are virtual
void Person::start_supplying(Oxygen_Depot* inputDepot) {
	cout << "Sorry, I can't work a depot." << endl;
}

void Person::start_depositing(Space_Station* inputStation) {
	cout << "Sorry, I can't work a station." << endl;
}

void Person::go_to_station(Space_Station* inputStation) {
	cout << "Sorry, I can't lock into a station." << endl;
}

bool Person::update_location() {

	//cout << location << endl;

	if (destination.x == location.x && destination.y == location.y) { //if already there
		cout << display_code << id_num << ": I'm there!" << endl;
		return true;
	} else {
		Cart_Vector distanceRemaining = destination - location;

		if (fabs(distanceRemaining.x) <= fabs(delta.x) && fabs(distanceRemaining.y) <= fabs(delta.y)) { //if within one step of destination
			location.x = destination.x; //set x to destination x
			location.y = destination.y; //set y to destination y
			cout << display_code << id_num << ": I'm there!" << endl;
			return true;
		} else {
			location.x = location.x + delta.x; //increments location's x-coordinate by delta's y-coordinate
			location.y = location.y + delta.y; //increments location's y-coordinate by delta's y-coordinate
			cout << display_code << id_num << ": step..." << endl;
			// cout << distanceRemaining << endl;
			// cout << destination << endl;
			return false;
		}
	}
}

void Person::setup_destination(Cart_Point dest) {
	destination = dest; //soft-copy dest to destination
	Cart_Vector deltaVect = destination - location; //calculate first part of equation
	double unitSpeed = speed/cart_distance(destination, location); //calculate second part of equation
	delta = deltaVect * unitSpeed; //put them together

	//cout << delta << endl;
}

bool Person::is_alive() {
	if (state == 'x') { //x for dead
		return false;
	} else {
		return true;
	}
}

int Person::get_num_live_people() {
	return num_live_people;
}

void Person::take_hit(int attack_strength) {
	health -= attack_strength;
	if (health <= 0) {
		cout << "Gasp!" << endl;
		state = 'x';
		num_live_people--;
		health = 0;
	} else {
		cout << "Ouch!" << endl;
		if (health < 3) {
			display_code += 32;
		}
	}
}

Person::~Person() {
	cout << "Person destructed." << endl;
}