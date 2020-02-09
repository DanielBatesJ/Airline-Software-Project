#include "planes.h"

// Gives the user an outline of what options they have, printed when needed.
void planes::printMenu()
{
	cout << "What would you like to do?" << endl <<
	"1.) Add a plane" << endl <<
	"2.) Modify a plane" << endl <<
	"3.) Delete a plane" << endl <<
	"4.) Print all plane (Model and Tail Number)" << endl <<
	"5.) Print all information about a specific plane" << endl <<
	"6.) Search by plane ID" << endl <<
	"7.) Advanced Search (Search by specific fields)" << endl <<
	"8.) Save to Disk" << endl <<
	"9.) Load from Disk" << endl <<
	"10.) Exit" << endl << endl;
}

// All the options for user to take advantage of to jump into different function
void planes::menu()
{
	int input;
	bool check = false;

	cout << endl;
	printMenu();

	do
	{
		cin >> input;

		cin.ignore();
		if((input > 0) && (input < 11))
		{
			switch(input)
			{
				case 1:{
					addPlane();
					printMenu();
					break;
				}
				case 2:{
					modifyPlane();					
					printMenu();
					break;
				}
				case 3:{
					deletePlane();
					printMenu();
					break;
				}
				case 4:{
					printPlanes();
					printMenu();
					break;
				}
				case 5:{
					printAllPlanes();
					printMenu();
					break;
				}
				case 6:{
					searchTailNum();
					printMenu();
					break;
				}
				case 7:{
					advSearch();
					printMenu();
					break;
				}
				case 8:{
					storePlane();
					printMenu();
					break;
				}
				case 9:{
					loadPlane();
					printMenu();
					break;
				}
				case 10:{
					check = true;
					break;
				}
			}
		}
	}while(check != true);	
}

void planes::enterMake(plane &temp)
{
	string make;
	cout << "Enter the Make of your plane: " << endl;
	getline(cin, make);
	temp.setMake(make);
}

void planes::enterModel(plane &temp)
{
	int model;
	cout << "Enter the Model Number of your plane: "<< endl;
	cin >> model;
	cin.ignore();
	temp.setModel(model);
}

void planes::enterTail(plane &temp)
{
	string tail;
	cout << "Enter the Tail Number (Combination of letters and numbers): "<< endl;
	getline(cin, tail);
	temp.setTailNum(tail);
}

void planes::enterSeats(plane &temp)
{
	int seat;
	cout << "Enter the Number of Seats in your plane: " << endl;
	cin >> seat;
	cin.ignore();
	temp.setSeatNum(seat);
}

void planes::enterRange(plane &temp)
{
	int range;
	cout << "Enter the Range of your plane (In miles): "<< endl;
	cin >> range;
	cin.ignore();
	temp.setRange(range);
}

//Originally allowed for choice, but was reworked in later versions to allow for automatic status changes based on flights
void planes::enterStatus(plane &temp)
{
	temp.setStatus("Avalible");
}

void planes::addPlane()
{
	// Runs through the enter functions with the temp varible.
	plane temp;
	enterMake(temp);
	enterModel(temp);
	enterTail(temp);
	enterSeats(temp);
	enterRange(temp);
	enterStatus(temp);

	// Adds the temp varible to the list, increments the crew count
	planeList.push_back(temp);
	planeCnt++;
	// Auto runs the store function
	storePlane();

	return;
}

// Finds the plane specified, and removes the object from the vector
void planes::deletePlane()
{
	int i;
	string input;

	cout << "Enter tail number" << endl;
	getline(cin, input);

	for(i = 0; i < planeCnt; i++)
	{
		if(input == planeList[i].getTailNum())
		{
			cout << "Plane Found!" << endl;
			planeList.erase(planeList.begin() + i);
			// Decremenets the plane count
			planeCnt--;
			storePlane();
			return;
		}
	}
	cout << "Tail number " << input << " not found, please try again." << endl;
}

