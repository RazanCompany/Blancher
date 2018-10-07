
#define F_CPU 16000000
#include "util/delay.h"
#include "Tasks.h"
#include "MCAL/DIO.h"
#include "ECUAL/levels.h"
#include "ECUAL/Flow_rate.h"
#include "GLOBAL.h" //tank global letters defined here



static uint8_t g_calibration_done_feeding ;
static uint8_t g_calibration_done_outing  ;

static volatile uint16_t g_calibration_feeding_liters_counter ;
static volatile uint16_t g_calibration_out_liters_counter ;

static volatile uint16_t g_calibration_feed_liters ;
static volatile uint16_t g_calibration_out_liters ;

static void Tank_calibration_feed_operation(uint16_t liters);
static void Tank_calibration_out_operation(uint16_t liters);
static void Tank_calibration_feed_callback (void);
static void Tank_calibration_out_callback(void);



//this function checks the flow rate of input tank water
//return 1 for normal operation
static uint8_t check_water_inlet(void){
	return 1;
}

//this function checks the flow rate of output tank water
//return 1 for normal operation
static uint8_t check_water_outlet(void){
	return 1;
}

static void Fail(void){
	Tank_valve_1_change_state(LOW);
	Tank_valve_2_change_state(LOW);
	Blancher_valve_change_state(LOW);
	Pump_change_state(LOW);
}
gSystemError Wash(uint8_t CycleNumber){

	while (CycleNumber > 0)
	{
			while(Get_tank_level() < 3){
				Tank_valve_1_change_state(HIGH);
				Tank_valve_2_change_state(LOW);
				Pump_change_state(LOW);
				Blancher_valve_change_state(LOW);
				if( check_water_inlet() != 1) {
					Fail();
					return E_Fail;
				}
				
			}
			Tank_valve_1_change_state(LOW);
			Tank_valve_2_change_state(HIGH);
			Blancher_valve_change_state(LOW);
			_delay_ms(5000); //wait the water to reach the pump //mechanical issue //not vTaskdelay scheduler stopping here
			Pump_change_state(HIGH);
			while ( Get_blancher_level() || (Get_tank_level()==0) )
			{
				if(check_water_outlet() != 1){
					Fail();
					return E_Fail;
				}
			}
			Tank_valve_2_change_state(LOW);
			Tank_valve_1_change_state(LOW);
			Pump_change_state(LOW);
			Blancher_valve_change_state(HIGH);
			CycleNumber --;
			
	}
	return E_OK;
}




//the tank in real must be empty

gSystemError Tank_Calibrate(void){
	// initialize flow rate sensors before RTOS start .
	Tank_operation_calibrate_wash_init();
	// make sure all valves are off .
	Tank_valve_2_change_state(LOW);
	Pump_change_state(LOW);
	Blancher_valve_change_state(LOW);
	Tank_valve_1_change_state(LOW);
	//empty the tank first
	uint32_t Tank_capacity_temp = 0;
    
	// calculate the first capacity .
	while (Get_tank_level() < 1)
	{
		Tank_calibration_feed_operation(5);
		Tank_capacity_temp +=5;
		if(check_water_inlet() != 1){
			Fail();
			return E_Fail;
		}
	}
	Tank_level_1_in_letters = Tank_capacity_temp;
	
	// calculate the second capacity .
	Tank_capacity_temp =0;
	while (Get_tank_level() < 2)
	{
		Tank_calibration_feed_operation(5);
		Tank_capacity_temp +=5;
		if(check_water_inlet() != 1){
			Fail();
			return E_Fail;
		}
	}
	Tank_level_2_in_letters = Tank_capacity_temp;
	
	// calculate the third capacity .
	Tank_capacity_temp =0;
	while (Get_tank_level() < 3)
	{
		Tank_calibration_feed_operation(5);
		Tank_capacity_temp +=5;
		if(check_water_inlet() != 1){
			Fail();
			return E_Fail;
		}
	}
	Tank_level_3_in_letters = Tank_capacity_temp;	
	return E_OK;	
	
}










void Tank_operation_calibrate_wash_init(void)
{
	Flow_rate_init(FLOWRATE_SENSOR_1_TIMER_NUMBER ,FLOWRATE_SENSOR_2_TIMER_NUMBER, Tank_calibration_feed_callback , Tank_calibration_out_callback);
	g_calibration_done_feeding = 0;
	g_calibration_done_outing  = 0 ;
	g_calibration_feeding_liters_counter = 0 ;
	g_calibration_out_liters_counter = 0 ;
}

static void Tank_calibration_feed_operation(uint16_t liters)
{
	g_calibration_feeding_liters_counter = 0;
	g_calibration_feed_liters = liters * 2 ;
	
	// start the feeding valve to fill the tank.
	Tank_valve_1_change_state(HIGH);
	// wait until the tank feed operation ends
	while (!g_calibration_done_feeding) ;
	// turn the feeding valve when the proper amount pass.
	Tank_valve_1_change_state(LOW);
	g_calibration_done_feeding = 0 ;
	
}


static void Tank_calibration_out_operation(uint16_t liters)
{
	g_calibration_out_liters_counter = 0;
	g_calibration_out_liters = liters * 2 ;
	// opening the out valve and pump
	Tank_valve_2_change_state(HIGH);
	Pump_change_state(HIGH);
	// block until the amount of water pass
	while (!g_calibration_done_feeding) ;
	// turn the pump and valve off .
	Pump_change_state(LOW);
	Tank_valve_2_change_state(LOW);
	g_calibration_done_outing = 0 ;
	
}


static void Tank_calibration_feed_callback (void)
{
	
	g_calibration_feeding_liters_counter ++ ;
	// keep monitoring the amount of water .
	if (g_calibration_feeding_liters_counter >= g_calibration_feed_liters )
	{
		g_calibration_done_feeding = 1;
	}
	
}

static void Tank_calibration_out_callback(void)
{
	
	g_calibration_out_liters_counter ++ ;
	if (g_calibration_out_liters_counter >= g_calibration_out_liters )
	{
		g_calibration_done_outing = 1 ;
	}
	
}

