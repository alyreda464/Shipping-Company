#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"
class ArrivalEvent : public Event
{   
	int cost;
	int loadtime;
	int carDistance;
	CAR_TYPE CARType;
	int D; //day
	int H; //hour

public:
	//constructor
	ArrivalEvent(CAR_TYPE cType,int day ,int hour, int cID,int dis,int load, int c);

	//execute
	virtual void Execute(Company* pComp);
 };
#endif