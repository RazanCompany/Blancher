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

#include "../MCAL/UART.h"
 

void Level_task (void* pvParameters )
{
	uint8_t Tank_level = 0;
	uint8_t Blancher_level = 0;
	while (1)
	{
		Tank_level = Get_tank_level();
		Blancher_level = Get_blancher_level();
		if (LEVEL_ERROR == Tank_level)
		{
			// sensors error 
			RTE_set_tank_level(INVALID_DATA);
			// callback error function .
			UART0_puts("level error !!!");
		}
		else 
		{
			RTE_set_tank_level(Tank_level);
			RTE_set_blancher_level(Blancher_level);
		}
		vTaskDelay(200/portTICK_PERIOD_MS) ;
	}
}





