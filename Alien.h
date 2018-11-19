#ifndef ALIEN_H
#define ALIEN_H
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Person.h"
#include "Alien.h"
#include <iostream>

class Alien : public Game_Object {
	public: 
		Alien();
		Alien(int in_id, Cart_Point in_loc);
		void start_attack(Person* in_target);
		void start_moving(Cart_Point dest);
		void stop();
		bool update();
		void show_status();
		~Alien();
	private:
		int attack_strength;
		double range;
		Person* target;
		double speed;
		Cart_Point destination;
		Cart_Vector delta;
		void setup_destination(Cart_Point dest);
		bool update_location();

};

#endif