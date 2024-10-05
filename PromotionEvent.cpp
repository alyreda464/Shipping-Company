#include "PromotionEvent.h"
#include "Company.h"

//constructor
PromotionEvent::PromotionEvent(int day,int hour, int cID, int exMoney) :Event(day,hour, cID)
{
	ExtraMoney = exMoney;
}

//execute
void PromotionEvent::Execute(Company* pComp)
{

	pComp->PromoteCargo(getCargoID());
	 
}

