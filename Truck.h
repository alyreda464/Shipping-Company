#pragma once
#include "Defs.h"
#include"Cargo.h"
#include"PriQ.h"

 
class Truck
{
    friend ostream &operator<<(ostream&, Truck*); //the friend function for operator overloading
private:

    int ID; // truck id
    CAR_TYPE type;    // truck type
    TRUCK_Status status; // truck status
    int Speed;        // truck speed
    int Capacity;     // truck capacity
	int Deliveryint; // deivery time interval
    int totalloadtime; //total loading time
    int MaxDistance;  //maximum distance
    int checkuptime; //checkup time of trucks
    int numberofj; // number of journeys
    int MoveTime;  //moving time of truck
    int front; // front of moving cargo list
    int TruckDeliveryT; //truck delivery time
    //PriQ<Cargo*> Loading_Cargo_Q;  // queue to store/load cargos in trucks
    PriQ<Cargo*> Moving_Cargo_Q;  // queue to moving cargos in trucks

public:
    //constructors
    Truck();
    Truck(int id, CAR_TYPE tp, TRUCK_Status ts, int spd, int capacity, int checkup, int j);

    //ID related
    int getID() const;
    void setID(int);

    //related to cargo types
    CAR_TYPE getType() const;
    void setType(CAR_TYPE);
   
    //speed of tuck
	void setSpeed(int s);
	int getSpeed();

    //capacity of truck
    void setCapacity(int CP);

    //related to Max distance of cargos
    void setMaxD(int maxd);
    int getMaxD();

    //related to truck status
    TRUCK_Status getstatus() const;
    void setstatus(TRUCK_Status);

    ////Loading of cargos 
    //void setLoadingC(Cargo* car);
    //template <typename T>
    //T getLoadingC();

    //Moving cargos 
    void setMovingC(Cargo* car);
    template <typename T>
    T getMovingC();
    
    //delivery time of trucks
    void setTDT(int h);
    int getTDT();
    
    //pointer to front of the queue
    int getPF();
    int setPF(Cargo* car);

    //total loading time of truck
    void setLoadingt(int t);
    int getLoadingt();

    //total moving time of truck
    void setMovingt(int t);
    int getMovingt();

    //truck checkup
    void setcheckuptime(int ch);
    int getcheckup();

    //returns number of journeys
    int getnumberofj();

    //delivery interval
    int DI(Cargo*pCAR);

    //gets delivered cargos
    void getDelivC(Cargo* cargo);

    //gets count of cargos
    int getCarcnt();

    //constructor
	virtual ~Truck();
};
