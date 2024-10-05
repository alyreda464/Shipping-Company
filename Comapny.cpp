#include <cstdlib>
#include <time.h>
#include <iostream>
#include<string>
#include "Company.h"
#include "Cargo.h"
#include "Event.h"
#include"UI.h"
#include"ArrivalEvent.h"
#include"CancelEvent.h"
#include"PromotionEvent.h"
#include"Defs.h"
using namespace std;

Company::Company() 
{      
	HOUR = 0;
	DAY = 1;
	cwait = 0;
	cload=0;
	cdelv=0;
	Tload=0;
	Tcheckup=0;
	Truck_count=0;
	timestep=0;
	totalcargonumber=0;
	NcargoNUM=0;
	NCFORAUTO=0;
	ScargoNUM=0;
	VcargoNUM=0;
    AutoPN=0;
	 maxD = 0;
     LDv = 0;
    LDs = 0;
    LDn = 0;
	deliveredcheck = 0;
    frontOT = 0; //front of truck
}

 // Executes events
void Company::ExecuteEvents(int day,int hour)
{
	Event *pE;
	
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if (pE->getEventhour() < 5 || pE->getEventhour() > 23)
		{
			pE->setEventhour(5);
		}

		if (pE->getEventday() == day && pE->getEventhour() == hour)
		{
			pE->Execute(this);
			EventsQueue.dequeue(pE);	//remove event from the queue
			delete pE;		//deallocate event object from memory
		}
		else break;
	}
	 
}



//Wrapper function for arrival event
void Company::Wrapper_Arrival(CAR_TYPE& C_Type, int& day,int& hour, int& id,int&distance,int&loadtime,int&cost )
{
	Event* pE;
	pE = new ArrivalEvent(C_Type,day,hour,id,distance,loadtime,cost);
	EventsQueue.enqueue(pE);
}

// Wrapper function for cancel event
void Company::Wrapper_Cancelation(int& day,int&hour, int& id)
{
	Event* pE;
	pE = new CancelEvent(day,hour, id);
	EventsQueue.enqueue(pE);
}

// Wrapper function promotion event
void Company::Wrapper_Promote(int& day,int& hour, int& id, int& EXTRAM)
{
	Event* pE;
	pE = new PromotionEvent(day,hour,id,EXTRAM);
	EventsQueue.enqueue(pE);
}

 // distructor
Company::~Company()
{
		 
}
 
 //to Delete a Cargo
bool Company::DeleteCargo(int ID)
{
	Cargo* pCAR = NormalCargo_L.GetCargoFromID(ID);     //to look for the Cargo to be deleted
	if (pCAR)
	{
		CAR_STATUS status = pCAR->getStatus();

		if (status == WAITING)
			{
			cwait--;
			return NormalCargo_L.DeleteNode(pCAR);        // To delete the Cargo  
	}
	}
	return false;
}


//Adding Cargo to a queue
void Company::AddtoQueue(Cargo* pCAR)
{
	CAR_TYPE type = pCAR->GetType();
 

	switch (type)
	{
	case TYPE_NRM:

		NormalCargo_L.InsertEnd(pCAR);
	
		
		break;
		
	case TYPE_SPC:

		SpecialCargo_Q.enqueue(pCAR);
	
		break;

	case TYPE_VIP:
		     
			VIPCargo_Q.enqueue(pCAR,pCAR->getPriority());
	
		break;
		
	default:

		return ;

	}
	 
}

// to promote a normal Cargo
void Company:: PromoteCargo(int ID)
{
	Cargo* pCargo = NormalCargo_L.GetCargoFromID(ID);
	if (pCargo)
	{
		Cargo* TempCargo = pCargo;
		pCargo->setType(TYPE_VIP);
		NcargoNUM--;
		VcargoNUM++;
		AddtoQueue(pCargo);
		bool deleted = NormalCargo_L.DeleteNode(TempCargo);

	}
	                  
}
// to move truck from waiting list to moving list
void Company::LoadTruck(CAR_TYPE C_Type,Truck* pT )
{
		if (C_Type == TYPE_VIP)
		{
			if (!Truck_V_Q.isEmpty())
			{
				Truck_V_Q.dequeue(pT);
			}
			else if (!Truck_N_Q.isEmpty())
			{
				Truck_N_Q.dequeue(pT);
			}
			else if (!Truck_S_Q.isEmpty())
			{
				Truck_S_Q.dequeue(pT);
			}
			Truck_count--;
			Tload++;
			pT->setstatus(loading);
			loading_Trucks_B.InsertEnd(pT);

		}


		else if (C_Type == TYPE_NRM)
		{
		 if (!Truck_N_Q.isEmpty())
		{
			Truck_N_Q.dequeue(pT);
		}
		else if (!Truck_V_Q.isEmpty())
			{
				Truck_V_Q.dequeue(pT);
			}
		    Truck_count--;
		    Tload++;
			pT->setstatus(loading);
			loading_Trucks_B.InsertEnd(pT);
		}



		else if (C_Type == TYPE_SPC)
		{
			Truck_S_Q.dequeue(pT);
			Truck_count--;
			Tload++;
			pT->setstatus(loading);
			loading_Trucks_B.InsertEnd(pT);
		}
}

