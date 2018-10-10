/*
 *õ  Encoderõ.c
 *
 *  Created: 9/9/2018 2:50:34 PM
 *  Author: Mahmoud elgendy
 *  this sw component is used to return how many liters passes uses timer  
 *
 */

#include "Flow_rate.h"
#include "../MCAL/Timer.h" 
#include "../MCAL/DIO.h"
#include "../CONFIG.h"

//#include "../MCAL/UART.h"



static void flowrate_feeding_callback (uint32_t time );
static void flowrate_outing_callback (uint32_t time );

// pointer to function for the callbacks of the operation layer .
void (*feeding_operation_callback)(void) ; 
void (*out_operation_callback)(void) ;

// struts to hold the timers config .
g_Timer_Config feeding_configeration;
g_Timer_Config outing_configeration;

void Flow_rate_init(void (*callback1)(void) , void (*callback2)(void)) 
{
	
	feeding_configeration.ticks = TICKS_FOR_HALF_LITER ;
	feeding_configeration.timer_number = FLOWRATE_SENSOR_1_TIMER_NUMBER ;//flowrate1_timer_number
	feeding_configeration.isr_call_back = flowrate_feeding_callback ;
	// initialize the needed timer with the previous config .
    timers_init(&feeding_configeration);
	// initialize other timer for the second flow rate .
	outing_configeration.ticks = TICKS_FOR_HALF_LITER ;
	outing_configeration.timer_number = FLOWRATE_SENSOR_2_TIMER_NUMBER ;//flowrate2_timer_number
	outing_configeration.isr_call_back = flowrate_outing_callback ;
	
	// initialize the needed timer with the previous config .
	timers_init(&outing_configeration);
	feeding_operation_callback = callback1;
	out_operation_callback = callback2 ;
}

void flowrate_feeding_callback (uint32_t time )
{
	/*
	*	this function is called back from the ISR to increment the liters counter .
	*/
  // call the feeding operation callback .
    // UART0_puts("FLOW_FEED FFFFFFFFFFFFFFFFFFFFFFFFF\n");
     feeding_operation_callback();
  
 
}

void flowrate_outing_callback (uint32_t time )
{
	/*
	*	this function is called back from the isr to increment the liters counter .
	*/
  // call the feeding operation callback .
  //UART0_puts("FLOW_OUT OOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
     out_operation_callback();
  
}


