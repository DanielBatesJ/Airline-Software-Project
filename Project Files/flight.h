#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

// Flight class definition
class flight
{
	private:
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

	public:
		flight()
		{
			startTime = 0;
			endTime = 0;
			numPassengers = 0;
		}
		string getFlightID();
		void setFlightID(string m);
		string getPlaneID();
		void setPlaneID(string pl);
		int getPilotID();
		void setPilotID(int pID);
		int getCoPilotID();
		void setCoPilotID(int cID);
		void getCrewID(int crID[3]);
		void setCrewID(int crID[3]);
		double getStartTime();
		void setStartTime(double st);
		double getEndTime();
		void setEndTime(double et);
		string getStartingAirport();
		void setStartingAirport(string sA);
		string getEndingAirport();
		void setEndingAirport(string eA);
		int getNumPassengers();
		void setNumPassengers(int p);
		string getStatus();
		void setStatus(string s);
};