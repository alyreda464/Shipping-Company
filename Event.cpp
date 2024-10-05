#include "Event.h"
//constructors & destructor
Event::Event()
{
}
Event::Event(int day,int hour, int cID)
{
	EventTimeday = day;
	EventTimehour = hour; 
	CargoID = cID;
}
Event::~Event()
{
}

//hour and day of an event
int Event::getEventday()
{
	return EventTimeday;
}

void Event::setEventhour(int h)
{
	EventTimehour = h;
}

int Event::getEventhour()
{
	return EventTimehour;
}

//getter for cargo id
int Event::getCargoID()
{
	return CargoID;
}

