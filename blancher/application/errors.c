/*
 * errors.c
 *
 * Created: 07/10/2018 01:17:42 م
 *  Author: ENG
 */
#define F_CPU  16000000

#include "errors.h"
#include "../GLOBAL.h"
#include "../CONFIG.h"
#include "../ECUAL/LCD.h"
#include "../MCAL/DIO.h"
#include "../RTOS_Includes.h"
#include "../Services/Ignition_operation.h"
#include "../MCAL/DIO.h"
#include "../ECUAL/Inverter.h"
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
	 uint16_t counter=0;
	 uint8_t watchdog_state =1;
	 while (1)
	 {
		 // check the Error number
		 if (g_error_number != NO_ERRORS)
		 {
			 counter++;
			 watchdog_state^=1;
			 Watch_dog_change_state(watchdog_state);
			 Sareen_change_state(HIGH);
			 //close main Valve of the Gas
			 Main_gas_valve_change_state(LOW);
			 // Stop Frying 
			 Stop_ignition();
			 // Stop scheduler of The RTOS
			 vTaskEndScheduler();
			 if(counter >= 1500 ){
				Inverter_change_state(LOW);
				Conveyor_motor_change_state(LOW);
				 
			 }
			  // delay to sure the bus is free
			 _delay_ms(200);
			 // jump to error photo
			 lcd_Jump_to(g_error_number);  
		 }
		 else
		 {
		  vTaskDelay(50/portTICK_PERIOD_MS) ;
		 }
	 }
	 
	 
 }
