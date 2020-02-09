/*
 ==================================================================
 Name        : Airline Management Program
 Instructor  : David Keathly
 Email		 : DanielBates2@my.unt.edu
 Author      : Daniel Bates
 Version     : 3.12
 Description : Airline management software, designed to keep track
 			   of 3 classes through the use of 3 collection classes
 			   users are able to manage the basic functionallity
 			   of an airline.
 Notes		 : g++ -std=c++11
 ==================================================================
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "crews.h"
#include "flights.h"
#include "planes.h"

// Global variables, are used in flights.cpp
planes p1;
crews c1;
flights f1;

// Prints the menu for the user.
void printStartMenu()
{
	cout << "What would you like to do? (Please note that all changes are auto-saved. So keep backups of your files!)" << endl <<
	"1.) Crew     (Add, edit, delete, print, etc.)" << endl <<
	"2.) Plane    (Add, edit, delete, print, etc.)" << endl <<
	"3.) Flights  (Add, edit, delete, print, etc.)" << endl <<
	"4.) Quick Load (Loads disk-saved information for Crew Members and Planes, not Flights!)" << endl << 
	"5.) Exit" << endl << endl;
}

int main()
{
	int i;
	int input;
	bool check = false;
	printStartMenu();

	do
	{
		cin >> input;
		if((input > 0) && (input < 6))
		{
			//Opens the option chosen by the user.
			switch(input)
			{
				case 1:{
					c1.menu();
					printStartMenu();
					break;
				}
				case 2:{
					p1.menu();
					printStartMenu();
					break;
				}
				case 3:{
					f1.menu();
					printStartMenu();
					break;
				}
				case 4:{
					c1.loadCrew();
					p1.loadPlane();
					//f1.loadFlight();
					printStartMenu();
					break;
				}
				case 5:{
					check = true;
					break;
				}
				default:{
					cout << "Error, please try again." << endl;
					check = false;
					break;
				}
			}
		}
	}while(check != true);

	return 0;
}