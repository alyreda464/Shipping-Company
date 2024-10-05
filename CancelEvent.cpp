#include "CancelEvent.h"
#include "Company.h"

//constructor
CancelEvent::CancelEvent(int day,int hour, int cID) :Event(day,hour, cID)
{
}

//execute
void CancelEvent::Execute(Company* pComp)
{

 pComp->DeleteCargo(getCargoID());
}

//destructor
CancelEvent::~CancelEvent()
{
 
}