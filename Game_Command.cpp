#include <iostream>
#include <cstdlib>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Person.h"
#include "Astronaut.h"
#include "Model.h"
#include "Game_Command.h"
#include "View.h"
#include "Input_Handling.h"

void do_new_command(Model& model, char type, int id, int x, int y) {

	if (id > 9) {
		throw Invalid_Input("ID number must be a single digit (0-9)");
	}
	switch(type) {
		case 'd':
			cout << "Creating new oxygen depot" << endl;
			break;
		case 's':
			cout << "Creating new space station" << endl;
			break;
		case 'a':
			cout << "Creating new astronaut" << endl;
			break;
		case 'x':
			cout << "Creating new alien" << endl;
			break;
		default:
			throw Invalid_Input("Unrecognized object type");
	}

	model.handle_new_command(type, id, x, y);
}

void do_move_command(Model& model, int id, int x, int y) {
	Person* personPtr = model.get_Person_ptr(id);
	if (personPtr == NULL)
		throw Invalid_Input("Unrecognized id");

	if (personPtr->is_alive())
		personPtr->start_moving(Cart_Point(x, y));
	else
		cout << "This person is dead. He has a valid excuse not to work." << endl;		
}

void do_work_a_depot_command(Model& model, int personId, int depotId) {
	Person* personPtr = model.get_Person_ptr(personId);
	Oxygen_Depot* depotPtr = model.get_Oxygen_Depot_ptr(depotId);
	if (personPtr == NULL || depotPtr == NULL)
		throw Invalid_Input("Unrecognized id");

	if (personPtr->is_alive())
		personPtr->start_supplying(depotPtr);
	else
		cout << "This person is dead. He has a valid excuse not to work." << endl;
}

void do_deposit_moon_stones_command(Model& model, int personId, int stationId) {
	Person* personPtr = model.get_Person_ptr(personId);
	Space_Station* stationPtr = model.get_Space_Station_ptr(stationId);
	if (personPtr == NULL || stationPtr == NULL)
		throw Invalid_Input("Unrecognized id");

	if (personPtr->is_alive())
		personPtr->start_depositing(stationPtr);
	else
		cout << "This person is dead. He has a valid excuse not to work." << endl;
}

void do_stop_command(Model& model, int personId) {
	Person* personPtr = model.get_Person_ptr(personId);
	if (personPtr == NULL)
		throw Invalid_Input("Unrecognized id");

	if (personPtr->is_alive())
		personPtr->stop();
	else
		cout << "This person is dead. He has a valid excuse not to work." << endl;
}

void do_lock_in_at_station_command(Model& model, int personId, int stationId) {
	Person* personPtr = model.get_Person_ptr(personId);
	Space_Station* stationPtr = model.get_Space_Station_ptr(stationId);
	if (personPtr == NULL || stationPtr == NULL)
		throw Invalid_Input("Unrecognized id");

	if (personPtr->is_alive())
		personPtr->go_to_station(stationPtr);
	else
		cout << "This person is dead. He has a valid excuse not to work." << endl;
}

void do_attack_command(Model& model, int alienId, int personId) {
	Person* personPtr = model.get_Person_ptr(personId);
	Alien* alienPtr = model.get_Alien_ptr(alienId);
	if (personPtr == NULL || alienPtr == NULL)
		throw Invalid_Input("Unrecognized id");

	model.get_Alien_ptr(alienId)->start_attack(model.get_Person_ptr(personId));
}

void do_go_command(Model& model) {
	cout << "Advancing one tick." << endl;
	model.update();
}

void do_run_command(Model& model) {

	cout << "Advancing to next event." << endl;
	bool eventHappened;
	int counter = 0;
	do {
		eventHappened = model.update();
		counter++;
	} while (!eventHappened && counter != 5);

	model.show_status();

}

void do_quit_command(Model& model) {
	cout << "Terminating program." << endl;
	model.~Model();
	exit(0);
}