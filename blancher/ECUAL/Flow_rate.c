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





#define TICKS_FOR_LITER   480
#define TICKS_FOR_HALF_LITER   240

static void flowrate_feeding_callback (uint32_t time );
static void flowrate_outing_callback (uint32_t time );

// pointer to function for the callbacks of the operation layer .
void (*feeding_operation_callback)(void) ; 
void (*out_operation_callback)(void) ;

// struts to hold the timers config .
g_Timer_Config feeding_configeration;
g_Timer_Config outing_configeration;

void Flow_rate_init(uint8_t flowrate1_timer_number,uint8_t flowrate2_timer_number,void (*callback1)(void) , void (*callback2)(void)) 
{
	
	feeding_configeration.ticks = TICKS_FOR_HALF_LITER ;
	feeding_configeration.timer_number = 1 ;//flowrate1_timer_number
	feeding_configeration.isr_call_back = flowrate_feeding_callback ;
	
	// initialize the needed timer with the previous config .
    timers_init(&feeding_configeration);
	
	// initialize other timer for the second flow rate .
	feeding_configeration.ticks = TICKS_FOR_HALF_LITER ;
	feeding_configeration.timer_number = 3 ;//flowrate2_timer_number
	feeding_configeration.isr_call_back = flowrate_outing_callback ;
	
	// initialize the needed timer with the previous config .
	timers_init(&outing_configeration);
	feeding_operation_callback = callback1;
	out_operation_callback = callback2 ;
	DIO_init();
}

void flowrate_feeding_callback (uint32_t time )
{
	/*
	*	this function is called back from the isr to increment the liters counter .
	*/
  // call the feeding operation callback .
     feeding_operation_callback();
  
 
}

void flowrate_outing_callback (uint32_t time )
{
	/*
	*	this function is called back from the isr to increment the liters counter .
	*/
  // call the feeding operation callback .
     out_operation_callback();
  
}


