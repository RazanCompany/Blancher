﻿/*
 * Temp_monitor.c
 *
 * Created: 07/10/2018 01:16:06 م
 *  Author: ENG
 */ 

#include "Temp_monitor.h"
#include "../GLOBAL.h"
#include "../CONFIG.h"
#include "../MCAL/DIO.h"
#include "../RTOS_Includes.h"
#include "../RTE/RTE_temperature.h"
#include "../RTE/RTE_operations.h"
#include "../Services/Ignition_operation.h"
#include "errors.h"
#include "../MCAL/UART.h"

// hold temp rang state 
uint8_t g_heat_state  = 0 ;
uint8_t g_iginited    = 0 ;
uint16_t  g_negative_offset = 0 , g_Positive_offset = 0 ; 


void Temp_monitor_main(void* pvParameters)
{
	uint16_t sleep_temp  , sleep_Threshold   ;
	uint16_t set_temp , threshold_set_temp  ;  
	uint16_t current_temp;
	gSystemError error ;
	
	while (RTE_get_Start_blancher_Operation() == 0 )
	{
		UART0_puts("start heating to sleep temp ");
		sleep_temp = RTE_get_Sleep_temperature() ;
		sleep_Threshold = RTE_get_Threshold_sleep_temperature() ;
		if ((error = Heat( (sleep_temp+sleep_Threshold) , (sleep_temp - sleep_Threshold ) ) ) != E_OK )
		{
			if (error == E_FLAME_Fail || error == E_IGNITION_Fail)    g_error_number = iGNITION_TYPE ;
		    else if (error == E_OVER_TEMP_Fail)                       g_error_number  = OVER_TEMP_ERROR ;
		}
		vTaskDelay(200/portTICK_PERIOD_MS) ;
	}
	
	
	while (1)
	{
		set_temp = RTE_get_Set_temperature();
		threshold_set_temp = RTE_get_Threshold_set_temperature();
		g_Positive_offset = RTE_get_Positive_offset_temperature();
		g_negative_offset = RTE_get_Negative_offset_temperature();
		current_temp = RTE_get_app_Current_temperature() ;
		current_temp += g_Positive_offset ;
		current_temp -= g_negative_offset ;
		if (current_temp != INVALID_DATA)
		{
			if( (error = Heat((set_temp + threshold_set_temp) , (set_temp - threshold_set_temp) )) != E_OK )
			{
				if (error == E_FLAME_Fail || error == E_IGNITION_Fail)    g_error_number = iGNITION_TYPE ;
				else if (error == E_OVER_TEMP_Fail)                       g_error_number  = OVER_TEMP_ERROR ;
			}
			
		} /* current != INVALID_DATA */ 
		else 
		{
			g_error_number  = OVER_TEMP_ERROR ;
		}
		vTaskDelay(200/portTICK_PERIOD_MS) ;
     }
}



gSystemError Heat ( uint16_t high_temp , uint16_t low_temp )
{   
	uint16_t current_temp = RTE_get_app_Current_temperature() ;
	current_temp += g_Positive_offset ;
	current_temp -= g_negative_offset ;
	
	if (current_temp > low_temp && current_temp < high_temp )            g_heat_state = 1 ;
	else if (current_temp < low_temp )                                   g_heat_state = 2 ;
	else if (current_temp > high_temp )                                  g_heat_state = 3 ;
	
	if (g_heat_state == 2  )    // lower than low_range .    
	{
		while (g_heat_state !=3)
		{   
			current_temp = RTE_get_app_Current_temperature() ;
			current_temp += g_Positive_offset ;
			current_temp -= g_negative_offset ;
			if(current_temp == INVALID_DATA)       return E_OVER_TEMP_Fail ;
			
			if (current_temp > low_temp && current_temp < high_temp )    g_heat_state = 1 ;
			else if (current_temp < low_temp )                           g_heat_state = 2 ;
			else if (current_temp > high_temp )                          g_heat_state = 3 ;
			
			if (  g_iginited )
			{
				if (!Get_light_state())         return E_FLAME_Fail ;
				
			}
			else
			{
				if (Get_light_state())          return E_FLAME_Fail ;
				if(Start_ignition() == E_Fail ) return E_IGNITION_Fail ;
				g_iginited = 1 ;
			}  /* iginited */
		}  /*heat_state !=3*/
		
	    // stop the flame .	    
		Stop_ignition();
		g_iginited = 0;
					
	}/* heat_state = 2 */ 
	return E_OK;
}
	



