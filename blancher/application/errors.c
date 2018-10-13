/*
 * errors.c
 *
 * Created: 07/10/2018 01:17:42 م
 *  Author: ENG
 */
#include "errors.h"
#include "../GLOBAL.h"
#include "../CONFIG.h"
#include "../ECUAL/LCD.h"
#include "../MCAL/DIO.h"
#include "../RTOS_Includes.h"
#include "../Services/Ignition_operation.h"
#include <util/delay.h>

 uint8_t g_error_number;
 /*
 * Task run for ever stop the scheduler Report Errors To LCD and Close the Systems 
 *parameters@ Void Pointer
 * Return@ Nothing
 */
 
 void Error_monitor_main(void* pvParameters)
 {
	 g_error_number = NO_ERRORS; 
	 
	 while (1)
	 {
		 // check the Error number
		 if (g_error_number != NO_ERRORS)
		 {
			 //close main Valve of the Gas
			 Main_gas_valve_change_state(LOW);
			 // Stop Fruing 
			 Stop_ignition();
			 // Stop scheduler of The RTOS
			  vTaskEndScheduler();
			  // delay to sure the bus is free
			  _delay_ms(200);
			  // jump to error photo
			  lcd_Jump_to(g_error_number);  
		 }
		 else
		 {
		  vTaskDelay(200/portTICK_PERIOD_MS) ;
		 }
	 }
	 
	 
 }
