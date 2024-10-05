#pragma once
#include "Defs.h"
#include "Truck.h"
#include "Queue.h"
#include "Event.h"
#include "PriQ.h"
#include "Linkedlist.h"
#include"ListBag.h"
#include "Cargo.h"
#include "UI.h"
#include<fstream>
#include<string>
#include<iostream>
 using namespace std;
class UI; 
// it is the maestro of the project
class Company  
{	
private:
	
	/*UI* pUI;*/ ///UI pointer to call it to open and read the file
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

    ////////////////waiting cargos/////////////////
	PriQ<Cargo*> VIPCargo_Q;  //Queue for VIP Cargos
	LinkedList <Cargo*> NormalCargo_L;  //List for Normal Cargos
	Queue <Cargo*> SpecialCargo_Q;  //Queue for Sprcial Cargos

    /////////////waiting trucks////////////////////////
	Queue<Truck*> Truck_V_Q;  //Queue for VIP trucks
	Queue<Truck*> Truck_N_Q;  //Queue for Normal trucks
	Queue<Truck*> Truck_S_Q;  //Queue for Special trucks

	/////////////////Moving Trucks///////////////////
	PriQ<Truck*> Moving_Trucks_Q; //Queue for moving trucks

	///////////////loading cargos////////////////
	PriQ<Cargo*> Loading_Cargo_Q;   

	///////////////loading trucks////////////////
	
	LinkedList<Truck*> loading_Trucks_B;
	

	///////////////unavailable trucks////////////////
	LinkedList<Truck*> Unavailable_Trucks_B;  


	///////////////delivered cargos////////////////
	Queue <Cargo*> Cargos_DELI;  //Queue for Cargos delieverd

	///////////////variables////////////////
	int DAY;
	int HOUR;
	int cwait;
	int cload;
	int cdelv;
	int Tload;
	int timestep;
	int Truck_count;
	int Tcheckup;
	int nT ;
	int nS ;
	int nV ;
	int totalcargonumber;
	int NcargoNUM;
	int ScargoNUM;
	int NCFORAUTO;
	int AutoPN;
	int VcargoNUM;
	int maxD;
	int LDv;
	int LDs;
	int LDn;
	int frontOT;  //front of truck
	int deliveredcheck;

	ifstream InFile;
	ofstream OutFile;

 //end of private  
public:
   
	Company();
	~Company();

	/////////////////SETTER & GETTER///////////////////////
	//1
	void setdel(int D);
	void setwait(int wait);
	void settload(int l);
	void settcheckup(int c);

	int getwait();
	int getcload();
	int getdel(); 
	int gettload(); 
	int gettcheckup();
	int getAutoPN();
	//2
	void setHour(int hour);
	void setDay(int day);

	int getHour();
	int getDay();

	//3
	void setTotalCargoNumber(int tc);
	void setNcargoNUM(int C);
	void setScargoNUM(int C);
	void setVcargoNUM(int C);

	int getTotalCargoNumber();
	int getNcargoNUM();
	int getScargoNUM();
	int getVcargoNUM();

	//4
	void settimestep(int ts);
	int gettimestep();

	//5
	void settruckc(int c);
    void setNTruckNUM(int C);
	void setSTruckNUM(int C);
	void setVTruckNUM(int C);

	int gettruckc();
	int getNtruckNUM();
	int getStruckNUM();
	int getVtruckNUM();

	/////////////////Truck related//////////////////////////
	void LoadTruck(CAR_TYPE C_Type,Truck*pT  );
	//void MovingTruck(Truck* pT);
	void TruckMaint(Truck* pTru);
	void TruckMaintdone(Truck* pTru);

	/////////////////PRINTING CONTROL//////////////////////////
	void PrintWait_S();
	void PrintWait_V();
	void PrintWait_N();

    void PrintDeliv_S();
	void PrintDeliv_V();
	void PrintDeliv_N();

	void PrintEMPTYT_S();
	void PrintEMPTYT_V();
	void PrintEMPTYT_N();
	LinkedList<Truck*> PrintCheckupTruck();
 
	void PrintHour();

	////////////////////////EVENTS & RELATETED FUNCTIONS //////////////////////////////

	void ExecuteEvents(int day,int hour );	//executes all events at current timestep
 

	void Wrapper_Arrival(CAR_TYPE& C_Type, int& day,int& hour, int& id,int&distance,int&loadtime,int&cost);
	void Wrapper_Cancelation(int& day, int& hour, int& id);
	void Wrapper_Promote(int &day,int& hour, int& id, int& EXTRAM);
	


	bool DeleteCargo(int ID); //to Delete an Cargo
	void AddtoQueue(Cargo* pCargo); //to add Cargo to queue
	void PromoteCargo(int ID); // to promote a normal Cargo 

	///////////////////////////////////MODES////////////////////////////////////////
	void RunSimulation();
	void Simlulation (UI* pUI , PROG_MODE MODE);
	void Step_by_Step_mode( UI* pUI,  PROG_MODE MODE);
	void Interactive_mode(UI* pUI, PROG_MODE MODE);
	void Silent_mode(UI* pUI, PROG_MODE MODE);

	////////////////////////////Save & Load///////////////////////////////////////
	void LoadFile(int& N, int& S, int& V, int& SN, int& SS, int& SV, int& NTC, int& STC, int& VTC, int& J,int& CN,int& CS,int& CV, int& AutoP,int& MaxW, int& M);
	void SaveFile();
};

 