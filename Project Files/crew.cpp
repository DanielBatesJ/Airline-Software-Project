#include "crews.h"

//Set and get functions
string crew::getName(){
	return name;
}

void crew::setName(string n){
	name = n;
}

int crew::getID(){
	return idNum;
}

void crew::setID(int ID){
	idNum = ID;
}

string crew::getType(){
	return type;
}

void crew::setType(string t){
	type = t;
}

string crew::getStatus(){
	return status;
}

void crew::setStatus(string s){
	status = s;
}

string cabinCrew::getPosition(){
	return position;
}

void cabinCrew::setPosition(string pos){
	position = pos;
}

string coPilot::getRating(){
	return ratingCode;
}

void coPilot::setRating(string rating){
	ratingCode = rating;
}

double coPilot::getHours(){
	return flightHours;
}

void coPilot::setHours(double hours){
	flightHours = hours;
}

string pilot::getRating(){
	return ratingCode;
}

void pilot::setRating(string rating){
	ratingCode = rating;
}

double pilot::getHours(){
	return flightHours;
}

void pilot::setHours(double hours){
	flightHours = hours;
}