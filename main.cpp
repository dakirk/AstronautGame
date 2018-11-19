#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include "Person.h"
#include "Astronaut.h"
#include "Alien.h"
#include "Model.h"
#include "Game_Command.h"
#include "View.h"
#include "Input_Handling.h"

using namespace std;

double* getUserInputMultiParameters(string multiParamInput);
void updateView(View* viewer, Model* gameModel);

int main() {

	bool funcArgsDeclared = false;

	Model testModel;
	Model* modelPtr = &testModel;

	View viewer;
	View* viewPtr = &viewer;
	
	testModel.show_status();

	string inputLine;
	double* funcArgs;

	while(true) {
		testModel.display(viewer);
		cout << "Enter command: ";
		getline(cin, inputLine);

		try {
			if (!isalpha(inputLine[0])) {
				throw Invalid_Input("First character must be a single letter");
			}

			if (inputLine.length() > 1) { //if command has parameters

				if (inputLine[1] == ' ' && isalpha(inputLine[2])) { //if it's the new object command (2 chars and then numbers)

					if (inputLine.length() <= 4)
						throw Invalid_Input("Not enough parameters");

					funcArgs = getUserInputMultiParameters(inputLine.substr(4));
					funcArgsDeclared = true;
					switch(inputLine[0]) {
						case 'n': {
							if (funcArgs[0] != 2)
								throw Invalid_Input("Must be exactly 4 arguments");
							do_new_command(testModel, inputLine[2], funcArgs[1], funcArgs[2], funcArgs[3]);
							break;
						}
						default:
							throw Invalid_Input("Unrecognized command");
					}

				} else {
					funcArgs = getUserInputMultiParameters(inputLine.substr(2));
					funcArgsDeclared = true;
					switch(inputLine[0]) {

						case 'm': { //if command is m for move
							if (funcArgs[0] != 2)
								throw Invalid_Input("Must be exactly 3 arguments");
							do_move_command(testModel, funcArgs[1], funcArgs[2], funcArgs[3]);
							break;
						}
						case 'w': { //if command is w for go to depot
							if (funcArgs[0] != 1)
								throw Invalid_Input("Must be exactly 2 arguments");
							do_work_a_depot_command(testModel, funcArgs[1], funcArgs[2]);
							break;
						}
						case 'd': { //if command is d for deposit at base
							if (funcArgs[0] != 1)
								throw Invalid_Input("Must be exactly 2 arguments");
							do_deposit_moon_stones_command(testModel, funcArgs[1], funcArgs[2]);
							break;
						}
						case 's': { //if command is s for stop
							if (funcArgs[0] != 0)
								throw Invalid_Input("Must be only 1 argument");
							do_stop_command(testModel, funcArgs[1]);
							break;
						}
						case 'l': { //if command is l for lock on
							if (funcArgs[0] != 1)
								throw Invalid_Input("Too many arguments");
							do_lock_in_at_station_command(testModel, funcArgs[1], funcArgs[2]);
							break;
						}
						case 'a': { //if command is a for attack
							if (funcArgs[0] != 1)
								throw Invalid_Input("Too many arguments");
							do_attack_command(testModel, funcArgs[1], funcArgs[2]);
							break;
						}
						default:
							throw Invalid_Input("Unrecognized command");
					}
				}
			} else {

				//commands with no parameters
				switch(inputLine[0]) {
					
					case 'g': { //if command is g for advance one tick
						do_go_command(testModel);
						testModel.show_status();
						break;
					}
					case 'r': { //if command is r for run 5 ticks
						do_run_command(testModel);
						testModel.show_status();
						break;
					}
					case 'q': { //if command is q for quit
						do_quit_command(testModel);
						break;
					}
					default:
						throw Invalid_Input("Unrecognized command");
				}
			}
		} catch (Invalid_Input& except) {
			cout << "Invalid input - " << except.msg_ptr << endl;
			//doesn't really seem like there's much else to do right now--seems to work fine like this
		}



		//reset input
		inputLine = ' ';

		if (funcArgsDeclared) {
			int arrSize = funcArgs[0]; //gets size of array from first index

			//populate funcArgs with zeroes to prevent re-use
			for (int index = 0; index <= arrSize+1; index++) {
				funcArgs[index] = 0;
				//cout << funcArgs[index] << endl;
			}
		}


	}

	return 0;
}

//copied from Q1 of PA2
double* getUserInputMultiParameters(string multiParamInput) {

	//string multiParamInput;
	
	bool badInput;
	int spaceCounter = 0;

	//check for bad input


	//check each character for validity (must be a number or space)
	for (int i = 0; i < multiParamInput.length(); i++) {

		//if invalid, continue loop
		if ((multiParamInput[i] < '0' || multiParamInput[i] > '9') && (multiParamInput[i] != ' ') && (multiParamInput[i] != '.') && (multiParamInput[i] != '-')) {
			
			//badInput = true;
			//spaceCounter = 0;
			throw Invalid_Input("Bad parameters. Non-numerical submissions are not recognized.");
			//break;

		//if valid
		} else {
			badInput = false;
		}

		//if space, increment counter (used as delimiter later)
		if (multiParamInput[i] == ' ' && i < multiParamInput.length()-1) {

			//if 2 spaces in a row, invalid answer
			if(multiParamInput[i+1] == ' ') {
				//badInput = true;
				//spaceCounter = 0;
				throw Invalid_Input("Bad parameters. Please separate numbers by one space each.");
				//break;
			} else {
				spaceCounter++;
			}
		}
	}



	//necessary declarations for preparing return pointer
	string tempNumStr;
	stringstream ss(multiParamInput);

	//splits input string into array of doubles, with first value as length of array - 1
	double doublesArray[spaceCounter+2];
	doublesArray[0] = spaceCounter;
	for (int i = 0; i <= spaceCounter; i++) {
		getline(ss, tempNumStr, ' ');
		doublesArray[i+1] = atof(tempNumStr.c_str());
	}

	//creates and populates an array on the heap, pointed to by returnArray
	double* returnArray = new double[spaceCounter+2];

	for (int i = 0; i < spaceCounter+2; i++) {
		returnArray[i] = doublesArray[i];
	}
	return returnArray;
}

/*
void updateView(View* viewer, Model* gameModel) { //updates everything
	viewer->clear();
	viewer->plot(gameModel->get_Person_ptr(1));
	viewer->plot(gameModel->get_Person_ptr(2));
	viewer->plot(gameModel->get_Space_Station_ptr(1));
	viewer->plot(gameModel->get_Space_Station_ptr(2));
	viewer->plot(gameModel->get_Oxygen_Depot_ptr(1));
	viewer->plot(gameModel->get_Oxygen_Depot_ptr(2));
	viewer->plot(gameModel->get_Alien_ptr(1));
	viewer->plot(gameModel->get_Alien_ptr(2));
	viewer->draw();
}*/
