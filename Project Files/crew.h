#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

using namespace std;

// Class definition for crew
class crew
{
	private:
		string name;
		int idNum;
		string type;
		string status;
	public:
		crew()
		{
			idNum = 0;
		}
		crew(string n, int id, string t, string s)
		{
			name = n;
			idNum = id;
			type = t;
			status = s;
		}
		virtual ~crew()
		{
			
		}
		string getName();
		void setName(string n);
		int getID();
		void setID(int ID);
		string getType();
		void setType(string t);
		string getStatus();
		void setStatus(string s);
};

class cabinCrew : public crew
{
	private:
		string position;
	public:
		cabinCrew(string n, int id, string t, string s, string p):crew(n, id, t, s)
		{
			position = p;
		}
		string getPosition();
		void setPosition(string pos);
};

class coPilot : public crew
{
	private:
		string ratingCode;
		double flightHours;
	public:
		coPilot(string n, int id, string t, string s, string r, double fh):crew(n, id, t, s)
		{
			ratingCode = r;
			flightHours = fh;
		}
		string getRating();
		void setRating(string rating);
		double getHours();
		void setHours(double hours);
};

class pilot : public crew
{
	private:
		string ratingCode;
		double flightHours;
	public:
		pilot(string n, int id, string t, string s, string r, double fh):crew(n, id, t, s)
		{
			ratingCode = r;
			flightHours = fh;
		}
		string getRating();
		void setRating(string rating);
		double getHours();
		void setHours(double hours);
};