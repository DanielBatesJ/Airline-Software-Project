#include "flights.h"
#include "planes.h"
#include "crews.h"

// You don't need to automatically change flight hours, you can do it through edit.

// Uses the global varibles to access the same data as main.
extern planes p1;
extern crews c1;

// Prints all the menu options avalible to the user
void printMenu()
{
	cout << "What would you like to do?" << endl <<
	"1.) Add a flight" << endl <<
	"2.) Modify a flight" << endl <<
	"3.) Delete a flight" << endl <<
	"4.) Print all flights (By ID)" << endl <<
	"5.) Print all information about a specific flight" << endl <<
	"6.) Search by flight ID" << endl <<
	"7.) Advanced Search" << endl <<
	"8.) Store to a file" << endl <<
	"9.) Load from a file (Loading a single flight from a file might cause issues with time, if this happens, rerun this function)" << endl <<
	"10.) Check for Flight Status Updates" << endl <<
	"11.) Exit" << endl << endl;
}

// Code to interprate the time given by the set time functions
double timeFunc(string inputTime)
{
	// From http://www.cplusplus.com/reference/ctime/time/
	double inSeconds;
	// Struct of the time struct from ctime
	struct tm input = {0};

	int month;
	int day;
	int year;
	int hr;
	int min;
	int sec;

	string junk;

	//string testTime = "11/12/2018 23:15:21\n";
	// Writes the time to the file.
	ofstream timeW;
	timeW.open("time.txt");
	timeW << inputTime;
	timeW.close();
	// Reads the time from the file, and uses the data to construct a epoc-type number to use to compare to current time later.
	ifstream timeR;
	timeR.open("time.txt");
	timeR >> month;
	getline(timeR, junk, '/');
	timeR >> day;
	getline(timeR, junk, '/');
	timeR >> year;
	getline(timeR, junk, ' ');
	timeR >> hr;
	getline(timeR, junk, ':');
	timeR >> min;
	getline(timeR, junk, ':');
	timeR >> sec;
	getline(timeR, junk, '\n');

	input.tm_hour = hr;   
	input.tm_min = min; 
	input.tm_sec = sec;
	input.tm_year = year - 1900; 
	input.tm_mon = month - 1; 
	input.tm_mday = day;	
	// Makes the epoc type number
	inSeconds = mktime(&input);
	//printf ("%.f seconds since January 1, 2000 for the input\n", inSeconds);
	return inSeconds;
	
}

// Checks the status of the flight, based on the time.
bool flights::checkStatus()
{
	// Code based around https://www.youtube.com/watch?v=qXB5icpo0qY
	time_t now;
	struct tm time_now;
	double seconds;
	int i;
	int crew[3];

	now=time(NULL);

	time_now = *localtime(&now);
	// Sets the local time equal to the same kind of number used in the timeFunc() function
	seconds = mktime(&time_now);

	// Compares the times, and makes changes to flights, crews and planes accordingly.
	for(i = 0; i < flightCnt; i++)
	{
		// If the status isn't currently In-Flight, but the current local time on your machine is between the start and end times, it sets all varibles, accross different classes to be In-Flight
		if((flightList[i].getStatus() != "In-Flight") && ((seconds >= flightList[i].getStartTime()) && (seconds <= flightList[i].getEndTime())))
		{
			flightList[i].setStatus("In-Flight");
			flightList[i].getCrewID(crew);
			c1.updateCrew(flightList[i].getPilotID(), flightList[i].getCoPilotID(), crew , flightList[i].getStatus());
			p1.updatePlane(flightList[i].getPlaneID(), flightList[i].getStatus());
			cout << "UPDATE: Flight " << flightList[i].getFlightID() << " is currently In-Flight\n";
			storeFlight();
		}
		// If the current time is past the end time, the flight is set to be completed, and the varibles become avalible again
		else if(seconds >= flightList[i].getEndTime())
		{
			flightList[i].setStatus("Completed");
			flightList[i].getCrewID(crew);
			string a = "Avalible";
			c1.updateCrew(flightList[i].getPilotID(), flightList[i].getCoPilotID(), crew, a);
			p1.updatePlane(flightList[i].getPlaneID(), a);
			cout << "UPDATE: Flight " << flightList[i].getFlightID() << " is currently Completed\n";
			storeFlight();
		}
		// If the current time is less than the start time, than the varibles are kept as scheduled
		else if(seconds <= flightList[i].getStartTime())
		{
			flightList[i].setStatus("Scheduled");
			flightList[i].getCrewID(crew);
			c1.updateCrew(flightList[i].getPilotID(), flightList[i].getCoPilotID(), crew , flightList[i].getStatus());
			p1.updatePlane(flightList[i].getPlaneID(), flightList[i].getStatus());
			cout << "UPDATE: Flight " << flightList[i].getFlightID() << " is currently Scheduled\n";
			storeFlight();
		}
	}
//	printf ("%.f seconds since January 1, 2000 in the current timezone\n", seconds);
	
	cout << endl;
	return true;

}

