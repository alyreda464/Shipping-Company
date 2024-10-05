#include "Truck.h"
//the friend function for operator overloading
class Cargo;
ostream& operator<<(ostream& output, Truck* pTru)
{
    output << pTru->getID();
    return output;
}

//constructors & destructors
Truck::Truck()
{
}

Truck::Truck(int id, CAR_TYPE tp, TRUCK_Status ts, int spd, int capacity, int checkup, int j)
{
    setID(id);
    setType(tp);
    setstatus(ts);
    setSpeed(spd);
    setCapacity(capacity);
    setcheckuptime(checkup);
    numberofj = j;
}

Truck::~Truck()
{
}

//ID related
void Truck::setID(int id)
{
    ID = id;
}

int Truck::getID() const
{
    return ID;
}

//related to truck status
TRUCK_Status Truck::getstatus() const
{
    return status;
}

void Truck::setstatus(TRUCK_Status t)
{
    status = t;
}

//related to cargo types
CAR_TYPE Truck::getType() const
{
    return type;
}

void Truck::setType(CAR_TYPE t)
{
    type = t;
}

//speed of tuck
void Truck::setSpeed(int s)
{
    if (s > 0)
    {
        Speed = s;
    }
}
int Truck::getSpeed()
{
    return Speed;
}

////Loading of cargos 
//void Truck::setLoadingC(Cargo* car)
//{
//
//    Loading_Cargo_Q.enqueue(car , (car->getDistance()) );
//}
//
//template <typename T>
// T Truck::getLoadingC()
//{
//    return Loading_Cargo_Q;
//}


 //total loading time of truck
 void Truck::setLoadingt(int t)
 {
     totalloadtime = t;
 }
 int Truck::getLoadingt()
 {
     return totalloadtime;
 }

 //related to Max distance of cargos
 void Truck::setMaxD(int maxd)
 {
     MaxDistance = maxd;
 }
 int Truck::getMaxD()
 {
     return MaxDistance;
 }

 //truck checkup
    void Truck::setcheckuptime(int ch)
    {
        checkuptime = ch;
    }

    int Truck::getcheckup()
    {
        return checkuptime;
    }

 //returns number of journeys
    int Truck::getnumberofj()
    {
        return numberofj;
    }

 //capacity of truck
	void Truck::setCapacity(int CP)
	{
	Capacity=CP;
	}

    //delivery interval
	int Truck::DI(Cargo* pCAR)
	{
		Deliveryint=( getMaxD()/getSpeed() ) + getLoadingt() + ( getMaxD()/getSpeed() );
	    return 0;
	}


    //total moving time of truck
    void Truck::setMovingt(int t)
    {
        MoveTime = t;
    }
    int Truck::getMovingt()
    {
        return MoveTime;
    }

    //Moving cargos 
    void Truck::setMovingC(Cargo* car)
    {
        car->setStatus(MOVING);
        Moving_Cargo_Q.enqueue(car, (car->getCDTH()));

    }
    template <typename T>
    T Truck::getMovingC()
    {
        return Moving_Cargo_Q;
    }

    //pointer to front of the queue
    int Truck::setPF(Cargo* car)
    {
        Moving_Cargo_Q.peekFront(car);
        front=car->getCDTH();
    }

    int Truck::getPF()
    {
        return front;
    }

    //delivery time of trucks
    void Truck::setTDT(int h)
    {
        TruckDeliveryT = h;
    }
    int Truck::getTDT()
    {
        return TruckDeliveryT;
    }

    //gets delivered cargos
    void Truck::getDelivC(Cargo* cargo)
    {
        Moving_Cargo_Q.dequeue(cargo);
    }

    //gets count of cargos
    int Truck::getCarcnt()
    {
        int var=0;
       var= Moving_Cargo_Q.getCount();
    }