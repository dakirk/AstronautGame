#ifndef PERSON_H
#define PERSON_H
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Oxygen_Depot.h"
#include "Space_Station.h"
#include <iostream>

using namespace std;

class Person : public Game_Object {
	public:
		Person();
		Person (char in_code);
		Person(Cart_Point in_loc, int in_id, char in_code);
		void start_moving(Cart_Point dest);
		void stop();
		void show_status();
		bool is_alive();
		void take_hit(int attack_strength);
		static int get_num_live_people();
		virtual void start_supplying(Oxygen_Depot* inputDepot);
		virtual void start_depositing(Space_Station* inputStation);
		virtual void go_to_station(Space_Station* inputStation);
		~Person();
	protected:
		bool update_location();
		void setup_destination(Cart_Point dest);
		int health;
		static int num_live_people;
	private:
		double speed;
		Cart_Point destination;
		Cart_Vector delta;
};


#endif