
#ifndef DEFSH
#define DEFSH

enum CAR_TYPE    //types of cargos 
{
    TYPE_NRM,    //normal 
    TYPE_SPC,    //special
    TYPE_VIP,    //VIP
    TYPE_CNT    //Number of types

};

enum CAR_STATUS    //cargo status
{
    WAITING,    //waiting to be deliverd
	LOADING,    //loading cargo
    MOVING,    //moving but not delivered (not finished) yet
    DELIVERED,    //Delivered 
    CAR_STATUS_CNT
};

enum TRUCK_Status
{
    waiting,
    loading,
    ondelivery,
    CheckUp,
};

enum PROG_MODE    //mode of the program interface
{
    MODE_INTR,    //interactive mode
    MODE_STEP,    //Step-by-step mode
    MODE_SLNT,    //Silent mode
 
    MODE_CNT    //number of possible modes
};


//#define MaxPossibleCarCnt 999    //max possible cargo count (arbitrary value)
//#define MaxPossibleMtCnt  100    //max possible truck count (arbitrary value)


#endif
