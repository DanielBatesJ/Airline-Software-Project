#include "crew.h"

class crews
{
	// Do work to find which crew type it is.
	private:
		int crewCnt;
		vector<crew*> crewList;
	public:
		crews()
		{
			crewCnt = 0;
		}
		~crews()
		{
			// Vector contains no memory that isn't automatically cleaned up
		}
		// Enter functions used in addCrew(), they take a temporary variable of type crew, that is passed by reference, to be pushed back eventually
		string enterName();
		int enterID();
		int enterType(string name);

		// Functionality outlined in the non-member function printMenu()
		void menu();
		void addCrew();
		void deleteCrew();
		void modifyCrew();
		void printCrew();
		void printAllCrew();
		void searchID();
		void advSearch();
		void storeCrew();
		void loadCrew();

		// Returns a bool to check the validity of the crew entered in flights.
		bool flightPilotSearch(int pID);
		bool flightCoPilotSearch(int cpID);
		bool flightCrewSearch(int cID);
		// Updates the crew members on a flight based off the status of the flight.
		void updateCrew(int pilot, int copilot, int crew[3], string newStatus);
};