// Allows for user input to choose the function they want to enter
void flights::menu()
{
	int input;
	bool check = false;
	printMenu();
	do
	{
		cin >> input;
		cin.ignore();
		if((input > 0) && (input < 12))
		{
			switch(input)
			{
				case 1:{
					addFlight();
					printMenu();
					break;
				}
				case 2:{
					deleteFlight();
					printMenu();
					break;
				}
				case 3:{
					modifyFlight();
					printMenu();
					break;
				}
				case 4:{
					printFlight();
					printMenu();
					break;
				}
				case 5:{
					printAllFlight();
					printMenu();
					break;
				}
				case 6:{
					searchID();
					printMenu();
					break;
				}
				case 7:{
					advSearch();
					printMenu();
					break;
				}
				case 8:{
					storeFlight();
					printMenu();
					break;
				}
				case 9:{
					loadFlight();
					printMenu();
					break;
				}
				case 10:{
					checkStatus();
					printMenu();
					break;
				}
				case 11:{
					check = true;
					break;
				}
			}
		}
	}while(check != true);	
}

void flights::enterFlightID(flight &temp)
{
	string fID;
	cout << "Enter the Flight ID (Three Letters, Three Numbers): " << endl;
	getline(cin, fID);
	temp.setFlightID(fID);
}

bool flights::enterPlaneID(flight &temp)
{
	bool check;
	string plID;
	cout << "Enter the Tail Number for the plane: " << endl;
	getline(cin, plID);
	// Runs a check on the information provided, is the same in pilot, copilot, and cabin crew
	check = p1.flightPlaneSearch(plID);
	if(check == true)
	{
		temp.setPlaneID(plID);
		return true;
	}
	else if(check == false)
	{
		return false;
	}
}

bool flights::enterPilotID(flight &temp)
{
	bool check;
	int pID;
	cout << "Enter the Pilot ID (4 Numbers): " << endl;
	cin >> pID;
	cin.ignore();
	check = c1.flightPilotSearch(pID);
	if(check == true)
	{
		temp.setPilotID(pID);
		return true;
	}
	else if(check == false)
	{
		return false;
	}
}

bool flights::enterCoPilotID(flight &temp)
{
	bool check;
	int cpID;
	cout << "Enter the Co-Pilot ID (4 Numbers): " << endl;
	cin >> cpID;
	cin.ignore();
	check = c1.flightCoPilotSearch(cpID);
	if(check == true)
	{
		temp.setCoPilotID(cpID);
		return true;
	}
	else if(check == false)
	{
		return false;
	}
}

bool flights::enterCrewID(flight &temp)
{
	bool check;
	int crewID[3];
	int i;
	for(i = 0; i < 3; i++)
	{
		cout << "Enter Crew ID #" << i+1 << " (4 Numbers): ";
		cin >> crewID[i];
		cin.ignore();
		check = c1.flightCrewSearch(crewID[i]);
		if(check == false)
		{
			return false;
		}
	}
	temp.setCrewID(crewID);
	return true;
}

