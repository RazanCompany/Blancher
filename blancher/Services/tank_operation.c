/*
 * tank_operation.c
 *
 * Created: 20/09/2018 02:45:23 م
 *  Author: ENG
 */
#include "tank_operation.h" 
#include "../MCAL/DIO.h"
#include "../ECUAL/Flow_rate.h"
#include "../RTOS_Includes.h"


static void Tank_feed_callback ();
static void Tank_out_callback ();

static volatile uint16_t g_feeding_liters_counter = 0; 
static volatile uint16_t g_out_liters_counter = 0;
static uint8_t g_tank_out_off = 0;

static volatile uint16_t g_feed_liters ;
SemaphoreHandle_t  Feeding_Semaphore , outing_Semaphore ;
StaticSemaphore_t feeding_SemaphoreBuffer , outing_SemaphoreBuffer ;




void Tank_operation_init()
{
	Flow_rate_init( Tank_feed_callback , Tank_out_callback);	
	Feeding_Semaphore = xSemaphoreCreateBinaryStatic( &feeding_SemaphoreBuffer );
	outing_Semaphore = xSemaphoreCreateBinaryStatic( &outing_SemaphoreBuffer );
}

void Tank_feed_operation(uint8_t liters)
{   
	xSemaphoreTake(Feeding_Semaphore , 0);
	g_feeding_liters_counter = 0;
	g_feed_liters = liters * 2 ;
	
	// start the feeding valve to fill the tank.
	Tank_valve_1_change_state(HIGH);
	// wait until the tank feed operation ends 
	xSemaphoreTake(Feeding_Semaphore ,  portMAX_DELAY );
	// turn the feeding valve when the proper amount pass.
	Tank_valve_1_change_state(LOW);
	xSemaphoreGive( Feeding_Semaphore) ;
	
}


void Tank_out_operation_on(void)
{
   	xSemaphoreTake(outing_Semaphore , 0);
	g_out_liters_counter = 0;
	// openning the out valvev and punp 
	Tank_valve_2_change_state(HIGH);
	Pump_change_state(HIGH);
	// block until the amount of water pass
	xSemaphoreTake(outing_Semaphore , portMAX_DELAY);
	// turn the pump and valve off .
	Pump_change_state(LOW);
	Tank_valve_2_change_state(LOW);
	// release the semaphore 
	xSemaphoreGive(outing_Semaphore);
	
}


void Tank_out_operation_off(void)
{
	g_tank_out_off = 1; 
}

static void Tank_feed_callback ()
{
	
	g_feeding_liters_counter ++ ;
	// keep monitoring the amount of water .
	if (g_feeding_liters_counter < g_feed_liters )
	{
		// release the semaphore
		xSemaphoreGive(Feeding_Semaphore );
	}
	
}

static void Tank_out_callback ()
{
	
	g_out_liters_counter ++ ;
	if (g_tank_out_off )
	{
		// release the semaphore
		xSemaphoreGive(outing_Semaphore );
		g_tank_out_off = 0;
	}
	
}


