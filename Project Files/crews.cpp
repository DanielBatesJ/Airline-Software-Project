 #include "crews.h"

// Outline that is printed out when needed, telling the user what options they have 
void printmenu()
{
	cout << "What would you like to do?" << endl <<
	"1.) Add a crew Memeber" << endl <<
	"2.) Modify a crew Member" << endl <<
	"3.) Delete a crew Member" << endl <<
	"4.) Print all Crew Members (Name and ID)" << endl <<
	"5.) Print all information about a Crew Member" << endl <<
	"6.) Search by crew ID" << endl <<
	"7.) Search by other factors (Availability and Type)" << endl <<
	"8.) Store to a file" << endl <<
	"9.) Load from a file" << endl <<
	"10.) Exit" << endl << endl;

}

// Menu that gives options to the user on what functions to enter.
void crews::menu()
{
	int input;
	bool check = false;
	printmenu();
	do
	{
		cin >> input;
		cin.ignore();
		if((input > 0) && (input < 11))
		{
			switch(input)
			{
				case 1:{
					addCrew();
					printmenu();
					break;
				}
				case 2:{
					modifyCrew();
					printmenu();
					break;
				}
				case 3:{
					deleteCrew();
					printmenu();
					break;
				}
				case 4:{
					printCrew();
					printmenu();
					break;
				}
				case 5:{
					printAllCrew();
					printmenu();
					break;
				}
				case 6:{
					searchID();
					printmenu();
					break;
				}
				case 7:{
					advSearch();
					printmenu();
					break;
				}
				case 8:{
					storeCrew();
					printmenu();
					break;
				}
				case 9:{
					loadCrew();
					printmenu();
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

string crews::enterName()
{
	string name;
	cout << "Enter the name of the Crew Member: " << endl;
	getline(cin, name);
	return name;
}

int crews::enterID()
{
	int id;
	cout << "Enter the Crew Member's ID Number (4 digits, do not end with a 0): " << endl;
	cin >> id;
	cin.ignore();
	return id;
}

// Gives the user options to choose from to prevent chance of user error.
int crews::enterType(string name)
{
	int type;
	bool check = false;
	cout << "Which type of crew is " << name << "?" << endl
	<< "1. Pilot" << endl << "2. Co-Pilot" << endl << "3. Cabin Crew" << endl;
	
	do{
		cin >> type;
		switch(type)
		{
			case 1: {
				return 1;
			}
			case 2: {
				return 2;
			}
			case 3: {
				return 3;
			}
			default: {
				cout << "Invalid input, try again" << endl;
			}
		}
	}while(check != true);
}

void crews::addCrew()
{
	// Runs through the enter functions with the temp varible.
	crew *temp;
	int choice;
	string name;
	int ID;
	string type;
	string rating;
	double hoursFlown;
	bool check = false;

	string status = "Avalible";
	name = enterName();
	ID = enterID();
	choice = enterType(name);

	if(choice == 1)
	{
		cout << "Enter the Pilot's 5 character rating code:";
		do{
			getline(cin, rating);
			if(rating.length() != 5)
			{
				cout << "Code must be 5 characters long, try again.\n";
			}
			else
			{
				check = true;
			}
		}while(check !=true);
		cout << "Enter the Pilot's cumulative hours flown:";
		cin >> hoursFlown;
		type = "Pilot";
		temp = new pilot(name, ID, type, status, rating, hoursFlown);
	}
	else if(choice == 2)
	{
		cout << "Enter the Co-Pilot's 4 character rating code:";
		do{
			getline(cin, rating);
			if(rating.length() != 4)
			{
				cout << "Code must be 4 characters long, try again.\n";
			}
			else
			{
				check = true;
			}
		}while(check !=true);
		cout << "Enter the Co-Pilot's cumulative hours flown:";
		cin >> hoursFlown;
		type = "Co-Pilot";
		temp = new coPilot(name, ID, type, status, rating, hoursFlown);
	}
	else if(choice == 3)
	{

		type = "Cabin Crew";
		//temp = new cabinCrew;
	}	

	//Adds the *temp varible to the list, increments the crew count
	crewList.push_back(temp);
	crewCnt++;
	//Auto runs the store function
	storeCrew();

	return;
}

void crews::deleteCrew()
{
	int i;
	int input;
	// Takes the input for the crew ID, if it's found, erase the element from the vector
	cout << "Enter crew ID" << endl;
	cin >> input;
	for(i = 0; i < crewCnt; i++)
	{
		if(input == crewList[i]->getID())
		{
			cout << "Crew Member Found!" << endl;
			cout << crewList[i]->getName() << " has been deleted.\n";
			crewList.erase(crewList.begin() + i);
			// Derements the crew count
			crewCnt--;
			// Auto stores
			storeCrew();
			return;
		}
	}
	cout << "Crew Member " << input << " not found, please try again." << endl;
}

// Only gave options to modify things that were not important to other functionality. There was originally an option to change status, but that is done automatically
void crews::modifyCrew()
{
	int i;
	int input;
	int input2;
	bool check = false;
	int type;
	string name;

	cout << "Enter crew ID" << endl;
	cin >> input;
	cin.ignore();
	//Loop to find the entered ID
	for(i = 0; i < crewCnt; i++)
	{
		if(input == crewList[i]->getID())
		{
			cout << "Crew Member Found!" << endl;
			//Enter the first of two switch statements
			cout << "What would you like to edit?" << endl <<
			"1.) Type" << endl <<
			"2.) Name" << endl;
			
			do{
				cin >> input2;
				cin.ignore();
				switch(input2)
				{
					//A very slightly modified version of the enter functions, to have them more suitable for modification.
					case 1: 
					{
						cout << "Which type would you like to change to?" << endl
						<< "1. Pilot" << endl << "2. Co-Pilot" << endl << "3. Cabin Crew" << endl;
						do{
							cin >> type;
							cin.ignore();
							switch(type)
							{
								case 1: {
									crewList[i]->setType("Pilot");
									check = true;
									storeCrew();
									break;
								}
								case 2: {
									crewList[i]->setType("Co-Pilot");
									check = true;
									storeCrew();
									break;
								}
								case 3: {
									crewList[i]->setType("Cabin Crew");
									check = true;
									storeCrew();
									break;
								}
								default: {
									cout << "Invalid input, try again" << endl;
									check = false;
									break;
								}
							}
						}while(check != true);
						check = true;
						return;
					}
					// Case 2 and 3 are basic functions that change a single object
					case 2: {
						cout << "What should " << crewList[i]->getName() << "'s new name be:";
						getline(cin, name);
						crewList[i]->setName(name);
						return;
					}
					default: {
						cout << "Invalid input, try again" << endl;
						check = false;
						break;
					}
				}
			}while(check != true);
		}
	}	
	cout << "Crew Member Not Found" << endl;
	return;
}

// Outputs basic information about all crew members.
void crews::printCrew()
{
	int i;
	if(crewCnt == 0)
	{
		cout << "No Crew Members found" << endl << endl;
		return;
	}
	for(i = 0; i < crewCnt; i++)
	{
		cout << crewList[i]->getName() << " - " << crewList[i]->getID() << endl;
	}
	cout << endl;
}

// Prints all information on one specific crew member
void crews::printAllCrew()
{
	int i;
	int input;
	cout << "Enter the crew ID of the crew member you want more information on: ";
	cin >> input;
	//IDK if this causes problems or not
	cin.ignore();
	for(i = 0; i < crewCnt; i++)
	{
		if(crewList[i]->getID() == input)
		{
			cout << "ID	- " << crewList[i]->getID() << endl <<
			"Name 	- " << crewList[i]->getName() << endl <<
			"Type 	- " << crewList[i]->getType() << endl <<
			"Status	- " << crewList[i]->getStatus() << endl << endl;
			return;
		}
	}
	cout << "Crew member not found" << endl;
}

// Similar to the print function, but more friendly.
void crews::searchID()
{
	int i;
	int input;
	cout << "Enter the crew member's ID: ";
	cin >> input;
	cin.ignore();
	for(i = 0; i < crewCnt; i++)
	{
		if(crewList[i]->getID() == input)
		{
			cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\" is currently " << crewList[i]->getStatus() << endl << endl;
			return;
		}
	}
	cout << "Crew member not found" << endl;
}

// Allows the user to search by status and type, to help find members to use in flights down the line.
void crews::advSearch()
{
	int i;
	int choice;
	int choice2;
	bool check = false;
	bool check2 = false;

	cout << "Would you like to search by Status (Availability) or type?" << endl <<
	"1.) Status" << endl <<
	"2.) Type" << endl;
	do{
		cin >> choice;
		switch(choice)
		{
			case 1:{
				cout << "What type of status would you like to find?" << endl << 
				"1. Avalible" << endl << 
				"2. Scheduled" << endl << 
				"3. In-flight" << endl;
				do
				{
					cin >> choice2;
					switch(choice2)
					{
						case 1:{
							cout << "Avalible:" << endl;
							for(i = 0; i < crewCnt; i++)
							{
								if(crewList[i]->getStatus() == "Avalible")
								{
									cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\"" << endl;
								}
							}
							return;
						}
						case 2:{
							cout << "Scheduled:" << endl;
							for(i = 0; i < crewCnt; i++)
							{
								if(crewList[i]->getStatus() == "Scheduled")
								{
									cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\"" << endl;
								}
							}
							return;
						}
						case 3:{
							cout << "In-flight:" << endl;
							for(i = 0; i < crewCnt; i++)
							{
								if(crewList[i]->getStatus() == "In-flight")
								{
									cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\"" << endl;
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
				cout << "What type of crew member would you like to find?" << endl << 
				"1. Pilot" << endl << 
				"2. Co-Pilot" << endl << 
				"3. Cabin Crew" << endl;
				do
				{
					cin >> choice2;
					switch(choice2)
					{
						case 1:{
							cout << "Pilot:" << endl;
							for(i = 0; i < crewCnt; i++)
							{
								if(crewList[i]->getType() == "Pilot")
								{
									cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\"" << endl;
								}
							}
							return;
						}
						case 2:{
							cout << "Co-Pilot:" << endl;
							for(i = 0; i < crewCnt; i++)
							{
								if(crewList[i]->getType() == "Co-Pilot")
								{
									cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\"" << endl;
								}
							}
							return;
						}
						case 3:{
							cout << "Cabin Crew:" << endl;
							for(i = 0; i < crewCnt; i++)
							{
								if(crewList[i]->getType() == "Cabin Crew")
								{
									cout << "Crew Member #" << crewList[i]->getID() << " \"" << crewList[i]->getName() << "\"" << endl;
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
			default:{
				cout << "Invalid input, try again." << endl;
			}
		}
	}while(check != true);
}

// When a Pilot is entered in flights.cpp, we enter this function to check if they can be used.
bool crews::flightPilotSearch(int pID)
{
	int i;
	for(i = 0; i < crewCnt; i++)
	{
		if(crewList[i]->getID() == pID)
		{
			if(crewList[i]->getType() == "Pilot")
			{
				cout << "Pilot Found" << endl;
				if(crewList[i]->getStatus() == "Avalible")
				{
					return true;
				}
				else if(crewList[i]->getStatus() == "In-Flight")
				{
					cout << "Pilot is not avalible." << endl;
					return false;					
				}
				cout << "Pilot is not avalible." << endl;
				return false;	
			}
			else
			{
				cout << "Crew Member is not a Pilot" << endl;
				return false;
			}
		}
	}
	cout << "Crew Member not found" << endl;
	return false;
}

// When a Co-Pilot is entered in flights.cpp, we enter this function to check if they can be used.
bool crews::flightCoPilotSearch(int cpID)
{
	int i;
	for(i = 0; i < crewCnt; i++)
	{
		if(crewList[i]->getID() == cpID)
		{
			if(crewList[i]->getType() == "Co-Pilot")
			{
				cout << "Co-Pilot Found" << endl;
				if(crewList[i]->getStatus() != "Avalible")
				{
					cout << "Co-Pilot is not avalible." << endl;
					return false;
				}
				return true;	
			}
			else
			{
				cout << "Crew Member is not a Co-Pilot" << endl;
				return false;
			}
		}
	}
	cout << "Crew Member not found" << endl;
	return false;
}

// When a Cabin Crew Member is entered in flights.cpp, we enter this function to check if they can be used.
bool crews::flightCrewSearch(int cID)
{
	int i;
	for(i = 0; i < crewCnt; i++)
	{
		if(crewList[i]->getID() == cID)
		{
			if(crewList[i]->getType() == "Cabin Crew")
			{
				cout << "Crew Member Found" << endl;
				if(crewList[i]->getStatus() != "Avalible")
				{
					cout << "Crew Member is not avalible." << endl;
					return false;
				}
				return true;	
			}
			else
			{
				cout << "Crew Member is not a Cabin Crew" << endl;
				return false;
			}
		}
	}
	cout << "Crew Member not found" << endl;
	return false;
}

// Updates the crew's status based on changes in flights.cpp
void crews::updateCrew(int pilot, int copilot, int crew[3], string newStatus)
{
	int i;
	if(crewCnt < 5)
	{
		cout << "ERROR: Not all crew members have been found! Check your crew memebers." << endl;
		return;
	}
	for(i = 0; i < crewCnt; i++)
	{
		if((crewList[i]->getID() == pilot) || (crewList[i]->getID() == copilot) || (crewList[i]->getID() == crew[0]) || (crewList[i]->getID() == crew[1]) || (crewList[i]->getID() == crew[2]))
		{
			crewList[i]->setStatus(newStatus);
			storeCrew();
		}

	}
}

void crews::storeCrew()
{
	// Writes all information of crewList to a file
	// Some test crew members are provided, keep in mind, the program re-writes the file when this function is called, so keep backups
	int i;
	ofstream crews;
	crews.open("crews.txt");	
	crew *temp;
	for(i = 0; i < crewCnt; i++)
	{
		temp = crewList[i];
		if(typeid(crewList[i]) == typeid(pilot))
		{
			pilot *tempP = dynamic_cast<pilot*> (temp);
			crews << tempP->getType() << "	" <<
			tempP->getName() << "	" <<
			tempP->getID() << "	" <<
			tempP->getStatus() << "	" <<
			tempP->getRating() << "	" <<
			tempP->getHours() << endl;
		}
		else if(typeid(crewList[i]) == typeid(coPilot))
		{
			coPilot *tempCP = dynamic_cast<coPilot*> (temp);
			crews << crewList[i]->getType() << "	" <<
			tempCP->getName() << "	" <<
			tempCP->getID() << "	" <<
			tempCP->getStatus() << "	" <<
			tempCP->getRating() << "	" <<
			tempCP->getHours() << endl;			
		}
		else if(typeid(crewList[i]) == typeid(cabinCrew))
		{
			cabinCrew *tempCC = dynamic_cast<cabinCrew*> (temp);
			crews << crewList[i]->getType() << "	" <<
			tempCC->getName() << "	" <<
			tempCC->getID() << "	" <<
			tempCC->getStatus() << "	" <<
			tempCC->getPosition() << endl;			
		}
	}
	crews.close();
	return;
}

// Load Function that is automatically called when important changes are made.
void crews::loadCrew()
{
	int i;
	string junk;

	string name;
	int ID;
	string type;
	string status;
	string rating;
	double hoursFlown;
	string position;

	ifstream crews;
	crews.open("crews.txt");
	crew *temp;
	
	// Resets the crew count
	crewCnt = 0;

	while(!crews.eof())
	{
		getline(crews, type, '	');
		
		if(type == "Pilot")
		{
			getline(crews, name, '	');
			crews >> ID;
			getline(crews, junk, '	');
			getline(crews, status, '	');
			getline(crews, rating, '	');
			crews >> hoursFlown;
			getline(crews, junk, '\n');
			temp = new pilot(name, ID, type, status, rating, hoursFlown);
		}
		else if(type == "Co-Pilot")
		{
			getline(crews, name, '	');
			crews >> ID;
			getline(crews, junk, '	');
			getline(crews, status, '	');
			getline(crews, rating, '	');
			crews >> hoursFlown;
			getline(crews, junk, '\n');			
			temp = new coPilot(name, ID, type, status, rating, hoursFlown);
		}
		else if(type == "Cabin Crew")
		{
			getline(crews, name, '	');
			crews >> ID;
			getline(crews, junk, '	');
			getline(crews, status, '	');
			getline(crews, position, '\n');
			temp = new cabinCrew(name, ID, type, status, position);
		}
		else
		{
			break;
		}
		// This line prevents the errors I was getting from the program reading blank information after the eof should have stopped.
/*		if(name.empty())
		{
			break;
		}
*/

		crewCnt++;
		crewList.push_back(temp);
	}
	crews.close();
	return;	
}