// Gives the user options to change information about a plane that isn't critical to other functionality
void planes::modifyPlane()
{
	int i;
	string input;
	int input2;
	bool check = false;

	string make;
	int model;
	string tailNumber;
	int seatNum;
	int range;
	int status;

	cout << "Enter tail number" << endl;
	getline(cin, input);
	//Loop to find the entered ID
	for(i = 0; i < planeCnt; i++)
	{
		if(planeList[i].getTailNum() == input)
		{
			cout << "Plane Found!" << endl;
			cout << "What would you like to edit?" << endl <<
			"1.) Make" << endl <<
			"2.) Model" << endl <<
			"3.) Seat Number" << endl <<
			"4.) Range" << endl;
			
			do{
				cin >> input2;
				cin.ignore();
				switch(input2)
				{
					//A very slightly modified version of the enter functions, to have them more suitable for modification.
					case 1: 
					{
						cout << "Enter the new Make of your plane: " << endl;
						getline(cin, make);
						planeList[i].setMake(make);
						storePlane();
						return;
					}
					case 2: 
					{
						cout << "Enter the new Model Number of your plane: "<< endl;
						cin >> model;
						planeList[i].setModel(model);	
						storePlane();
						return;					
					}
					case 3: 
					{
						cout << "Enter the new Number of Seats in your plane: " << endl;
						cin >> seatNum;
						planeList[i].setSeatNum(seatNum);	
						storePlane();
						return;					
					}
					case 4: 
					{
						cout << "Enter the new Range of your plane (In miles): "<< endl;
						cin >> range;
						planeList[i].setRange(range);
						storePlane();
						return;			
					}
					default: {
						cout << "Invalid input, try again" << endl;
						check = false;
						break;
					}
				}
			}while(check != true);
			cout << "Plane Not Found" << endl;
			return;
		}
	}	
}

// Prints out basic information about all planes
void planes::printPlanes()
{
	int i;
	if(planeCnt == 0)
	{
		cout << "No planes found." << endl;
		return;
	}
	for(i = 0; i < planeCnt; i++)
	{
		cout << "Plane #" << i+1 << ": " << planeList[i].getModel() << " - " << planeList[i].getTailNum() << endl;
	}
	cout << endl;
}

// Prints all information about a specific plane
void planes::printAllPlanes()
{
	int i;
	string input;
	cout << "Enter the Tail Number for the plane you want more information on: ";
	getline(cin, input);
	for(i = 0; i < planeCnt; i++)
	{
		if(planeList[i].getTailNum() == input)
		{
			cout << "Make		- " << planeList[i].getMake() << endl <<
			"Model 		- " << planeList[i].getModel() << endl <<
			"Tail Number 	- " << planeList[i].getTailNum() << endl <<
			"Seat Number 	- " << planeList[i].getSeatNum() << endl <<
			"Range 		- " << planeList[i].getRange() << endl <<
			"Status		- " << planeList[i].getStatus() << endl << endl;
			return;
		}
	}
	cout << "Plane not found" << endl;

}

// Similar to the print function, but with nicer formatting.
void planes::searchTailNum()
{
	int i;
	string input;
	cout << "Enter the Tail Number:";
	getline(cin, input);
	for(i = 0; i < planeCnt; i++)
	{
		if(planeList[i].getTailNum() == input)
		{
			cout << endl << "Plane #" << planeList[i].getTailNum() << " is currently " << planeList[i].getStatus() << "." << endl <<
			"The plane has a range of " << planeList[i].getRange() << " and a seat capacity of " << planeList[i].getSeatNum() << endl << endl;
			return;
		}
	}
	cout << "Plane not found" << endl;
}

