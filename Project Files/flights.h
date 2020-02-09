#include "flight.h"

class flights
{
	private:
		int flightCnt;
		vector<flight> flightList;

	public:
		flights()
		{
			flightCnt = 0;
		}
		~flights()
		{
			//Nothing to delete in the vector. ALl memory should be handled.
		}
		// Enter functions that take a temp variable to be pushed back into flightList later on.
		void enterFlightID(flight &temp);
		bool enterPlaneID(flight &temp);
		bool enterPilotID(flight &temp);
		bool enterCoPilotID(flight &temp);
		bool enterCrewID(flight &temp);
		void enterStartTime(flight &temp);
		void enterEndTime(flight &temp);
		void enterStartingAirport(flight &temp);
		void enterEndingAirport(flight &temp);
		bool enterNumPassengers(flight &temp);
		void enterStatus(flight &temp);

		// Check the status of flights
		bool checkStatus();
		// Menu functions that are called from the menu
		void menu();
		void addFlight();	
		void deleteFlight();
		void modifyFlight();	
		void printFlight();
		void printAllFlight();
		void searchID();
		void advSearch();
		void storeFlight();
		void loadFlight();

};