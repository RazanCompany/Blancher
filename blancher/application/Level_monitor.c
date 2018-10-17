/*
 * Level_monitor.c
 *
 * Created: 07/10/2018 01:16:51 م
 *  Author: ENG
 */ 

#include "Level_monitor.h"
#include "../RTOS_Includes.h"
#include "../GLOBAL.h"
#include "../CONFIG.h"
#include "../RTE/RTE_levels.h"
#include "../Services/tank_operation.h"
#include "../ECUAL/PowderIF.h"
#include "../MCAL/UART.h"
#define LEVEL_LITERS_STEP	 10



void Level_monitor_task(void* pvParameters)
{
	// First time : fill the tank to level two
	// initialization of the tank with water
	static uint8_t tank_initailized_water_flag = 0;
	uint16_t Tank_level_1_in_letters_measured = 0;
	static uint16_t Tank_out_flow_in_litters = 0 ;
	uint16_t ret_blancher_level ;
	uint16_t ret_tank_level = RTE_get_tank_level();


	if( (ret_tank_level == 0 ) || (ret_tank_level != INVALID_DATA)){

		// first fill tank with water to level one
		while( ret_tank_level == 0 ){
			
			// tank is empty >> feed it step by step
			if(Tank_feed_operation(LEVEL_LITERS_STEP) == E_OK){
				Tank_level_1_in_letters_measured += LEVEL_LITERS_STEP;
			}
			else{
				// ERROR in TANK FEED operation
				// shut down system
				// Set_System_error_main(TANK_FEED_OPERATION_FAIL_PIC);
			}
			
			ret_tank_level = RTE_get_tank_level();
		}
		
		// here >> tank supposed to reach level 1
		// Recheck if tank level s
		if(ret_tank_level == 1){
			
			// fill with salt water => (level 2 filled + level 2)
			if( Powder_drop( TANK_POWDER_DENSITY * (Tank_level_1_in_letters_measured+Tank_level_2_in_letters + (Tank_level_2_in_letters * 0.2)) ) == E_OK){
				
				//  feed tank with water till level 2
				if(Tank_feed_operation(Tank_level_2_in_letters + (Tank_level_2_in_letters * 0.2) ) == E_OK){
					
					// tank supposes to reach level 2
					// check level
					ret_tank_level = RTE_get_tank_level();
					
					if(ret_tank_level != INVALID_DATA){
						
						if(ret_tank_level == 2){
							//every thing ok >> water higher than level 2
							//we can start the while one loop
							//Set flag to start while one loop
							tank_initailized_water_flag = 1;
						}
						else{
							//warning only
							//tank did not reach more than level 2
							//احتمال سيسنور 2 بايظ
							//LCD_main_Report_error_warning(TANK_LEVEL_2_FAIL_PIC);
						}
					}
					else{
						//ERROR INVALID DATA FROM RTE
						//sensor fail
						//Set_System_error_main(LEVEL_SENSORS_FAIL_PIC);
						// 
					}
					
				}
				else{
					//ERROR in TANK FEED TO LEVEL 2
					//Set_System_error_main(TANK_FEED_OPERATION_FAIL_PIC);
				}
			}
			else{
				//ERROR IN Powder_drop
				//Set_System_error_main(POWDER_TANK_FAIL_PIC);
			}
			
		}
		else{
			//ERROR SOMETHING WRONG LEVEL DIDNOT REACH LEVEL 1
			//LCD_main_Report_error_warning(TANK_LEVEL_1_FAIL_PIC);
		}
		
	}
	else{
		// error RTE Should return 0
		if(ret_tank_level == INVALID_DATA){
			//shut down the system and empty the tank
			//Set_System_error_main(LEVEL_SENSORS_FAIL_PIC);
			
		}
		// error RTE Should return 0
		else{
			//Set_System_error_main(TANK_SHOULD_BE_EMPTY);
		}
	
	
	}
	
	
	// Forever loop
	while (tank_initailized_water_flag)
	{
		ret_blancher_level = RTE_get_blancher_level();
		while ( ret_blancher_level == 0 )
		{
			if (Tank_out_operation(LEVEL_LITERS_STEP) == E_OK)
			{
				Tank_out_flow_in_litters += LEVEL_LITERS_STEP ;
			}
			else 
			{
				//error in tank outing.
				//Set_System_error_main(TANK_OUT_FAIL);
				//	
			}
			ret_blancher_level = RTE_get_blancher_level();
			ret_tank_level = RTE_get_tank_level();
			if (ret_tank_level == 0 || ret_tank_level == INVALID_DATA ) break ; 
			
		} /*while ( ret_blancher_level == 0 ) */  
		if (Powder_drop( TANK_POWDER_DENSITY * (Tank_out_flow_in_litters + (Tank_out_flow_in_litters * 0.2)) ) == E_OK)
		{
			
		
			if (Tank_feed_operation(Tank_out_flow_in_litters) == E_OK )
			{
				Tank_out_flow_in_litters = 0 ;
			}
			else 
			{
				//error feeding .
				//LCD_main_Report_error_warning(TANK_FEED_OPERATION_FAIL_PIC); //warning
				tank_initailized_water_flag =0;
				while (ret_blancher_level == 1)
				{
					ret_blancher_level = RTE_get_blancher_level();
					vTaskDelay(2000/portTICK_PERIOD_MS);
				}
				//Set_System_error_main(BLANCHER_EMPTY_AND_TANK_ERROR_WITH_WATER_INLET);//check flow rate
			}
		}
		else
		{
			tank_initailized_water_flag = 0;
			//ERROR IN Powder_drop
			//LCD_main_Report_error_warning(POWDER_TANK_FAIL_PIC); //warning
			ret_blancher_level = RTE_get_blancher_level();
			while (ret_blancher_level == 1)
			{
				ret_blancher_level = RTE_get_blancher_level();
				vTaskDelay(2000/portTICK_PERIOD_MS);
			}
			//Set_System_error_main(BLANCHER_LEVEL_EMPTY_AND_TANK_POWDER_DROP_ERROR);//check powder
		}
	}
	while (1)
	{
		UART0_puts("level monitor task has been stopped .") ;
		vTaskDelay(3000/portTICK_PERIOD_MS) ;
	}
}