﻿/*
 * tank_operation.c
 *
 * Created: 20/09/2018 02:45:23 م
 *  Author: ENG
 */
#include "tank_operation.h" 
#include "../MCAL/DIO.h"
#include "../ECUAL/Flow_rate.h"
#include "../RTOS_Includes.h"
#include "../CONFIG.h"


#include "../MCAL/UART.h"

static void Tank_feed_callback (void);
static void Tank_out_callback (void);

static volatile uint16_t g_feeding_liters_counter = 0; 
static volatile uint16_t g_out_liters_counter = 0;


static volatile uint16_t g_feed_liters ;
static volatile uint16_t g_out_liters ;
SemaphoreHandle_t  Feeding_Semaphore , outing_Semaphore ;
StaticSemaphore_t feeding_SemaphoreBuffer , outing_SemaphoreBuffer ;




void Tank_operation_init(void)
{
	Flow_rate_init(Tank_feed_callback , Tank_out_callback);	
	Feeding_Semaphore = xSemaphoreCreateBinaryStatic( &feeding_SemaphoreBuffer );
	outing_Semaphore = xSemaphoreCreateBinaryStatic( &outing_SemaphoreBuffer );
}

gSystemError Tank_feed_operation(uint16_t liters)
{   
	g_feeding_liters_counter = 0;
	g_feed_liters = liters * 2 ;

	// start the feeding valve to fill the tank.
	Tank_valve_1_change_state(HIGH);
	// wait until the tank feed operation ends 
// 	if(xSemaphoreTake(Feeding_Semaphore , ( TickType_t ) (liters * 2000)) == pdFALSE  )
// 	{
// 		Tank_valve_1_change_state(LOW);
// 		return E_Fail ;
// 	}
	xSemaphoreTake(Feeding_Semaphore , portMAX_DELAY); //debug
	// turn the feeding valve when the proper amount pass.
	UART0_puts("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
	Tank_valve_1_change_state(LOW);
	return E_OK ;
}


gSystemError Tank_out_operation(uint16_t liters)
{
  
	g_out_liters_counter = 0;
	g_out_liters = liters * 2 ;
	// opening the out valve and pump 
	Tank_valve_2_change_state(HIGH);
	Pump_change_state(HIGH);
	// block until the amount of water pass
// 	if(xSemaphoreTake(outing_Semaphore , ( TickType_t )(liters * 2000)) == pdFALSE  )
// 	{
// 		Pump_change_state(LOW);
// 		Tank_valve_2_change_state(LOW);
// 		return E_Fail ;
// 	}
	xSemaphoreTake(outing_Semaphore , portMAX_DELAY);
	// turn the pump and valve off .
	UART0_puts("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
	Pump_change_state(LOW);
	Tank_valve_2_change_state(LOW);
	return E_OK ;
}


static void Tank_feed_callback (void)
{
	//UART0_puts("")

	g_feeding_liters_counter ++ ;
	// keep monitoring the amount of water .
	if (g_feeding_liters_counter >= g_feed_liters )
	{
		// release the semaphore
		UART0_puts("BEFORRRRRE FWFWFWFWFWFWFWFWFWFWFWFWFWFWF");
		xSemaphoreGive(Feeding_Semaphore);
		UART0_puts("g_feeding_liters_counter FWFWFWFWFWFWFWFWFWFWFWFWFWFWF");
		UART0_OutUDec(g_feeding_liters_counter);
		UART0_putc('\n');
	}

	
}

static void Tank_out_callback(void)
{
	
	g_out_liters_counter ++ ;
	if (g_out_liters_counter >= g_out_liters )
	{
		// release the semaphore
		UART0_puts("beforrrreeeeee OWOWOWOWOOWOWOWOWOWOOWOWOWOWOOWOW");
		xSemaphoreGive(outing_Semaphore );
		UART0_puts("g_out_liters_counter OWOWOWOWOOWOWOWOWOWOOWOWOWOWOOWOW");
		UART0_OutUDec(g_out_liters_counter);
		UART0_putc('\n');
	}
	

}


