#include "ArrivalEvent.h"
#include "Company.h"

//constructor
ArrivalEvent::ArrivalEvent(CAR_TYPE cType,int day ,int hour, int cID,int dis,int load, int c ) : Event(day,hour,cID)
{
	CARType = cType;
	cost=c;
	loadtime=load;
	carDistance=dis;
	D=day;
	H=hour;
}

//Execute
void ArrivalEvent::Execute(Company* pComp)
{
	 
	Cargo* pCAR = new Cargo (CargoID,CARType);
	pComp->AddtoQueue(pCAR);
	int x = pComp->getwait();
	x++;
	pComp->setwait(x);
}

