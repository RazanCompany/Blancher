/*
 * System.c
 *
 * Created: 9/26/2018 7:00:03 AM
 *  Author: Mohab Adel
 */ 

#include "System.h"
#include "RTE/RTE_main.h"
#include "utils/Millis.h"
#include "MCAL/DIO.h"
#include "Services/Service_main.h"
#include "error_callbacks.h"



gSystemError System_init(void){
	
	gSystemError res = E_OK;
	DIO_init();
	millis_init();	
	Service_error_init();
	Service_init();
	RTE_init();
	//App_init();
	return res;

}