//INCOMPLETE: implement and display()

#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Person.h"
#include "Astronaut.h"
#include "Alien.h"
#include "Model.h"
#include "View.h"
#include "Input_Handling.h"


using namespace std;

Model::Model() {
	time = 0;
	count_down = 10;

	//populate person_ptrs
	person_ptrs.push_back(new Astronaut(1, Cart_Point(5, 1)));
	object_ptrs.push_back(person_ptrs.back());
	person_ptrs.push_back(new Astronaut(2, Cart_Point(10, 1)));
	object_ptrs.push_back(person_ptrs.back());
	//num_persons = 2;

	//populate depot_ptrs
	depot_ptrs.push_back(new Oxygen_Depot(Cart_Point(1, 20), 1));
	object_ptrs.push_back(depot_ptrs.back());
	depot_ptrs.push_back(new Oxygen_Depot(Cart_Point(10, 20), 2));
	object_ptrs.push_back(depot_ptrs.back());
	//num_depots = 2;

	//populate station_ptrs
	station_ptrs.push_back(new Space_Station());
	object_ptrs.push_back(station_ptrs.back());
	station_ptrs.push_back(new Space_Station(Cart_Point(5, 5), 2));
	object_ptrs.push_back(station_ptrs.back());
	//num_stations = 2;

	//populate alien_ptrs
	alien_ptrs.push_back(new Alien(1, Cart_Point(7, 14)));
	object_ptrs.push_back(alien_ptrs.back());
	alien_ptrs.push_back(new Alien(2, Cart_Point(7, 5)));
	object_ptrs.push_back(alien_ptrs.back());
	//num_aliens = 2;

	//add all pointers to the active pointers list, since all pointers are active at start
	for (std::list<Game_Object*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); ++it) {
		active_ptrs.push_back(*it);
	}

	cout << "Model default constructed." << endl;
}

Person* Model::get_Person_ptr(int id) { //returns pointer to person of id number if exists, or 0 if doesn't
	for (std::list<Person*>::iterator it=person_ptrs.begin(); it != person_ptrs.end(); ++it){
		if (id == (*it)->get_id()) {
			return (*it);
		}
	}

	return 0;
}

Oxygen_Depot* Model::get_Oxygen_Depot_ptr(int id) { //returns pointer to depot of id number if exists, or 0 if doesn't
	for (std::list<Oxygen_Depot*>::iterator it=depot_ptrs.begin(); it != depot_ptrs.end(); ++it){
		if (id == (*it)->get_id()) {
			return (*it);
		}
	}

	return 0;
}

Space_Station* Model::get_Space_Station_ptr(int id) { //returns pointer to station of id number if exists, or 0 if doesn't
	for (std::list<Space_Station*>::iterator it=station_ptrs.begin(); it != station_ptrs.end(); ++it){
		if (id == (*it)->get_id()) {
			return (*it);
		}
	}

	return 0;
}

Alien* Model::get_Alien_ptr(int id) {
	for (std::list<Alien*>::iterator it=alien_ptrs.begin(); it != alien_ptrs.end(); ++it){
		if (id == (*it)->get_id()) {
			return (*it);
		}
	}

	return 0;
}

void Model::handle_new_command(char type, int id, int x, int y) {
	switch(type) {
		case 'd': {
			if (get_Oxygen_Depot_ptr(id) == NULL) { //if station doesn't already exist
				depot_ptrs.push_back(new Oxygen_Depot(Cart_Point(x, y), id));
				object_ptrs.push_back(depot_ptrs.back());
				active_ptrs.push_back(depot_ptrs.back());
			} else {
				throw Invalid_Input("There already exists a depot with this id");
			}
			break;
		}
		case 's': {
			if (get_Space_Station_ptr(id) == NULL) {
				station_ptrs.push_back(new Space_Station(Cart_Point(x, y), id));
				object_ptrs.push_back(station_ptrs.back());
				active_ptrs.push_back(station_ptrs.back());
			} else {
				throw Invalid_Input("There already exists a station with this id");
			}
			break;
		}
		case 'a': {
			if (get_Person_ptr(id) == NULL) {
				person_ptrs.push_back(new Astronaut(id, Cart_Point(x, y)));
				object_ptrs.push_back(person_ptrs.back());
				active_ptrs.push_back(person_ptrs.back());
			} else {
				throw Invalid_Input("There already exists an astronaut with this id");
			}
			break;
		}
		case 'x': {
			if (get_Alien_ptr(id) == NULL) {
				alien_ptrs.push_back(new Alien(id, Cart_Point(x, y)));
				object_ptrs.push_back(alien_ptrs.back());
				active_ptrs.push_back(alien_ptrs.back());
			} else {
				throw Invalid_Input("There already exists and alien with this id");
			}
			break;
		}
		default:
			throw Invalid_Input("Unrecognized object type");
	}
}

