
#define F_CPU 16000000
#include "util/delay.h"
#include "Tasks.h"
#include "MCAL/DIO.h"
#include "ECUAL/levels.h"
#include "GLOBAL.h" //tank global letters defiend here
#include "Services/tank_operation.h"
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
	Tank_valve_2_change_state(LOW);
	Pump_change_state(LOW);
	Blancher_valve_change_state(LOW);
	Tank_valve_1_change_state(LOW);
	//empty the tank first
	uint32_t Tank_capacity_temp = 0;

	while (Get_tank_level() < 1)
	{
		Tank_feed_operation(5);
		Tank_capacity_temp +=5;
		if(check_water_inlet() != 1){
			Fail();
			return E_Fail;
		}
	}
	Tank_level_1_in_letters = Tank_capacity_temp;
	
	Tank_capacity_temp =0;
	while (Get_tank_level() < 2)
	{
		Tank_feed_operation(5);
		Tank_capacity_temp +=5;
		if(check_water_inlet() != 1){
			Fail();
			return E_Fail;
		}
	}
	Tank_level_2_in_letters = Tank_capacity_temp;
	
	Tank_capacity_temp =0;
	while (Get_tank_level() < 3)
	{
		Tank_feed_operation(5);
		Tank_capacity_temp +=5;
		if(check_water_inlet() != 1){
			Fail();
			return E_Fail;
		}
	}
	Tank_level_3_in_letters = Tank_capacity_temp;	
	return E_OK;	
	
}