#ifndef __EVENT_H_
#define __EVENT_H_
#include "Defs.h"
 
 
class Company;
class Event
{
protected:
	int EventTimeday;
	int EventTimehour;
	int CargoID;
public:
	//constructors & destructor
    Event();
	Event(int day, int hour, int cID);
	virtual ~Event();

	//hour and day of an event
	int getEventday();
	void setEventhour(int h);
	int getEventhour();

	//getter for cargo id
	int getCargoID();

	//execute "pure virtual"
	virtual void Execute(Company* pComp) = 0;
};
#endif