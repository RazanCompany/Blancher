/*
 * sequance.c
 *
 * Created: 07/10/2018 01:18:24 م
 *  Author: ENG
 */ 
#define  F_CPU 16000000
#include "../System.h"
#include "../GLOBAL.h"
#include "../MCAL/DIO.h"
#include "sequance.h"
#include "../Services/tank_operation.h"
#include "../ECUAL/Inverter.h"
#include "../ECUAL/Drum.h"
#include "../ECUAL/PowderIF.h"
#include "util/delay.h"


g_Inveter_Config Inverter_check_config ;
gSystemError errors ;

void Sequance_task (void* pvParameters)
{
	errors = System_check();
	
	if (errors.E_CONVOYER_ENCODER_fail)
	{
		xSemaphoreTake(LCD_mutex_handle , portMAX_DELAY ) ;
		lcd_Jump_to(CONVEYOR_MOTOR_ERROR_PIC);
		Lcd_Read()
		xSemaphoreGive(LCD_mutex_handle);
	}
	
	while (1) 
	{
		
	}
}


gSystemError System_check (void)
{
	// check salt existence .
	if( !Salt_exist() )
	   return E_SALT_fail ;
	   
	// check  input flow rate 
	if (Tank_feed_operation(2) == E_Fail)
	{
		return E_INLET_FLOW_fail ; 
	}
	
	// check output flow rate
	if (Tank_out_operation(2) == E_Fail)
	{
		return E_OUTLET_FLOW_fail ;
	}
	
	if (Powder_drop(2) == E_Fail)
	{
		return E_SALT_MOTER_ENCODER_fail ;
	}
	
	Inverter_check_config.distance = distance ;
	Inverter_check_config.gear_ratio=gear_ratio;
	Inverter_check_config.gear_diameter = gear_diameter;
	Inverter_check_config.motor_rpm_max = motor_rpm_max;
	Inverter_check_config.time_user_M = 0;
	Inverter_check_config.time_user_S = 5 ;
	
	// check inverter & conveyor 
	Inverter_set_Freq(&Inverter_check_config);
	Conveyor_motor_change_state(HIGH);
	_delay_ms(10000);
	if (Drum_speed() == 0 )  return E_DRUM_ENCODER_fail ;
	
	if (!Get_conveyor_state()) return E_CONVOYER_ENCODER_fail ;
	 
	return E_OK;
}

