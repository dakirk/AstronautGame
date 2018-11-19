#include <iostream>
#include "Cart_Point.h"
#include "Oxygen_Depot.h"
#include "Game_Object.h"

using namespace std;

Oxygen_Depot::Oxygen_Depot() : Game_Object('O') { //default constructor
	amount_oxygen = 50;
	state = 'f'; //full of oxygen
	cout << "Oxygen_Depot default constructed" << endl;
}

Oxygen_Depot::Oxygen_Depot(Cart_Point inputLoc, int inputId) : Game_Object(inputLoc, inputId, 'O') {
	amount_oxygen = 50;
	state = 'f';
	cout << "Oxygen_Depot constructed" << endl;
}

bool Oxygen_Depot::is_empty() {
	if (amount_oxygen == 0.0) { //if oxygen depleted, return true
		return true;
	} else { //otherwise return false
		return false;
	}
}

double Oxygen_Depot::extract_oxygen(double amount_to_extract) {
	if (amount_oxygen >= amount_to_extract) { //if enough oxygen left, subtract amount to extract from total and return amount extracted
		amount_oxygen -= amount_to_extract;
		return amount_to_extract;
	} else { //if out of oxygen, return whatever oxygen is left as amount extracted, and set amount of oxygen left to 0
		amount_to_extract = amount_oxygen;
		amount_oxygen = 0;
		return amount_to_extract;
	}
}

bool Oxygen_Depot::update() {
	if (amount_oxygen == 0.0 && state != 'e') { //returns true only the first time empty depot is detected
		state = 'e';
		display_code = 'o';
		cout << "Oxygen_Depot " << id_num << " has been depleted." << endl;
		return true;
	} else { //return false in all other occasions
		return false;
	}
}

void Oxygen_Depot::show_status()
{
	cout << "Oxygen Depot status: ";
	Game_Object::show_status();
	cout << " contains " << amount_oxygen << " oxygen." << endl;;
} 

Oxygen_Depot::~Oxygen_Depot() {
	cout << "Oxygen_Depot destructed." << endl;
}