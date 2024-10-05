
#include "UI.h"
#include"Company.h"
#include <Windows.h>



UI::UI()
{

}


void UI::setFileName(string fn)
{
	fileName = fn;
}

bool UI::getINFileName(ifstream& InFile )
{
	cout<< "Please enter File name you want to open = " ;
	string fn ;
	cin >> fn;
 
	fileName =fn+".txt";
    InFile.open(fileName, ios::in);
	if (InFile.is_open())
	{
		cout<<"File Load Succesfully"<<endl;
		return true;
	}
	cout<<  "Cannot open the file.."<<endl ;
	return false;
 
}

void UI::getOutFileName(ofstream& OutFile ) 
{
	cout<< "Please enter File name you want to save data = " ;
	string fn ;
	cin >> fn;
 
	fileName =fn+".txt";
    OutFile.open(fileName, ios::out);
	 
}

void UI::outputmenu()
{
	cout<<"      Welcome Back      "<<endl; 
	cout<<"Please Select Simulation Mode"<<endl; 
	cout<<"1)interaction mode  "<<endl;
	cout<<"2)Step by Step mode  "<<endl;
	cout<<"3)Silent mode  "<<endl;
		int x;
		cin>>x;
		Company* pcomp = new Company;  
	switch (x)	 
	{
	case 1:
		 cout<< "Welcome to the Interactive Mode !!..." <<endl;;
         MODE=MODE_INTR;
		 pcomp->Interactive_mode(this,MODE);
	
		break;
	case 2:
		cout<< "Welcome to the Step by Step Mode !!..."<<endl;;
		MODE=MODE_STEP;
		pcomp->Step_by_Step_mode(this,MODE);
		break;
	case 3:
        MODE=MODE_SLNT;
		pcomp->Silent_mode(this,MODE);

        break;
	}
}

void UI::outputInterface_inte_step(Company * pcomp , PROG_MODE MODE)
{  
	  string x;
	if (MODE==MODE_INTR)
{
	     
	    cout << "press z to continue OR any key to END program ... "<<endl;
	   cin >> x;
}
	if (MODE==MODE_STEP)
	{
		Sleep(1000);
	}

 if (x == "z"|| MODE==MODE_STEP)
{      
	cout << "Current Time (Day:Hour):" << pcomp->getDay() << ":" << pcomp->getHour()<<endl;
	cout << pcomp->getwait() << " Waiting Cargos:";
	cout << "[ ";
	pcomp->PrintWait_N();
	cout << " ]";
	cout << "( ";
	pcomp->PrintWait_S();
	cout << " )";
	cout << "{ ";
	pcomp->PrintWait_V();
	cout << " }"<< endl;
	cout<<"-------------------------------------------------------"<<endl;
	cout << pcomp->gettload() << " Loading Trucks:" ;
	
	cout<<endl;






	cout<<"-------------------------------------------------------"<<endl;
	cout << pcomp->gettruckc() << " Empty Trucks:";
	/*cout << "[ ";*/
	pcomp->PrintEMPTYT_N();
	cout << " ,";
	/*cout << "( ";*/
	pcomp->PrintEMPTYT_S();
	cout << " ,";
	/*cout << "{";*/
	pcomp->PrintEMPTYT_V();
	cout<< endl;
    cout<<"-------------------------------------------------------"<<endl;
	cout << "0" << " Moving Cargos:"  << endl;
	cout<<"-------------------------------------------------------"<<endl;
	cout << pcomp->gettcheckup() << " In-Checkup Trucks:";
	
	pcomp->PrintCheckupTruck();
	LinkedList<Truck*> chup = pcomp->PrintCheckupTruck();
	Truck* pT;
	while (!chup.IsEmpty())
	{
      chup.GetfirstNode(pT);	
      CAR_TYPE type = pT->getType();
      switch (type)
	{
	case TYPE_NRM:

		 cout<<"["<<pT->getID() <<"] ";
	     chup.DeleteNode(pT);
		
		break;
		
	case TYPE_SPC:

		cout<<"("<<pT->getID() <<") ";
	    chup.DeleteNode(pT);
	
		break;

	case TYPE_VIP:
		     
		cout<<"{"<<pT->getID() <<"} ";
	    chup.DeleteNode(pT);
	
		break;
		
	default:

		break ;

	}
 	}
	cout<<endl;
    cout<<"-------------------------------------------------------"<<endl;
	cout << pcomp->getdel() << " Delivered Cargos:";
	cout << "[ ";
	pcomp->PrintDeliv_N();
	cout << " ]";
	cout << "( ";
	pcomp->PrintDeliv_S();
	cout << " )";
	cout << "{ ";
	pcomp->PrintDeliv_V();
	cout << " }"<< endl;
	cout<<"-------------------------------------------------------"<<endl;
	
	/*cout << "press z to continue OR any key to END program ..."<<endl;
    cin >> x;*/
 }
 else
 {
	 cout<<"SIMULATION STOPPED"<<endl;
 }

}
 void UI::outputInterface_silent(Company * pcomp)
 {
        cout<<"Silent Mode"<<endl;
		cout<<"Simulation Starts..."<<endl;
		cout<<"Simulation ends, Output file created"<<endl;
 }