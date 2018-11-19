
CC=g++

OBJS=main.o Cart_Point.o Cart_Vector.o Game_Object.o Game_Command.o Oxygen_Depot.o Astronaut.o Model.o Person.o Space_Station.o View.o Alien.o

default: PA4

PA4: $(OBJS)
	$(CC) -o PA4 $(OBJS) 

Cart_Vector.o: Cart_Vector.cpp Cart_Vector.h
	$(CC) -c Cart_Vector.cpp -o Cart_Vector.o 
	
Cart_Point.o: Cart_Point.cpp Cart_Point.h Cart_Vector.h
	$(CC) -c Cart_Point.cpp -o Cart_Point.o 

Game_Object.o: Game_Object.cpp Game_Object.h Cart_Point.h Cart_Vector.h
	$(CC) -c Game_Object.cpp -o Game_Object.o 

Oxygen_Depot.o: Oxygen_Depot.cpp Oxygen_Depot.h Game_Object.h Cart_Point.h
	$(CC) -c Oxygen_Depot.cpp -o Oxygen_Depot.o 

Astronaut.o: Astronaut.cpp Astronaut.h Person.h Game_Object.h Oxygen_Depot.h Space_Station.h Cart_Point.h Cart_Vector.h
	$(CC) -c Astronaut.cpp -o Astronaut.o 

Model.o: Model.cpp Model.h Game_Object.h Person.h Alien.h Space_Station.h Oxygen_Depot.h Astronaut.h View.h
	$(CC) -c Model.cpp -o Model.o -Wno-write-strings

Space_Station.o: Space_Station.cpp Space_Station.h Game_Object.h Cart_Point.h
	$(CC) -c Space_Station.cpp -o Space_Station.o 

View.o: View.cpp View.h Game_Object.h Cart_Point.h
	$(CC) -c View.cpp -o View.o 

Person.o: Person.cpp Person.h Game_Object.h Cart_Point.h Cart_Vector.h Space_Station.h Oxygen_Depot.h
	$(CC) -c Person.cpp -o Person.o

Alien.o: Alien.cpp Alien.h Person.h Game_Object.h Cart_Point.h Cart_Vector.h
	$(CC) -c Alien.cpp -o Alien.o

Game_Command.o: Game_Command.cpp Game_Command.h Model.h Game_Object.h Person.h Space_Station.h Oxygen_Depot.h Astronaut.h Input_Handling.h
	$(CC) -c Game_Command.cpp -o Game_Command.o -Wno-write-strings



main.o: main.cpp Cart_Point.h Cart_Vector.h Game_Command.h Oxygen_Depot.h Astronaut.h Alien.h Model.h Person.h Space_Station.h Game_Object.h View.h Input_Handling.h
	$(CC) -c main.cpp -Wno-write-strings

clean: 
	rm $(OBJS) PA4

