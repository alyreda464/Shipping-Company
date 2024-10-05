#include <iostream>
#include "Company.h"
 using namespace std;
 
int main()
{	
 Company* pComp= new Company;
 pComp->RunSimulation();
  
 delete pComp;
 
 return 0;
}
