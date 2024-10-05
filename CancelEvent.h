#pragma once
#include "Event.h"
class CancelEvent: public Event
{
	CAR_TYPE* CARType; 
public:
	//constructor and destructor
	CancelEvent(int day,int hour, int cID);
	~CancelEvent();

	//execute
	virtual void Execute(Company* pComp);
};