//move truck
//void Company::MovingTruck(Truck* pT)
//{
//	loading_Trucks_B.DeleteNode(pT);
//
//		Moving_Trucks_Q.enqueue(pT);
//}


// to send truck from moving list to checkup list
void Company::TruckMaint(Truck* pTru)
{

	    Moving_Trucks_Q.dequeue(pTru);
	  	pTru->setstatus(CheckUp);
		Truck_count--;
		Tcheckup++;
        Unavailable_Trucks_B.InsertEnd(pTru);
}

// to send a truck back from checkup list to available list
void Company::TruckMaintdone(Truck* pTru)
{
	Unavailable_Trucks_B.DeleteNode(pTru);

	CAR_TYPE type = pTru->getType();
	switch (type)
	{
	case TYPE_NRM:
     pTru->setstatus(waiting);
	 Truck_count++;
     Tcheckup--;
	 Truck_N_Q.enqueue(pTru);

		break;
		
	case TYPE_SPC:

     pTru->setstatus(waiting);
	 Truck_count++;
     Tcheckup--;
	 Truck_S_Q.enqueue(pTru);
	
		break;

	case TYPE_VIP:
     pTru->setstatus(waiting);
	 Truck_count++;
     Tcheckup--;
	 Truck_V_Q.enqueue(pTru);
	
		break;
		
	default:

		return ;

	}
}



///////////////////////////////////Load////////////////////////////////////////////////
	void Company::LoadFile(int& N, int& S, int& V, int& SN, int& SS, int& SV, int& NTC, int& STC, int& VTC, int& J,int& CN,int& CS,int& CV, int& AutoP,int& MaxW, int& E )
	{
	InFile >> N >> S >> V; // number of normal/ special/ VIP trucks
	InFile >> SN >> SS >> SV; // speed of normal/ SPECIAL / VIP trucks
	InFile >> NTC >> STC >> VTC ;  //Capacity of each truck type (N, S, V)
	InFile >> J >> CN >> CS >> CV ; // no. of journeys before checkup and thecheckup durations
    InFile >> AutoP >> MaxW; // limit for autopromotion
	InFile >> E; // number of events

	//////variables//////
    int day;
	int hour;
	int id;            // Cargo id
	int cost;          // cargo cost
	int loadunload;   // Cargo loadtime
	int distance;     // cargo distance
	CAR_TYPE CARTYPE; //cargo type  
    string type_cargo;
	string type_event;


	for (int i = 0; i < E; i++) 
	{
		InFile >> type_event;
		if (type_event == "R")
		{    
		     InFile>>type_cargo>>day>>hour>>id>>distance>>loadunload>>cost;
			 totalcargonumber++;	
			if (type_cargo== "N")
			{
				CARTYPE = TYPE_NRM;
				NcargoNUM++;
				NCFORAUTO++;
			}
			else if (type_cargo== "V")
			{
				CARTYPE = TYPE_VIP;
				VcargoNUM++;
				
			}
			else if (type_cargo== "S")
			{
				CARTYPE = TYPE_SPC;
				ScargoNUM++;
				
			}
			
			 
			Wrapper_Arrival(CARTYPE, day, hour, id, distance, loadunload, cost);

			
		}
		else if (type_event == "P")
		{ 
 
            InFile>> day>>hour>>id>> cost;
 
			 Wrapper_Promote(day,hour, id, cost); 
			 
		}
		else if (type_event == "X")
		{    
 
			InFile>> day>>hour>>id;
			 
		     Wrapper_Cancelation(day,hour, id); 
			 
		}
 
	} 
 
	InFile.close();
}

