/*
 * Temp_monitor.c
 *
 * Created: 07/10/2018 01:16:06 م
 *  Author: ENG
 */ 

#include "Temp_monitor.h"
#include "../GLOBAL.h"
#include "../CONFIG.h"
#include "../MCAL/DIO.h"
#include "../RTE/RTE_temperature.h"
#include "../Services/Ignition_operation.h"

// hold temp rang state 
uint8_t heat_state = 0 ;
uint8_t iginited = 0 ;


void Temp_monitor_main(void* pvParameters)
{
	uint16_t sleep_temp  , sleep_Threshold   ;
	uint16_t set_temp , threshold_set_temp ,  negative_offset , Positive_offset ;  
	uint16_t current_temp;
	
	sleep_temp = RTE_get_Sleep_temperature() ; 
	sleep_Threshold = RTE_get_Threshold_sleep_temperature() ; 
	if (Heat( (sleep_temp+sleep_Threshold) , (sleep_temp - sleep_Threshold ) ) != E_OK ) 
	{
		// handle errors to be done !!!!!!!!!
	}
	
	while (1)
	{
		set_temp = RTE_get_Set_temperature();
		threshold_set_temp = RTE_get_Threshold_set_temperature();
		current_temp = RTE_get_app_Current_temperature() ;
		if (current_temp != INVALID_DATA)
		{
			if(Heat((set_temp + threshold_set_temp) , (set_temp - threshold_set_temp)) != E_OK )
			{
				// handle errors to be done .
			}
			
		} /* current != INVALID_TEMP */ 
		else 
		{
			// over temp error .
		}
     }
}



gSystemError Heat ( uint16_t high_temp , uint16_t low_temp )
{   
	uint16_t current_temp = RTE_get_app_Current_temperature() ;
	
	if (current_temp > low_temp && current_temp < high_temp )    heat_state = 1 ;
	else if (current_temp < low_temp )                           heat_state = 2 ;
	else if (current_temp > high_temp )                          heat_state = 3 ;
	
	if (heat_state == 2  )      
	{
		while (heat_state !=3)
		{
			current_temp = RTE_get_app_Current_temperature() ;
			if (current_temp > low_temp && current_temp < high_temp )    heat_state = 1 ;
			else if (current_temp < low_temp )                           heat_state = 2 ;
			else if (current_temp > high_temp )                          heat_state = 3 ;
			
			if (  iginited )
			{
				if (!Get_light_state()) return E_FLAME_Fail ;
				
			}
			else
			{
				if (Get_light_state()) return E_FLAME_Fail ;
				if(Start_ignition() == E_Fail ) return E_IGNITION_Fail ;
				iginited = 1 ;
			}  /* iginited */
		}  /*heat_state !=3*/
		
	    // stop the flame .	    
		Stop_ignition();
		iginited = 0;
					
	}/* heat_state = 2 */ 
	return E_OK;
}
	



