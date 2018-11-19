#include <iostream>
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

using namespace std;

int main() {
	
	// Cart_Point point1(10,10);
	// Cart_Point point2(1, 1);
	// Cart_Point point3(15,30);
	// Cart_Point point4(1000, 1000);

	// // Person person1;
	// // Person person2('a');
	// // Person person3(personPoint1, 6, 'b');

	// // person1.show_status();
	// // cout << endl;
	// // person2.show_status();
	// // cout << endl;
	// // person3.show_status();
	// // cout << endl;

	// // person1.start_moving(personPoint2);
	// // person1.show_status();

	// //person1.update_location();
	// //person1.update_location();
	// //person1.update_location();

	// Astronaut astro1;
	// astro1.show_status();
	// cout << endl;

	// Astronaut astro2(2, point2);
	// astro2.show_status();
	// cout << endl;

	// Alien alien1;
	// alien1.show_status();

	// Astronaut* astroPtr = &astro2;

	// alien1.start_attack(astroPtr);
	// alien1.update();
	// alien1.update();
	// alien1.update();
	// alien1.update();

	Model testModel;

	Alien* alien1 = testModel.get_Alien_ptr(1);
	// Oxygen_Depot depot1(point1, 3);
	// Oxygen_Depot* depot1ptr = &depot1;

	// Space_Station station1(point3, 4);
	// Space_Station* station1ptr = &station1;

	// // astro1.start_supplying(depot1ptr);
	// // astro1.update();
	// // astro1.update();
	// // astro1.update();
	// // astro1.update();
	// // astro1.update();
	// // astro1.update();
	// // astro1.update();

	// station1.show_status();
	// depot1.show_status();
	
	// while (astro2.is_alive()) {
	// 	astro2.show_status();
	// 	astro2.take_hit(1);
	// 	astro2.update();
	// }
	
	// astro2.show_status();

	// // for (int i = 0; i < 9; i++) {
	// // 	astro2.update();
	// // }
	
	// // astro2.show_status();
	// // station1.update();

	// // astro2.start_depositing(station1ptr);

	// // for (int i = 0; i < 6; i++) {
	// // 	if(astro2.update()) {
	// // 		astro2.show_status();
	// // 	}
	// // }

	// // astro1.go_to_station(station1ptr);
	// // while(!astro1.update()) {
	// // 	astro1.show_status();
	// // }
	// // astro1.show_status();
	


	return 0;
}