///////////////////////////////////Save////////////////////////////////////////////////
void Company::SaveFile()
{
    OutFile << "CDT	" << "ID	" << "PT	" << "WT	" << "TID	";
	OutFile << endl;
 // data getter implementaion here 
	OutFile << "\n.......................................................................................................... \n";
	OutFile << "\n.......................................................................................................... \n";
	
	OutFile << "Cargos:" << getTotalCargoNumber() << "  ";
	OutFile << "[N: " << getNcargoNUM() << ", S: " << getScargoNUM() << ", V: " << getVcargoNUM() << "]" << endl;
    OutFile << "Cargo Avg Wait= ";
 // data getter implementaion here 
	OutFile << endl;
    
	
	OutFile << "Auto-promoted: ";
    OutFile << AutoPN/NCFORAUTO;
	OutFile << "%" << endl; 
	OutFile << endl;
	OutFile << "Trucks:" << gettruckc()  << "  ";
	OutFile << "[N: " << getNtruckNUM() << ", S: " << getStruckNUM() << ", V: " << getVtruckNUM() << "]" << endl;
	// data getter implementaion here 
	OutFile.close();

}
/////////////////////////////////////Simulation/////////////////////////////////////
void Company::RunSimulation()
{
	UI* pUI = new UI;
	pUI->outputmenu(); 

}
 