// Allows the user to search by a specific attribute
void planes::advSearch()
{
	int i;
	int choice;
	int choice2;
	bool check = false;
	bool check2 = false;

	cout << "Would you like to search by Status (Availability), Seat Number or Range?" << endl <<
	"1.) Status" << endl <<
	"2.) Seat Number" << endl <<
	"3.) Range" << endl;

	do{
		cin >> choice;
		cin.ignore();
		switch(choice)
		{
			case 1:{
				cout << "What type of status would you like to find?" << endl << 
				"1. Avalible" << endl << 
				"2. Scheduled" << endl << 
				"3. In-flight" << endl <<
				"4. Repair" << endl;
				do
				{
					cin >> choice2;
					cin.ignore();
					switch(choice2)
					{
						case 1:{
							cout << "Avalible:" << endl;
							for(i = 0; i < planeCnt; i++)
							{
								if(planeList[i].getStatus() == "Avalible")
								{
									cout << "Plane #" << planeList[i].getTailNum() << " with " << planeList[i].getSeatNum() << " seats and a range of " << planeList[i].getRange() << endl;
								}
							}
							return;
						}
						case 2:{
							cout << "Scheduled:" << endl;
							for(i = 0; i < planeCnt; i++)
							{
								if(planeList[i].getStatus() == "Scheduled")
								{
									cout << "Plane #" << planeList[i].getTailNum() << " with " << planeList[i].getSeatNum() << " seats and a range of " << planeList[i].getRange() << endl;
								}
							}
							return;
						}
						case 3:{
							cout << "In-flight:" << endl;
							for(i = 0; i < planeCnt; i++)
							{
								if(planeList[i].getStatus() == "In-flight")
								{
									cout << "Plane #" << planeList[i].getTailNum() << " with " << planeList[i].getSeatNum() << " seats and a range of " << planeList[i].getRange() << endl;
								}
							}
							return;
						}
						case 4:{
							cout << "Repair:" << endl;
							for(i = 0; i < planeCnt; i++)
							{
								if(planeList[i].getStatus() == "Repair")
								{
									cout << "Plane #" << planeList[i].getTailNum() << " with " << planeList[i].getSeatNum() << " seats and a range of " << planeList[i].getRange() << endl;
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
				int num;
				cout << "What is the minimum Number of Seats you need:";
				cin >> num;
				cin.ignore();
				for(i = 0; i < planeCnt; i++)
				{
					if(planeList[i].getSeatNum() >= num)
					{
						cout << "Plane #" << planeList[i].getTailNum() << " with " << planeList[i].getSeatNum() << " seats and a range of " << planeList[i].getRange() << " has enough seats for your flight" << endl;
					}
					else
					{
						cout << "Plane #" << planeList[i].getTailNum() << " does not have enough seats for your flight." << endl;
					}
				}
				return;
			}
			case 3:{
				int num;
				cout << "What is the minimum Range for your flight:";
				cin >> num;
				cin.ignore();
				for(i = 0; i < planeCnt; i++)
				{
					if(planeList[i].getRange() >= num)
					{
						cout << "Plane #" << planeList[i].getTailNum() << " with " << planeList[i].getSeatNum() << " seats and a range of " << planeList[i].getRange() << " has enough range for your flight" << endl;
					}
					else
					{
						cout << "Plane #" << planeList[i].getTailNum() << " does not have the range for your flight." << endl;
					}
				}
				return;
			}
			default:{
				cout << "Invalid input, try again." << endl;
			}
		}
	}while(check != true);

}

// Called from flights.cpp to check the validity of the plane
bool planes::flightPlaneSearch(string tn)
{
	int i;
	for(i = 0; i < planeCnt; i++)
	{
		if(planeList[i].getTailNum() == tn)
		{
			cout << "Plane found!" << endl;
			if(planeList[i].getStatus() == "Avalible")
			{
				cout << "Plane is Avalible!" << endl;
				return true;
			}
			cout << "Plane is not currently Avalible" << endl;
			return false;
		}
	}
	cout << "Plane not found, invalid Tail Number." << endl;
	return false;
}

bool planes::flightCheckSeats(string tn, int num)
{
	int i;
	for(i = 0; i < planeCnt; i++)
	{
		if(planeList[i].getTailNum() == tn)
		{
			if(planeList[i].getSeatNum() >= num)
			{
				cout << "Plane has enough seats!" << endl;
				return true;	
			}
			cout << "Plane does not have enough seats.\n";
			return false;
		}

	}
	cout << "Unknown Error\n";
	return false;
}

// Updates information about a planed based on changes in flights.cpp
void planes::updatePlane(string tailnum, string status)
{
	int i;
	for(i = 0; i < planeCnt; i++)
	{
		if(planeList[i].getTailNum() == tailnum)
		{
			planeList[i].setStatus(status);
		}
	}
}

// Stores all the information in the vector to a file, called automatically when important information is being added/deleted/changed
void planes::storePlane()
{
	int i;

	ofstream planes;
	// Note: Overrides the data every time it's called, make backups
	planes.open("planes.txt");	

	for(i = 0; i < planeCnt; i++)
	{
		planes << planeList[i].getMake() << "	" <<
		planeList[i].getModel() << "	" <<
		planeList[i].getTailNum() << "	" <<
		planeList[i].getSeatNum() << "	" <<
		planeList[i].getRange() << "	" <<
		planeList[i].getStatus() << endl;
	}
	planes.close();
}

// Loads all plane information from a file
void planes::loadPlane()
{
	int i;
	string junk;

	string make;
	int model;
	string tailNumber;
	int seatNum;
	int range;
	string status;

	ifstream planes;
	planes.open("planes.txt");
	plane temp;
	// Reset the counter
	planeCnt = 0;

	while(!planes.eof())
	{
		getline(planes, make, '	');

		if(make.empty())
		{
			break;
		}

		planes >> model;
		getline(planes, junk, '	');

		getline(planes, tailNumber, '	');

		planes >> seatNum;
		getline(planes, junk, '	');

		planes >> range;
		getline(planes, junk, '	');

		getline(planes, status, '\n');

		temp.setMake(make);
		temp.setModel(model);
		temp.setTailNum(tailNumber);
		temp.setSeatNum(seatNum);
		temp.setRange(range);
		temp.setStatus(status);

		planeList.push_back(temp);
		planeCnt++;
	}
	planes.close();
	return;	
}
