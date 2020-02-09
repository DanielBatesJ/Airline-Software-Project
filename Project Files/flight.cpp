#include "flights.h"

// Sets and gets

string flight::getFlightID()
{
	return flightID;
}

void flight::setFlightID(string m)
{
	flightID = m;
}

string flight::getPlaneID()
{
	return planeID;
}

void flight::setPlaneID(string pl)
{
	planeID = pl;
}

int flight::getPilotID()
{
	return pilotID;
}

void flight::setPilotID(int pID)
{
	pilotID = pID;
}

int flight::getCoPilotID()
{
	return coPilotID;
}

void flight::setCoPilotID(int cID)
{
	coPilotID = cID;
}

void flight::getCrewID(int crID[3])
{
	int i;
	for(i = 0; i < 3; i++)
	{
		crID[i] = crewID[i];
	}
}

void flight::setCrewID(int crID[3])
{
	int i;
	for(i = 0; i < 3; i++)
	{
		crewID[i] = crID[i];
	}	
}

double flight::getStartTime()
{
	return startTime;
}

void flight::setStartTime(double st)
{
	startTime = st;
}

double flight::getEndTime()
{
	return endTime;
}

void flight::setEndTime(double et)
{
	endTime = et;
}

string flight::getStartingAirport()
{
	return startingAirport;
}

void flight::setStartingAirport(string sA)
{
	startingAirport = sA;
}

string flight::getEndingAirport()
{
	return endingAirport;
}

void flight::setEndingAirport(string eA)
{
	endingAirport = eA;
}

int flight::getNumPassengers()
{
	return numPassengers;
}

void flight::setNumPassengers(int p)
{
	numPassengers = p;
}

string flight::getStatus()
{
	return status;
}

void flight::setStatus(string s)
{
	status = s;
}