void Company::Simlulation(UI* pUI , PROG_MODE MODE)
{
//////////////////////////////////////////////Variables/////////////////////////////

	/*UI* pUI = new UI;*/
	int nNormal = 0;
	int nSpecial = 0;
	int nVIP = 0; // Number of normal , special , vip Trucks
	int spd_Nrm, spd_Spc, spd_VIP; //Speed of each type of Truck
	int j, nj, sj, vj; //Number of journeys
	int CP_Nrm, CP_Spc, CP_VIP;  // Capacity
	int Autopromo, maxwait; // limit for autopromotion
	int nEvnt;// number of events
	Cargo* VIPCargo_load;
	Cargo* NormalCargo_load;
	Cargo* SpecialCargo_load;
	Truck* pTru;
	Truck* pTruck;
	Cargo* pCar;
	int maxD = 0;
	int LDv = 0;
	int LDs = 0;
	int LDn = 0;
   
	int frontOT=0; //front of truck
	
////////////////////////////////////////////////////////////////////////////////

 
	if (pUI->getINFileName(InFile))
	{
		LoadFile(nNormal, nSpecial, nVIP, spd_Nrm, spd_Spc, spd_VIP, j, nj, sj, vj, CP_Nrm, CP_Spc, CP_VIP, Autopromo, maxwait, nEvnt);
	}
 
		pUI->getOutFileName(OutFile);
 
	 
	Truck_count = nNormal + nSpecial + nVIP; // number of all Trucks in the Company
	settruckc(Truck_count);
	setNTruckNUM(nNormal);
	setSTruckNUM(nSpecial);
	setVTruckNUM(nVIP);
	int cID = 0;

///////////////////////////////////////Waiting Trucks/////////////////////////////////////
	for (int i = 0; i < nVIP; i++)
	{
		cID++;
		pTruck = new Truck(cID, TYPE_VIP, waiting, spd_VIP, CP_VIP,vj,j);
		Truck_V_Q.enqueue(pTruck);
	}

	for (int i = 0; i < nNormal; i++)
	{
		cID++;
		pTruck = new Truck(cID, TYPE_NRM, waiting, spd_Nrm, CP_Nrm,nj,j);
		Truck_N_Q.enqueue(pTruck);

	}
	for (int i = 0; i < nSpecial; i++)
	{
		cID++;
		pTruck = new Truck(cID, TYPE_SPC, waiting, spd_Spc, CP_Spc,sj,j);
		Truck_S_Q.enqueue(pTruck);
	}
///////////////////////////////////////////////////////////////////////////////////////

    if (MODE == MODE_SLNT)
	{
		pUI->outputInterface_silent(this);
	}
	while (!EventsQueue.isEmpty() || !NormalCargo_DELI.IsEmpty() || !VIPCargo_DELI.isEmpty() || !SpecialCargo_DELI.isEmpty())
	{

		if (MODE == MODE_INTR || MODE == MODE_STEP )
		{
            pUI->outputInterface_inte_step(this,MODE);
		}
	        ExecuteEvents(DAY, HOUR);
			HOUR++;
			timestep++;
			if (HOUR == 24)
			{
				DAY++;
				HOUR = 0;
			}
 ////////////////////////////////////////auto promotion handling////////////////////////////////////
			int autocheck=NormalCargo_L.getCount();
			for (int i = 0; i < autocheck; i++)
			{
				NormalCargo_L.GetfirstNode(pCar);
                
	           {
		 
		          if (DAY - pCar->getPreparationTimed() >= Autopromo)
	            	{    
						 AutoPN++;
			             PromoteCargo(pCar->GetID());
		            }
		        else
			        NormalCargo_L.InsertEnd(pCar);
					NormalCargo_L.DeleteFirst();
				 
	          } 
			} 
/////////////////////////////////////////////maxW handling//////////////////////////////////////////////
			int autocheckm=NormalCargo_L.getCount();
			for (int i = 0; i < autocheckm; i++)
			{
				NormalCargo_L.GetfirstNode(pCar);
                
	           {
		 
		          if (HOUR - pCar->getPreparationTimeh() >= maxwait)
	            	{
			            LoadTruck(TYPE_NRM, pTru);
						pCar->assigntruck(pTru);
				        pTru->setLoadingt(pCar->GetLoadUNTime()); 
					    pTru->setMaxD(pCar->getDistance());
                        
		            }
		        else
			        NormalCargo_L.InsertEnd(pCar);
					NormalCargo_L.DeleteFirst();
				 
	          } 
			} 

			 
			int autochecksm=SpecialCargo_Q.getCount();
			for (int i = 0; i < autochecksm; i++)
			{
				SpecialCargo_Q.dequeue(pCar);
                
	           {
		 
		          if (HOUR - pCar->getPreparationTimeh() >= maxwait)
	            	{
			            LoadTruck(TYPE_SPC, pTru);
						pCar->assigntruck(pTru);
				        pTru->setLoadingt(pCar->GetLoadUNTime()); 
					    pTru->setMaxD(pCar->getDistance());
                         
                    }
		        else
			        SpecialCargo_Q.enqueue(pCar);
 		 
	          } 
			} 
 //////////////////////////////////Loading of cargos///////////////////////////////////////////
			
			if (!Truck_V_Q.isEmpty() || !Truck_N_Q.isEmpty() || !Truck_S_Q.isEmpty())
			{     
				if (VIPCargo_Q.getCount() >= CP_VIP)
				{
						LoadTruck(TYPE_VIP, pTru);
					for (int i=0; i < CP_VIP; i++)
					{
 
						VIPCargo_Q.dequeue(VIPCargo_load);
						LDv = LDv + (VIPCargo_load->GetLoadUNTime());
						VIPCargo_load->setStatus(LOADING);
						VIPCargo_load->assigntruck(pTru );
						Loading_Cargo_Q.enqueue(VIPCargo_load,VIPCargo_load->getPriority());
						/*pTru->setLoadingC(VIPCargo_load);*/  
						if (VIPCargo_load->getDistance() > maxD)
						{
							maxD = VIPCargo_load->getDistance();	
						}
						cwait--;
						cload++;
					}
					pTru->setMaxD(maxD);
					pTru->setLoadingt(LDv);
				
					maxD = 0;
				}
				if (NormalCargo_L.getCount() >= CP_Nrm)
				{
					LoadTruck(TYPE_NRM, pTru); 
					for (int i=0; i < CP_Nrm; i++)
					{ 
						NormalCargo_L.GetfirstNode(NormalCargo_load);
						NormalCargo_load->setStatus(LOADING);
						Loading_Cargo_Q.enqueue(NormalCargo_load );
						NormalCargo_load->assigntruck(pTru );
						if (NormalCargo_load->getDistance() > maxD)
						{
							maxD = NormalCargo_load->getDistance();
						}

						LDn = LDn + (NormalCargo_load->GetLoadUNTime());
						NormalCargo_L.DeleteNode(NormalCargo_load);
					 
						cwait--;
						cload++;
					}
					pTru->setMaxD(maxD);
					pTru->setLoadingt(LDn);
					
					maxD = 0;
				}
				if (SpecialCargo_Q.getCount() >= CP_Spc)
				{
					LoadTruck(TYPE_SPC,  pTru); 
					for (int i=0; i < CP_Spc; i++)
					{ 
						SpecialCargo_Q.dequeue(SpecialCargo_load);
						SpecialCargo_load->setStatus(LOADING);
						SpecialCargo_load->assigntruck(pTru );
						if (SpecialCargo_load->getDistance() > maxD)
						{
							maxD = SpecialCargo_load->getDistance();
						}

					    Loading_Cargo_Q.enqueue(SpecialCargo_load );
						LDs = LDs + (SpecialCargo_load->GetLoadUNTime());
 
						cwait--;
						cload++;
					}
					pTru->setMaxD(maxD);
					pTru->setLoadingt(LDs);
					 
					maxD = 0;
				}

			}
//////////////////////////////////moving trucks///////////////////////////////////////////

			//for vip
			if (HOUR == (HOUR+LDv)%24)
			{
				Loading_Cargo_Q.dequeue(pCar);
				pTru=pCar->getassignedTruck();
				pTru->setMovingC(pCar);
				loading_Trucks_B.DeleteNode(pTru);
				frontOT=pTru->getPF();
				pTru->setTDT(frontOT);
				pTru->setstatus(ondelivery);
				Moving_Trucks_Q.enqueue(pTru, pTru->getTDT());
            }
			//for Normal
			if (HOUR == (HOUR + LDn) % 24)
			{
				Loading_Cargo_Q.dequeue(pCar);
				pTru = pCar->getassignedTruck();
				pTru->setMovingC(pCar);
				loading_Trucks_B.DeleteNode(pTru);
				frontOT = pTru->getPF();
				pTru->setTDT(frontOT);
				pTru->setstatus(ondelivery);
				Moving_Trucks_Q.enqueue(pTru, pTru->getTDT());
			}
			//for special
			if (HOUR == (HOUR + LDs) % 24)
			{
				Loading_Cargo_Q.dequeue(pCar);
				pTru = pCar->getassignedTruck();
				pTru->setMovingC(pCar);
				loading_Trucks_B.DeleteNode(pTru);
				frontOT = pTru->getPF();
				pTru->setTDT(frontOT);
				pTru->setstatus(ondelivery);
				Moving_Trucks_Q.enqueue(pTru, pTru->getTDT());
			}
		
//////////////////////////////////delivered trucks///////////////////////////////////////////
			deliveredcheck = Moving_Trucks_Q.getCount();
			for (int i = 0; i < deliveredcheck; i++)
			{
				Moving_Trucks_Q.dequeue(pTru);
				if (HOUR == pTru->getTDT())
				{
					pTru->getDelivC(pCar);
					pCar->setStatus(DELIVERED);
					Cargos_DELI.enqueue(pCar);
					if (pTru->getCarcnt() > 0)
					{
						frontOT = pTru->getPF();
						pTru->setTDT(frontOT);
						Moving_Trucks_Q.enqueue(pTru, pTru->getTDT());
					}
					else
					{
						CAR_TYPE type=pTru->getType();
						if (type == TYPE_VIP)
						{
							Truck_V_Q.enqueue(pTru);
						}
						else if (type == TYPE_NRM)
						{
							Truck_N_Q.enqueue(pTru);
						}
						else if (type == TYPE_SPC)
						{
							Truck_S_Q.enqueue(pTru);
						}
					}
				}
				else { Moving_Trucks_Q.enqueue(pTru); }
			}

//////////////////////////////Timestep//////////////////////////////////////////////////////////	
	
	//if ( gettimestep()%5==0)
	//{	
	//		Cargo* VIPCargo_delieverd;
	//		Cargo* NormalCargo_delieverd;
	//		Cargo* SpecialCargo_delieverd;

	//		bool VIPCargo = VIPCargo_Q.dequeue(VIPCargo_delieverd);
	//		bool NormalCargo = NormalCargo_L.GetfirstNode(NormalCargo_delieverd);
	//		bool SpecialCargo = SpecialCargo_Q.dequeue(SpecialCargo_delieverd);

	//		if (VIPCargo)
	//		{
	//			VIPCargo_delieverd->setStatus(DELIVERED);
	//			VIPCargo_DELI.enqueue(VIPCargo_delieverd); // we added the Cargo to the in delivered list
	//			cdelv++;
	//			cwait--;
	//		}
	//		if (NormalCargo)
	//		{
	//			NormalCargo_delieverd->setStatus(DELIVERED);
	//			NormalCargo_DELI.InsertEnd(NormalCargo_delieverd); // we added the Cargo to the in delivered list
	//			cdelv++;
	//			cwait--; 	
	//		}
	//		if (SpecialCargo)
	//		{
	//			SpecialCargo_delieverd->setStatus(DELIVERED);
	//			SpecialCargo_DELI.enqueue(SpecialCargo_delieverd);   // we added the Cargo to the in delivered list
	//		    cdelv++;
	//			cwait--;
	//		}

	//		timestep=0;
	//}
			SaveFile();
	}
}
/////////////////////////////////////MODES/////////////////////////////////////////////////
   void Company::Interactive_mode(UI* pUI , PROG_MODE MODE)

   {
   Simlulation( pUI,MODE);
   }

   void Company::Step_by_Step_mode(UI* pUI, PROG_MODE MODE)
  {
  Simlulation( pUI,MODE);
  }
  
   void Company::Silent_mode(UI* pUI, PROG_MODE MODE)
   {
   Simlulation( pUI,MODE);
   }

 //////////////////////////SETTER & GETTER & PRINT FUNCTIONS//////////////////////////////