void flights::enterStartTime(flight &temp)
{
	string st;
	double startingTime;
	// Gives specific instruction on how to enter the time, passes that into the timeFunc() to be translated
	cout << "Enter the time the flight will leave by (Format as such: MO/DA/YEAR HR:MI:SE): " << endl;
	getline(cin, st);
	startingTime = timeFunc(st);
	// Takes the double returned from the timeFunc, and adds it to temp
	temp.setStartTime(startingTime);
}

void flights::enterEndTime(flight &temp)
{
	string et;
	double endingTime;
	cout << "Enter the time the flight will be over by (Format as such: MO/DA/YEAR HR:MI:SE): " << endl;
	getline(cin, et);
	endingTime = timeFunc(et);
	temp.setEndTime(endingTime);
}

void flights::enterStartingAirport(flight &temp)
{
	string sa;
	cout << "Enter the starting airport: " << endl;
	getline(cin, sa);
	temp.setStartingAirport(sa);
}

void flights::enterEndingAirport(flight &temp)
{
	string ea;
	cout << "Enter the ending airport: " << endl;
	getline(cin, ea);
	temp.setEndingAirport(ea);
}

bool flights::enterNumPassengers(flight &temp)
{
	int pn;
	bool check;
	cout << "Enter the number of passengers for the flight: " << endl;
	cin >> pn;
	check = p1.flightCheckSeats(temp.getPlaneID(), pn);
	if(check == true)
	{
		temp.setNumPassengers(pn);
		return true;
	}
	else if(check == false)
	{
		return false;
	}	
}

// Originally gave options, but is now automatically changed, and defualted to Scheduled. If the time entered makes the flight either completed or in-flight, this will change afte the automated call to check
void flights::enterStatus(flight &temp)
{
	temp.setStatus("Scheduled");
}

void flights::addFlight()
{
	flight temp;
	bool check;
	int crew[3];
	// Checks in place
	enterFlightID(temp);
	do{
		check = enterPlaneID(temp);
		if(check == false)
		{
			cout << "Plane not found. Please try again." << endl;
		}
		else
		{
			check = true;
		}
	}while(check != true);
	check = false;
	
	do{
		check = enterNumPassengers(temp);
		if(check == false)
		{
			cout << "Please try again." << endl;
		}
		else
		{
			check = true;
		}
	}while(check != true);	
	check = false;

	do{
		check = enterPilotID(temp);
		if(check == false)
		{
			cout << "Pilot not found. Please try again." << endl;
		}
		else
		{
			check = true;
		}
	}while(check != true);
	check = false;

	do{
		check = enterCoPilotID(temp);
		if(check == false)
		{
			cout << "Co-Pilot not found. Please try again." << endl;
		}
		else
		{
			check = true;
		}
	}while(check != true);
	check = false;

	do{
		check = enterCrewID(temp);
		if(check == false)
		{
			cout << "One or more Crew Members were not found. Please try again." << endl;
		}
		else
		{
			check = true;
		}
	}while(check != true);	
	check = false;
	
	enterStatus(temp);
	temp.getCrewID(crew);
	// Updates the crew and plane to be scheduled
	c1.updateCrew(temp.getPilotID(), temp.getCoPilotID(), crew , temp.getStatus());
	p1.updatePlane(temp.getPlaneID(), temp.getStatus());

	enterStartTime(temp);
	enterEndTime(temp);
	enterStartingAirport(temp);
	enterEndingAirport(temp);	

	flightList.push_back(temp);
	flightCnt++;
	// Runs store flight automatically, which also runs the check function to update based on time
	storeFlight();

	return;
}

