#ifndef OXYGEN_DEPOT_H
#define OXYGEN_DEPOT_H
#include "Cart_Point.h"
#include "Game_Object.h"
#include <iostream>

using namespace std;

class Oxygen_Depot : public Game_Object {
	private:
		double amount_oxygen;
	public:
		Oxygen_Depot();
		Oxygen_Depot(Cart_Point inputLoc, int inputId);
		bool is_empty();
		double extract_oxygen(double amount_to_extract = 20.0);
		bool update();
		void show_status();
		~Oxygen_Depot();
};

#endif