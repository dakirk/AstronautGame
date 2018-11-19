//FINISH ME
//figure out why "I'm there!" message triggers twice
#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
#include "Person.h"
#include "Astronaut.h"

using namespace std;

Astronaut::Astronaut() : Person('A') {
	amount_moonstones = 0;
	amount_oxygen = 20;
	depot = NULL;
	home = NULL;
	cout << "Astronaut default constructed." << endl;
}

Astronaut::Astronaut(int in_id, Cart_Point in_loc) : Person(in_loc, in_id, 'A') {
	amount_moonstones = 0;
	amount_oxygen = 20;
	depot = NULL;
	home = NULL;
	cout << "Astronaut constructed." << endl;
}

bool Astronaut::update() {
	char tempState = state;
	if (amount_oxygen == 0) {
		state = 'x';
	} else if (amount_oxygen == -1) {
		state = 'l';
	}

	if (health < 3) {
		display_code = 'a';
		if (health == 0) { //prevents "zombie" behavior
			state = 'x';
		}
	}

	switch(state) { //sets astronaut to various states
		case 's': { //stopped
			break;
		}
		case 'm': { //moving (generic)
			bool arrived = update_location();
			if (arrived) {
				state = 's';
			}
			break;
		}
		case 'o': { //outbound to depot
			bool arrived = update_location();
			if (arrived) {
				state = 'g';
			}
			break;
		}
		case 'g': { //getting oxygen
			int extractAmount = 20; //might change later?
			depot->extract_oxygen(extractAmount);
			amount_oxygen += extractAmount;
			state = 's';
			cout << display_code << id_num << ": Got " << extractAmount << " oxygen." << endl;
			cout << display_code << id_num << ": Stopped." << endl;
			break;
		}
		case 'i': { //inbound to station
			bool arrived = update_location();
			if (arrived) {
				state = 'd';
			}
			break;
		}
		case 'd': { //deposit moonstones
			home->deposit_moonstones(amount_moonstones);
			state = 's';
			cout << display_code << id_num << ": Depositing. " << amount_moonstones << " moon stones." << endl;
			amount_moonstones = 0;
			cout << display_code << id_num << ": Stopped." << endl;
			break;
		}
		case 'l': { //locking into space station
			if (amount_oxygen > 0) { //if not out of oxygen
				Cart_Point stationPoint = home->get_location(); //get destination coords
				int prevX = location.x;
				int prevY = location.y;
				bool arrived = update_location();
				if (arrived && amount_oxygen != 0) {
					amount_oxygen = -1; //sets oxygen to -1 to signify that astronaut does not have oxygen supply anymore (using station's oxygen)
					if (stationPoint.x != prevX && stationPoint.y != prevY) { // if just arrived
						home->add_astronaut(); //will only add astronaut on arrival--if arrives before station opens, will not be able to enter
						return true;
					} else {
						bool astronautAdded = home->add_astronaut(); //will only add astronaut on arrival--if arrives before station opens, will not be able to enter
						if (astronautAdded) {
							return true;
						}
					}
					//return true; //break prematurely because case does not change
				} else {
					amount_moonstones++;
					amount_oxygen--;
				}
			}
		}

		case 'x': {
			//cout << display_code << id_num << ": I'm dead." << endl;
			break;
		}
	}

	if (state == 'm' || state == 'o' || state == 'i') { //if moving, get a moonstone and lose an oxygen
		amount_moonstones++;
		amount_oxygen--;
	}

	if (tempState != state) { //checks if state changed in switch statement
		return true;
	} else {
		return false;
	}



}

void Astronaut::show_status() { //determines what message to print when show_status() is called
	cout << "Astronaut status: ";
	Person::show_status();

	switch(state) {
		case 's': {
			cout << " with " << amount_oxygen << " oxygen and " << amount_moonstones << " moon stones. ";
			break;
		}
		case 'm': {
			cout << ". ";
			break;
		}
		case 'o': {
			cout << " and is outbound to a depot with " << amount_oxygen << " oxygen and " << amount_moonstones << " moon stones. ";
			break;
		}
		case 'g': {
			cout << " is getting oxygen from depot. ";
			break;
		}
		case 'i': {
			cout << " and is inbound to home with load: " << amount_moonstones << " moonstones and " << amount_oxygen << " oxygen. ";
			break;
		}
		case 'd': {
			cout << " is depositing " << amount_moonstones << " moon stones. ";
			break;
		}
		case 'l': {
			if (amount_oxygen == 0) {
				cout << ". Out of oxygen. ";
			} else {
				cout << " at Space_Station. ";
			}
			break;
		}
	}
	if (health > 0)
		cout << "Health: " << health << "." << endl;
	else
		cout << endl;
}

void Astronaut::start_supplying(Oxygen_Depot* inputDepot) {
	if (state != 'l') {
		depot = inputDepot; //set inputDepot as main depot
		setup_destination(depot->get_location()); //start moving to main depot
		state = 'o';
		cout << "Astronaut " << id_num << " supplying from Oxygen_Depot " << depot->get_id() << "." << endl;
		cout << display_code << id_num << ": Yes, my lord." << endl;
	} else {
		cout << display_code << id_num << ": I'm locked." << endl;
	}
	
}

void Astronaut::start_depositing(Space_Station* inputStation) {
	if (state != 'l') {
		home = inputStation; //set inputStation as home station
		setup_destination(home->get_location()); //start moving to home station
		state = 'i';
		cout << "Astronaut " << id_num << " depositing to Space_Station " << home->get_id() << "." << endl;
		cout << display_code << id_num << ": Yes, my lord." << endl;
	} else {
		cout << display_code << id_num << ": I'm locked." << endl;
	}
}

void Astronaut::go_to_station(Space_Station* inputStation) {
	home = inputStation; //set inputStation as home station
	setup_destination(home->get_location()); //start moving to home station
	state = 'l';
	cout << "Astronaut " << id_num << " locking in at Space_Station " << home->get_id() << "." << endl;
}

Astronaut::~Astronaut() {
	cout << "Astronaut destructed." << endl;
}