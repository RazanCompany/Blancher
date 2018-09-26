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
#include "Services/LCD_Tasks.h"


gSystemError System_init(void){
	
	gSystemError res=E_OK;
	DIO_init();
	millis_init();	
	Lcd_init(UART3,115200,1);
	RTE_init();
	return res;

}