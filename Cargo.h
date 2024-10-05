#pragma once
#include "Defs.h"
#include <iostream>
using namespace std;
class Truck; 
class Cargo
{
    friend ostream &operator<<(ostream&, Cargo*); //the friend function for operator overloading
	
protected:
    int ID;         //Each order has a unique ID 
    CAR_TYPE type;        //order type: Normal, Special, VIP
    CAR_STATUS status;    //waiting, in-service, done
    int Distance;    //The distance (in km) between the cargo location and the company
    int PreparationTimed,PreparationTimeh, CDTH ,waitingd ,waitingh,MTH; // all time variable needed
	int Cost; // cost of the cargo
	int LoadUNTime;//in hours load and unload
	int Priority;
	Truck* AssignedTruck;  
public:
    //constructors
   Cargo(int id,CAR_TYPE C_Type);
   Cargo(int id, CAR_TYPE C_Type,int day, int hour, int dis,int load, int cost );

   //ID of cargo
   int GetID();
   void SetID(int id);

   //priority related functions
   	void setPriority(Cargo* c);
	int getPriority() const;

   //Type of cargo
   CAR_TYPE GetType() const;
   void setType(CAR_TYPE t); // in case we wanted to promote a cargo from normal to VIP

   // distance of cargo
   int getDistance() const;
   void setDistance(int d);

   //status of cargo
   CAR_STATUS getStatus() const;
   void setStatus(CAR_STATUS s);

   //cost related
   void setCost(int c);
   double getCost() const;

   //load/unload time of cargo
   void SetLoadUNTime(int time);
   int GetLoadUNTime();

   //moving time
   void SetMoveTime(int HOUR);
   int getMTH();

   //waiting time 
   int getwaitingd();
   int getwaitingh();

   //delivertime of cargos
   void setCDTH(); //sets cargo delivery time hour
   int getCDTH(); //gets cargo delivery time hour

   //preparation time
   void setPreparationTime(int day,int hour);
   int getPreparationTimed();
   int getPreparationTimeh();
   
   //AssignedTruck
   void assigntruck(Truck* truck );
   Truck* getassignedTruck();

   //set waiting time
   void setWaitingH();

   //destructor
   virtual ~Cargo();
 
};




