/*
 *õ  Encoderõ.c
 *
 *  Created: 9/9/2018 2:50:34 PM
 *  Author: Mahmoud elgendy
 *  this sw component is used to return how many liters passes uses timer  
 *
 */

#include "flow_rate.h"
#include "Encoder/Encoder.h" 
#include "../MCAL/DIO.h"
#define FLOW_DEBBUGE 0

#ifdef FLOW_DEBBUGE
#include <stdio.h>
#include  "../MCAL/UART.h"
#endif 

#define TICKS_FOR_LITER   480
#define TICKS_FOR_HALF_LITER   240

 volatile float g_liters_counter = 0 ;
g_Timer_Config configeration;


void Flow_rate_init(uint8_t timer_num) 
{
	
	configeration.ticks = TICKS_FOR_HALF_LITER ;
	configeration.timer_number = timer_num ;
	configeration.isr_call_back = Liters_count ;
	
	// initialize the needed timer with the previous config .
    timers_init(&configeration);
}


uint8_t Tank_feed(float liters) 
{
	
	if(liters > 0.0)
	{
		// in case of debugging 
		#if FLOW_DEBBUGE
			UART0_puts("start feeding");
		#endif 
		// reset the global counter.
		g_liters_counter = 0;
		// start the feeding valve to fill the tank.
		Tank_valve_1_change_state(HIGH);
		// keep monitoring the amount of water .
		while(g_liters_counter < liters );
		// turn the feeding valve when the proper amount pass.
		Tank_valve_1_change_state(LOW);
		// in case of debugging .
		#if FLOW_DEBBUGE
			UART0_puts("done feeding");
		#endif
		return 1 ;
	} //liters > 0 
	
	// something went wrong .
	return -1 ;
}



void Liters_count (uint32_t time )
{
  // increment the global counter.
  g_liters_counter +=0.5 ;
  
  // in case of debugging 
  #if FLOW_DEBBUGE
     UART0_puts("counting : \n");
     UART0_OutUDec(g_liters_counter);
  #endif
}


