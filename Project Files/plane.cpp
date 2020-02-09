#include "plane.h"

// All set and get functions
string plane::getMake()
{
	return make;
}

void plane::setMake(string m)
{
	make = m;
}

int plane::getModel()
{
	return model;
}

void plane::setModel(int m)
{
	model = m;
}

string plane::getTailNum()
{
	return tailNumber;
}

void plane::setTailNum(string t)
{
	tailNumber = t;
}

int plane::getSeatNum()
{
	return seatNum;
}

void plane::setSeatNum(int s)
{
	seatNum = s;
}

int plane::getRange()
{
	return range;
}

void plane::setRange(int r)
{
	range = r;
}

string plane::getStatus()
{
	return status;
}

void plane::setStatus(string s)
{
	status = s;
}
