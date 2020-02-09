#include "plane.h"

class planes
{
	private:
		int planeCnt;
		vector<plane> planeList; 
	public:
		planes()
		{
			planeCnt = 0;
		}
		~planes()
		{
			//For object pointers
			planeList.erase(planeList.begin(), planeList.end());
		}
		// Enter functions used in addCrew(), they take a temporary variable of type crew, that is passed by reference, to be pushed back eventually
		void enterMake(plane &temp);
		void enterModel(plane &temp);
		void enterTail(plane &temp);
		void enterSeats(plane &temp);
		void enterRange(plane &temp);
		void enterStatus(plane &temp);

		// Functionality outlined in the non-member function printMenu()
		void printMenu();
		void menu();
		void addPlane();
		void deletePlane();
		void modifyPlane();
		void printPlanes();
		void printAllPlanes();
		void searchTailNum();
		void advSearch();
		void storePlane();
		void loadPlane();

		// Returns a bool to check the validity of the plane entered in flights.
		bool flightPlaneSearch(string tn);
		bool flightCheckSeats(string tn, int num);
		// Updates the information for a plaane when changes are made in flights.cpp
		void updatePlane(string tailnum, string status);
};