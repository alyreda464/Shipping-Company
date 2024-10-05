#include "Cargo.h"
#include "Company.h"

//the friend function for operator overloading
ostream& operator<<(ostream& output, Cargo* pcar)
{
    output << pcar->GetID();
    return output;
}

//constructors & destructor
Cargo::Cargo(int id,CAR_TYPE C_Type)
{
	 ID = id;
    type = C_Type;
    status = WAITING;
}

Cargo::Cargo(int id, CAR_TYPE C_Type,int day, int hour, int dis,int load, int cost )
{
    ID = id;
    type = C_Type;
	Distance=dis;
	Cost=cost;
	LoadUNTime=load;
	PreparationTimed=day;
	PreparationTimeh=hour;
    status = WAITING;

}

Cargo::~Cargo()
{
}

//priority related functions to set priority equation
void Cargo::setPriority(Cargo* c)
{
	Priority = c->getCost() / (c->getDistance() * (c->getPreparationTimeh() +( c->getPreparationTimed() * 24 )));
}

int Cargo::getPriority() const
{
	return Priority;
}


//ID of cargo
int Cargo::GetID()
{
    return ID;
}

void Cargo::SetID(int id)
{
  ID=id;
}

//Type of cargo
void Cargo::setType(CAR_TYPE t)
{
    type = t;
}

CAR_TYPE Cargo::GetType() const
{
    return type;
}

// distance of cargo
void Cargo::setDistance(int d)
{
    Distance = d > 0 ? d : 0;
}

int Cargo::getDistance() const
{
    return Distance;
}

//status of cargo
void Cargo::setStatus(CAR_STATUS s)
{
    status = s;
}

CAR_STATUS Cargo::getStatus() const
{
    return status;
}



//cost related
void Cargo::setCost(int c)
{
	Cost = c;
}

double Cargo::getCost() const
{
	return Cost;
}

//load/unload time of cargo
void Cargo::SetLoadUNTime(int time)
{
    LoadUNTime = time;
}

int Cargo::GetLoadUNTime()
{
    return LoadUNTime;
}

//moving time
void Cargo:: SetMoveTime(int HOUR)
{
	MTH=HOUR;
}

int Cargo::getMTH()
{
	return MTH;
}

//sets waiting time
void Cargo::setWaitingH()
{
    waitingh = getMTH() - getPreparationTimeh();
}

//deliver time of cargos
void Cargo::setCDTH()
{
    CDTH = AssignedTruck->getMovingt() + getDistance() / AssignedTruck->getSpeed() + GetLoadUNTime();
}

int Cargo::getCDTH()
{
     return CDTH;
}


//waiting time
int Cargo::getwaitingd()
{
	return waitingd;
}
int Cargo::getwaitingh()
{
	return waitingh;
}

// assigntruck related
void Cargo::assigntruck(Truck* truck )
{
    this->AssignedTruck = truck;  
  
}
Truck* Cargo::getassignedTruck()
{
	return AssignedTruck;
}

//preparation time
void Cargo::setPreparationTime(int day,int hour)
{
    PreparationTimed = day  ;
	PreparationTimeh = hour;
}

int Cargo::getPreparationTimed()
{
    return PreparationTimed;
}

int Cargo::getPreparationTimeh()
{
    return PreparationTimeh;
}