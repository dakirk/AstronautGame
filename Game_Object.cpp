#include <iostream>
#include "Game_Object.h"
#include "Cart_Point.h"

using namespace std;

//no default constructors
Game_Object::Game_Object(char in_code) {
	display_code = in_code;
	id_num = 1;
	state = 's';
	cout << "Game_Object constructed." << endl;
}

Game_Object::Game_Object(Cart_Point in_loc, int in_id, char in_code) {
	location = in_loc;
	id_num = in_id;
	display_code = in_code;	
	state = 's';
	cout << "Game_Object constructed." << endl;
}

Cart_Point Game_Object::get_location() {
	return location;
}

//getters
int Game_Object::get_id() {
	return id_num;
}

char Game_Object::get_state() {
	return state;
}

//generic show_status function, overridden by children of Game_Object
void Game_Object::show_status() {
	cout << display_code << id_num << " at " << location;
}

void Game_Object::drawself(char* ptr) {
	ptr[0] = display_code;
	ptr[1] = '0' + id_num;
}

bool Game_Object::is_alive() {
	return true;
}

Game_Object::~Game_Object() {
	cout << "Game_Object destructed." << endl;
}