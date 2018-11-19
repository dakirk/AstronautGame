#include <iostream>
#include "Cart_Point.h"
#include "Space_Station.h"
#include "Game_Object.h"

using namespace std;

Space_Station::Space_Station() : Game_Object('s') { //default constructor
	amount_moonstones = 0;
	number_astronauts = 0;
	state = 'o';
	cout << "Space_Station default constructed" << endl;
}

Space_Station::Space_Station(Cart_Point inputLoc, int inputId) : Game_Object(inputLoc, inputId, 's') {
	amount_moonstones = 0;
	number_astronauts = 0;
	state = 'o';
	cout << "Space_Station constructed" << endl;
}

void Space_Station::deposit_moonstones(double deposit_amount) {
	amount_moonstones += deposit_amount;
}

bool Space_Station::add_astronaut() {
	if (state == 'u') { //only increments astronauts if upgraded and there aren't any astronauts yet
		number_astronauts++;
		return true;
	} else {
		return false;
	}
}

int Space_Station::get_astronauts() {
	return number_astronauts;
}

bool Space_Station::update() {
	if (amount_moonstones >= 10 && state != 'u') { //if enough moonstones and not updated yet
		state = 'u'; //upgrades station
		display_code = 'S'; //updates display code to reflect upgrade
		cout << display_code << id_num << " has been upgraded." << endl;
		return true;
	} else {
		return false;
	}
}

void Space_Station::show_status() {
	cout << "Space Station status: ";
	Game_Object::show_status();
	cout << " contains " << amount_moonstones << " moon stones and contains " << number_astronauts << " astronauts.";
	
	if (amount_moonstones >= 10) { //if has enough moon stones to be upgraded
		cout << " Upgraded." << endl;
	} else {
		cout << " Not yet upgraded." << endl;
	}
}

Space_Station::~Space_Station() {
	cout << "Space_Station destructed." << endl;
}