void Company::setdel(int D)
 {
	 cdelv=D;
 }

 void Company::setDay(int day)
 {
	 DAY = day;
 }
 void Company::setHour(int hour)
 {
	 HOUR = hour;
 }
 void Company::setwait(int wait)
 {
	 cwait = wait;
 }
 void Company::settload(int l)
 {
     Tload=l; 
 }
 int Company::gettload()
 {
	return Tload;
 }
 void Company::settcheckup(int c)
 {
     Tcheckup=c; 
 }
 int Company::gettcheckup()
 {
	return Tcheckup;
 }
  void Company::settimestep(int ts)
 {
	 timestep = ts;
 }

    void Company::settruckc(int c)
 {
	 Truck_count = c;
 }

    void Company::setTotalCargoNumber(int tc)
	{
	 totalcargonumber=tc;
	}
	void Company::setNcargoNUM(int C)
	{
		NcargoNUM=C;
	} 
	void Company::setScargoNUM(int C)
	{
		ScargoNUM=C;
	}
	void Company::setVcargoNUM(int C)
	{
		VcargoNUM=C;
	}
    void Company::setNTruckNUM(int C)
	{
	nT=C;
	}
	void Company::setSTruckNUM(int C)
	{
	nS=C;
	}
	void Company::setVTruckNUM(int C)
	{
	nV=C;
	}

 int Company::getDay()
 {
	 return DAY;
 }
 int Company::getHour()
 { 
	 return HOUR; 
 }
 int Company::getwait()
 {
	 return cwait;
 }
 int Company::getAutoPN()
 {
	 return AutoPN; 
 }
 int Company::getdel()
 {
	 return cdelv;
 }

 int Company::gettimestep()
 {
	 return timestep;
 }

  int Company::gettruckc()
 {
	 return Truck_count;
 }
  	int Company::getTotalCargoNumber()
	{
	return totalcargonumber;
	}
    int Company::getNcargoNUM( )
	{
	return NcargoNUM;
	}
	int Company::getScargoNUM( )
	{
	return ScargoNUM;
	}
    int Company::getVcargoNUM( )
	{
	return VcargoNUM;
	}
    int Company::getNtruckNUM( )
	{
	return nT;
	}
	int Company::getStruckNUM( )
	{
	return nS;
	}
	int Company::getVtruckNUM( )
	{
	return nV;
	}

 void Company::PrintWait_N()
 {
   NormalCargo_L.PrintList();
 }
 void Company::PrintWait_S()
 {
	 SpecialCargo_Q.PrintQ();
 }
 void Company::PrintWait_V()
 {
	  /*VIPCargo_Q.PrintQ();*/
 }

 void Company::PrintDeliv_N()
 {
      NormalCargo_DELI.PrintList();
 }
 void Company::PrintDeliv_S()
 {
	 SpecialCargo_DELI.PrintQ();
 }
 void Company::PrintDeliv_V()
 {
	 VIPCargo_DELI.PrintQ();
 }

 
 void Company:: PrintEMPTYT_S()
 {
  Truck_S_Q.PrintQ_T_S();
 }
 void Company::PrintEMPTYT_V()
 {
 Truck_V_Q.PrintQ_T_V();
 }
 void Company::PrintEMPTYT_N()
 {
 Truck_N_Q.PrintQ_T_N();
 }

 LinkedList<Truck*> Company::PrintCheckupTruck()
 {
  return Unavailable_Trucks_B;
 }

 void Company::PrintHour()
 {
	 cout << HOUR;
 }