// Deletes the entered flight.
void flights::deleteFlight()
{
	int i;
	string input;
	string status = "Avalible";
	int crew[3];

	cout << "Enter Flight ID" << endl;
	getline(cin, input);

	for(i = 0; i < flightCnt; i++)
	{
		if(input == flightList[i].getFlightID())
		{
			cout << "Flight Found!" << endl;
			cout << "Flight: " << flightList[i].getFlightID() << " deleted." << endl;
			// Changes planes and crew associated with the flight to avalible
			flightList[i].getCrewID(crew);
			c1.updateCrew(flightList[i].getPilotID(), flightList[i].getCoPilotID(), crew , status);
			p1.updatePlane(flightList[i].getPlaneID(), status);
			flightList.erase(flightList.begin() + i);
			// Decrements the flight count, and auto runs the store 
			flightCnt--;
			storeFlight();
			return;
		}
	}
	cout << "Flight ID " << input << " not found, please try again." << endl;
}

// Allows the user to edit certain aspects of the flight that the automatic functions aren't dependant on.
void flights::modifyFlight()
{
	int i;
	string input;
	int input2;
	bool check = false;

	string planeID;
	int pilotID;
	int coPilotID;
	int crewID[3];
	double startTime;
	double endTime;
	string startingAirport;
	string endingAirport;
	int numPassengers;
	int status;

	cout << "Enter Flight ID:" << endl;
	getline(cin, input);
	//Loop to find the entered ID
	for(i = 0; i < flightCnt; i++)
	{
		if(flightList[i].getFlightID() == input)
		{
			cout << "Flight Found!" << endl;
			cout << "What would you like to edit?" << endl <<
			"1.) Starting & Ending times" << endl <<
			"2.) Starting Airport" << endl <<
			"3.) Ending Airport" << endl <<
			"4.) Passenger Number" << endl;
			
			do{
				cin >> input2;
				cin.ignore();
				switch(input2)
				{
					// A very slightly modified version of the enter functions, to have them more suitable for modification.
					case 1: 
					{
						string st;
						double startingTime;
						// Gives specific instruction on how to enter the time, passes that into the timeFunc() to be translated
						cout << "Enter the time the flight will leave by (Format as such: MO/DA/YEAR HR:MI:SE): " << endl;
						getline(cin, st);
						startingTime = timeFunc(st);
						// Takes the double returned from the timeFunc, and adds it to temp
						flightList[i].setStartTime(startingTime);

						string et;
						double endingTime;
						cout << "Enter the time the flight will be over by (Format as such: MO/DA/YEAR HR:MI:SE): " << endl;
						getline(cin, et);
						endingTime = timeFunc(et);
						flightList[i].setEndTime(endingTime);

						storeFlight();
						return;			
					}
					case 2: 
					{
						cout << "Enter the flight's new Starting Airport: " << endl;
						getline(cin, startingAirport);
						flightList[i].setStartingAirport(startingAirport);	
						storeFlight();
						return;					
					}
					case 3: 
					{
						cout << "Enter the flight's new Ending Airport: "<< endl;
						getline(cin, endingAirport);
						flightList[i].setEndingAirport(endingAirport);
						storeFlight();
						return;			
					}
					case 4:
					{
						int pn;
						bool check;
						cout << "Enter the new number of passengers for the flight: " << endl;
						cin >> pn;
						check = p1.flightCheckSeats(flightList[i].getPlaneID(), pn);
						if(check == true)
						{
							flightList[i].setNumPassengers(pn);
							storeFlight();
							return;
						}
						else
						{
							cout << "The plane being used does not support that many seats.\n";
							return;
						}	
					}
					default: {
						cout << "Invalid input, try again" << endl;
						check = false;
						break;
					}
				}
			}while(check != true);
			cout << "Flight Not Found" << endl;
			return;
		}
	}		
}

// Prints basic information on all flights
void flights::printFlight()
{
	int i;
	if(flightCnt == 0)
	{
		cout << "No flights found." << endl << endl;
		return;
	}
	for(i = 0; i < flightCnt; i++)
	{
		cout << "Flight ID - " << flightList[i].getFlightID() << ": " << 
		flightList[i].getStartingAirport() << " -> " << flightList[i].getEndingAirport() << 
		" (" << flightList[i].getStartTime() << " to " << flightList[i].getEndTime() << ") - " << flightList[i].getStatus() << endl;
	}
	cout << endl;
}

