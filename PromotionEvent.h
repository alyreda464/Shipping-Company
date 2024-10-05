#pragma once
#include "Event.h"
class PromotionEvent : public Event
{
	int ExtraMoney;
public:
	//constructor
	PromotionEvent(int day, int hour, int cID, int EXTRAM);

	//execute
	virtual void Execute(Company* pComp);
};

