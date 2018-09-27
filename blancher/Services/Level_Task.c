/*
 * Level_Task.c
 *
 * Created: 26/09/2018 01:00:54 م
 *  Author: Mahmoud Elgendy 
 */ 


#include "Level_Task.h"
#include "../RTOS_Includes.h"
#include "tank_operation.h"
#include "../ECUAL/levels.h"
#include "../RTE/RTE_levels.h"
#include "../RTE/RTE_error_types.h"

static uint8_t g_tank_level = 0;
static uint8_t g_blancher_level = 0;

void Level_task (void* pvParameters )
{
	while (1)
	{
		g_tank_level = Get_tank_level();
		g_blancher_level = Get_blancher_level();
		if (LEVEL_ERROR == Check_for_sensor_error() )
		{
			// sensors error 
			RTE_set_tank_level(INVALID_DATA);
		}
		RTE_set_tank_level(g_tank_level);
		RTE_set_blancher_level(g_blancher_level);
		
		vTaskDelay(200/portTICK_PERIOD_MS) ;
	}
}

static uint8_t Check_for_sensor_error(void)
{
	// check if level sensors are not in the normal ordre .
   if (g_tank_level != 0 || g_tank_level != 1 || g_tank_level != 3 || g_tank_level != 7  )	
   {
	   return LEVEL_ERROR ;
   }
   return LEVEL_OK ;
}