//following 2 functions must be implemented
bool Model::update() {

	bool returnVal = false; //true if something updated, false otherwise
	bool isTrue;

	list<Game_Object>::iterator it;
	
	for (std::list<Game_Object*>::iterator it=active_ptrs.begin(); it != active_ptrs.end(); ++it){
	    //cout << it->name;
	    isTrue = (*it)->update(); //double pointer?
		if (isTrue) { //if at least one of the game objects returns true
			returnVal = true;

		}
	}

	//remove dead people from the list
	int numActiveObjects = active_ptrs.size();
	for (list<Game_Object*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); ++it) {
		if (!(*it)->is_alive()) { //if object is alive and is in active list

			//find if the dead object in the list is dead for the first time
			for (list<Game_Object*>::iterator it2 = active_ptrs.begin(); it2 != active_ptrs.end(); ++it2) {
				if (*it == *it2) {
					cout << "Dead object removed" << endl;
				}
			}

			//remove dead object from list
			active_ptrs.remove(*it);
			
		}
	}

	int astronautsRemaining = Person::get_num_live_people();
	if (astronautsRemaining <= 0) {
		cout << "All astronauts died! You lose!" << endl;
		exit(0);
	}



	int numUpgradedStations = 0;
	int numStationedAstronauts = 0;

	for (std::list<Space_Station*>::iterator it=station_ptrs.begin(); it != station_ptrs.end(); ++it){
		if ((*it)->get_state() == 'u') {
			numUpgradedStations++; //increment number of stations upgraded
			numStationedAstronauts += (*it)->get_astronauts(); //increment number of astronauts stationed
		}
	}

	//start countdown if all stations upgraded
	if (numUpgradedStations == station_ptrs.size()) {
		if (numUpgradedStations == station_ptrs.size() && numStationedAstronauts == person_ptrs.size()) {
			cout << "Blast Off! You Win!" << endl;
			exit(1); //1 for win
		} else {
			if (count_down <= 10 && count_down > 0) {
				cout << "Ready for takeoff? " << count_down << "..." << endl;
			} else if (count_down == 0) {
				cout << "Unmanned takeoff... You lose!" << endl;
				exit(0); //0 for loss
			}
			count_down--;
		}
	}

	time++; //advances time by one

	return returnVal;
}
//void Model::display(View &view) {}

void Model::show_status() {
	cout << "Time: " << time << endl;
	cout << "Astronauts remaining: " << Person::get_num_live_people() << endl;

	for (std::list<Game_Object*>::iterator it=object_ptrs.begin(); it != object_ptrs.end(); ++it){
	    //cout << it->name;
	    (*it)->show_status(); //double pointer?
	}

}

void Model::display(View &view) {
	//show_status();
	view.clear();
	
	//plot all active objects
	for (std::list<Game_Object*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); ++it) {
		view.plot((*it));
	}
	/*
	viewer->plot(gameModel->get_Person_ptr(2));
	viewer->plot(gameModel->get_Space_Station_ptr(1));
	viewer->plot(gameModel->get_Space_Station_ptr(2));
	viewer->plot(gameModel->get_Oxygen_Depot_ptr(1));
	viewer->plot(gameModel->get_Oxygen_Depot_ptr(2));
	viewer->plot(gameModel->get_Alien_ptr(1));
	viewer->plot(gameModel->get_Alien_ptr(2));
	*/
	view.draw();
}

Model::~Model() {

	for (std::list<Person*>::iterator it=person_ptrs.begin(); it != person_ptrs.end(); ++it){
		delete *it;
	}

	for (std::list<Space_Station*>::iterator it=station_ptrs.begin(); it != station_ptrs.end(); ++it){
		delete *it;
	}

	for (std::list<Oxygen_Depot*>::iterator it=depot_ptrs.begin(); it != depot_ptrs.end(); ++it){
		delete *it;
	}

	for (std::list<Alien*>::iterator it=alien_ptrs.begin(); it != alien_ptrs.end(); ++it){
		delete *it;
	}

	cout << "Model destructed." << endl;
}