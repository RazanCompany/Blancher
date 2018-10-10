/*
 * Level_monitor.c
 *
 * Created: 07/10/2018 01:16:51 م
 *  Author: ENG
 */ 

#include "Level_monitor.h"
#include "GLOBAL.h"


#define LEVEL_LITERS_STEP 10



void Level_monitor_task(void* pvParameters)
{
	// First time : fill the tank to level two
	// initialization of the tank with water
	static uint8_t tank_initailized_water_flag = 0;
	uint16_t Tank_level_1_in_letters_measured = 0;
	uint16_t ret_tank_level = RTE_get_tank_level();
	

	if( (ret_tank_level == 0 ) || (ret_tank_level != INVALID_DATA)){

		// first fill tank with water to level one
		while( ret_tank_level == 0 ){
			
			// tank is empty >> feed it step by step
			if(Tank_feed_operation(LEVEL_LITERS_STEP) == E_OK){
				Tank_level_1_in_letters_measured += LEVEL_LITERS_STEP;
			}
			else{
				// ERROR in TANK FEED
			}
			
			ret_tank_level = RTE_get_tank_level();
		}
		
		// here >> tank supposed to reach level 1
		// Recheck if tank level s
		if(ret_tank_level == 1){
			
			// fill with salt water => (level 2 filled + level 2)
			if( Powder_drop(Tank_powder_density * (Tank_level_1_in_letters_measured+Tank_level_2_in_letters + (Tank_level_2_in_letters * 0.2)) ) == E_OK){
				
				//  feed tank with water till level 2
				if(Tank_feed_operation(Tank_level_2_in_letters + (Tank_level_2_in_letters * 0.2) ) == E_OK){
					
					// tank supposes to reach level 2
					// check level
					ret_tank_level = RTE_get_tank_level();
					
					if(ret_tank_level != INVALID_DATA){
						
						if(ret_tank_level == 2){
							// every thing ok >> water higher than level 2
							// we can start the while one loop
							// Set flag to start while one loop
							tank_initailized_water_flag = 1;
						}
						else{
							// tank did not reach more than level 2
							// resume or not
							// احتمال سيسنور 2 بايظ
						}
					}
					else{
						// ERROR INVALID DATA FROM RTE
						// sensor fail
						
					}
					
				}
				else{
					// ERROR in TANK FEED TO LEVEL 2
					
				}
			}
			else{
				// ERROR IN Powder_drop
				
			}
			
		}
		else{
			// ERROR SOMETHING WRONG LEVEL DIDNOT REACH LEVEL 1
			
		}
		
	}
	else{
		// error RTE Should return 0
	
	
	
	}
	
	
	// Forever loop
	while (tank_initailized_water_flag)
	{
		
		
	}
	
}