// Prints all information on one specific flight
void flights::printAllFlight()
{
	int i;
	int j;
	string input;
	int crew[3];

	cout << "Enter the Flight ID for the flight you want more information on: ";
	getline(cin, input);
	for(i = 0; i < flightCnt; i++)
	{
		if(flightList[i].getFlightID() == input)
		{
			flightList[i].getCrewID(crew);
			cout << "Flight ID		- " << flightList[i].getFlightID() << endl <<
			"Plane ID 		- " << flightList[i].getPlaneID() << endl <<
			"Pilot ID 		- " << flightList[i].getPilotID() << endl <<
			"Co-Pilot ID 		- " << flightList[i].getCoPilotID() << endl;
			for(j = 0; j < 3; j++)
			{
				cout << "Cabin Crew #" << j+1 << "		- " << crew[i] << endl;
			}
			cout <<"Starting Time 		- " << flightList[i].getStartTime() << endl <<
			"Ending Time		- " << flightList[i].getEndTime() << endl <<
			"Starting Airport	- " << flightList[i].getStartingAirport() << endl <<
			"Ending Airport		- " << flightList[i].getEndingAirport() << endl <<
			"Passenger Number	- " << flightList[i].getNumPassengers() << endl <<
			"Status			- " << flightList[i].getStatus() << endl;
			return;
		}
	}
	cout << "Flight not found" << endl;	
}

// Provides all information on one specific flight
void flights::searchID()
{
	int i;
	int j;
	int crew[3];
	bool check = false;
	string flightID;

	cout << "Enter the Flight ID:";
	do{
		getline(cin, flightID);
		for(i = 0; i < flightCnt; i++)
		{
			if(flightList[i].getFlightID() == flightID)
			{
				cout << "Flight found!" << endl;
				//Copied from print
				flightList[i].getCrewID(crew);
				cout << "Flight ID		- " << flightList[i].getFlightID() << endl <<
				"Plane ID 		- " << flightList[i].getPlaneID() << endl <<
				"Pilot ID 		- " << flightList[i].getPilotID() << endl <<
				"Co-Pilot ID 		- " << flightList[i].getCoPilotID() << endl;
				for(j = 0; j < 3; j++)
				{
					cout << "Cabin Crew #" << j+1 << "		- " << crew[i] << endl;
				}
				cout <<"Starting Time 		- " << flightList[i].getStartTime() << endl <<
				"Ending Time		- " << flightList[i].getEndTime() << endl <<
				"Starting Airport	- " << flightList[i].getStartingAirport() << endl <<
				"Ending Airport		- " << flightList[i].getEndingAirport() << endl <<
				"Passenger Number	- " << flightList[i].getNumPassengers() << endl <<
				"Status			- " << flightList[i].getStatus() << endl << endl;
				return;				
			}
		}	
	}while(check != true);
	cout << "Flight not found." << endl << endl;

}

