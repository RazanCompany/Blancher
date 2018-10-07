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
#include "error_callbacks.h"
#include "RTOS_sync.h"
#include "ECUAL/Inverter.h"
#include "Services/Drum_speed_Tasks.h"
#include "ECUAL/LCD.h"
#include "Services/tank_operation.h"



gSystemError System_init(void){
	
	gSystemError res = E_OK;
	DIO_init();
	millis_init();	
	Service_error_init();
	RTE_init();
	RTOS_sync_init();
	Inverter_init(UART1,38400,3);
	Lcd_init(UART3,115200,1);
	Drum_speed_Tasks_init();         //fixed here because no main task
	Tank_operation_init();
	return res;

}