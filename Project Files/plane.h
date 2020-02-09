#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Class definition for crew
class plane
{
	private:
		string make;
		int model;
		string tailNumber;
		int seatNum;
		int range;
		string status;
	public:
		plane()
		{
			model = 0;
			seatNum = 0;
			range = 0;
		}
		string getMake();
		void setMake(string m);
		int getModel();
		void setModel(int m);
		string getTailNum();
		void setTailNum(string t);
		int getSeatNum();
		void setSeatNum(int s);
		int getRange();
		void setRange(int r);
		string getStatus();
		void setStatus(string s);
};