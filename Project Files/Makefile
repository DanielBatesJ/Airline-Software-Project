output: main.o plane.o planes.o flight.o flights.o crew.o crews.o
	g++ main.o plane.o planes.o flight.o flights.o crew.o crews.o -o airline.exe
	
main.o: main.cpp crews.h planes.h flights.h
	g++ -c main.cpp

plane.o: plane.cpp plane.h
	g++ -c plane.cpp

planes.o: planes.cpp plane.h planes.h
	g++ -c planes.cpp

flight.o: flight.cpp flight.h
	g++ -c flight.cpp

flights.o: flights.cpp flight.h flights.h crews.h planes.h
	g++ -c flights.cpp

studnet.o: crew.cpp crew.h
	g++ -c crew.cpp

crews.o: crews.cpp crew.h crews.h
	g++ -c crews.cpp