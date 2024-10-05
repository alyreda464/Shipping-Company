#pragma once
#include"Company.h"
#include"Defs.h"
#include <fstream>
#include"Event.h"
#include "Queue.h"
 #include "PriQ.h"
#include "Linkedlist.h"
#include"ListBag.h"
#include<string>
#include<iostream>
#include<string>
#include "Defs.h"

using namespace std;
class Company;
class UI
{
private:
	ifstream InFile;
	string fileName;
	ofstream OutFile;
    PROG_MODE MODE; 
public:
	UI();
	void setFileName(string fn);
	bool getINFileName(ifstream& InFile );
	void getOutFileName(ofstream& OutFile );
	void outputmenu();
	void outputInterface_inte_step(Company * pcomp , PROG_MODE MODE);
    void outputInterface_silent(Company* pcomp);

};