// Allows you to search for a flight based on advanced options.
void flights::advSearch()
{
	int i;
	int choice;
	int choice2;
	bool check = false;
	bool check2 = false;

	cout << "What would you like to search by?" << endl <<
	"1.) Status" << endl <<
	"2.) Departure and Arrival Times" << endl <<
	"3.) Locations" << endl;

	do{
		cin >> choice;
		cin.ignore();
		switch(choice)
		{
			case 1:{
				cout << "What type of status would you like to find?" << endl << 
				"1. Completed" << endl << 
				"2. Scheduled" << endl << 
				"3. In-flight" << endl;
				do
				{
					cin >> choice2;
					cin.ignore();
					switch(choice2)
					{
						case 1:{
							cout << "Completed:" << endl;
							for(i = 0; i < flightCnt; i++)
							{
								if(flightList[i].getStatus() == "Completed")
								{
									cout << "Flight ID: " << flightList[i].getFlightID() << endl;
								}
							}
							return;
						}
						case 2:{
							cout << "Scheduled:" << endl;
							for(i = 0; i < flightCnt; i++)
							{
								if(flightList[i].getStatus() == "Scheduled")
								{
									cout << "Flight ID: " << flightList[i].getFlightID() << endl;
								}
							}
							return;
						}
						case 3:{
							cout << "In-flight:" << endl;
							for(i = 0; i < flightCnt; i++)
							{
								if(flightList[i].getStatus() == "In-flight")
								{
									cout << "Flight ID: " << flightList[i].getFlightID() << endl;
								}
							}
							return;
						}			
						default:{
							cout << "Invalid input, try again." << endl;
						}
					}
				}while(check2 != true);
			}
			case 2:{
				for(i = 0; i < flightCnt; i++)
				{
					cout << "Flight ID: " << flightList[i].getFlightID() << " - Departs at " << flightList[i].getStartTime() << ", and arrives at " << flightList[i].getEndTime() << endl;
				}

				return;	
			}
			case 3:{
				for(i = 0; i < flightCnt; i++)
				{
					cout << "Flight ID: " << flightList[i].getFlightID() << " - Departs from " << flightList[i].getStartingAirport() << ", and arrives at " << flightList[i].getEndingAirport() << endl;
				}			
				return;
			}
			default:{
				cout << "Invalid input, try again." << endl;
			}
		}
	}while(check != true);

}

//Stores all information on the flight. 
void flights::storeFlight()
{
	int i;
	int j;
	int crewID[3];
	// Runs automatically, so backup your data
	ofstream flights;
	flights.open("flights.txt");

	for(i = 0; i < flightCnt; i++)
	{
		flights << flightList[i].getFlightID() << "	" <<
		flightList[i].getPlaneID() << "	" <<
		flightList[i].getPilotID() << "	" <<
		flightList[i].getCoPilotID() << "	";
		flightList[i].getCrewID(crewID);
		for(j = 0; j < 3; j++)
		{
			flights << crewID[j] << "	"; 
		}
		flights << flightList[i].getStartTime() << "	" <<
		flightList[i].getEndTime() << "	" <<
		flightList[i].getStartingAirport() << "	" <<
		flightList[i].getEndingAirport() << "	" <<
		flightList[i].getNumPassengers() << "	" <<
		flightList[i].getStatus() << "	" << endl;
	}
	flights.close();
	return;
}

// Loads information from a file, and checks for changes based on time
void flights::loadFlight()
{
	int i;
	string junk;

	string flightID;
	string planeID;
	int pilotID;
	int coPilotID;
	int crewID[3];
	double startTime;
	double endTime;
	string startingAirport;
	string endingAirport;
	int numPassengers;
	string status;

	ifstream flights;
	flights.open("flights.txt");
	flight temp;

	flightCnt = 0;

	while(!flights.eof())
	{
		getline(flights, flightID, '	');

		if(flightID.empty())
		{
			break;
		}

		getline(flights, planeID, '	');

		flights >> pilotID;
		getline(flights, junk, '	');

		flights >> coPilotID;
		getline(flights, junk, '	');

		for(i = 0; i < 3; i++)
		{
			flights >> crewID[i];
			getline(flights, junk, '	');
		}

		flights >> startTime;
		getline(flights, junk, '	');

		flights >> endTime;
		getline(flights, junk, '	');

		getline(flights, startingAirport, '	');
		getline(flights, endingAirport, '	');

		flights >> numPassengers;
		getline(flights, junk, '	');

		getline(flights, status, '\n');

		temp.setFlightID(flightID);
		temp.setPlaneID(planeID);
		temp.setPilotID(pilotID);
		temp.setCoPilotID(coPilotID);
		temp.setCrewID(crewID);
		temp.setStartTime(startTime);
		temp.setEndTime(endTime);
		temp.setStartingAirport(startingAirport);
		temp.setEndingAirport(endingAirport);
		temp.setNumPassengers(numPassengers);
		temp.setStatus(status);

		flightList.push_back(temp);
		flightCnt++;
	}
	flights.close();
	// Checks the status of the newly loaded information, to check for any time-based changes
	checkStatus();

	return;	
}

