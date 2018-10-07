/*
 * Service_main.c
 *
 * Created: 9/29/2018 4:24:50 AM
 *  Author: Mohab Adel
 */ 

#include "Service_main.h"

#include "LCD_Tasks.h"
#include "TEMP_Task.h"
#include "Level_Task.h"
#include "tank_operation.h"
#include "Drum_speed_Tasks.h"

void Service_init(void){
	
	Drum_speed_Tasks_init(); //fixed here because no main task
	Tank_operation_init();
	
}
