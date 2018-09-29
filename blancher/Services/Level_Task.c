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
 
void (*g_callback_level_sensor_fail) (void) = NULL;
void Level_main_err_init( void (*callback_level_sensor_fail) (void) ){
	 g_callback_level_sensor_fail = callback_level_sensor_fail;
 }
 
//must sure that DIO_init() called
void Level_main (void* pvParameters )
{
	uint8_t Tank_level = 0;
	uint8_t Blancher_level = 0;
	
	while (1)
	{
		Tank_level = Get_tank_level();
		Blancher_level = Get_blancher_level();
		if (LEVEL_ERROR == Tank_level)
		{
		
			if(g_callback_level_sensor_fail == NULL){
				
			}
			else{
				// callback error function .
				g_callback_level_sensor_fail();
			}
			RTE_set_tank_level(INVALID_DATA);
			
			//UART0_puts("level error !!!");
		}
		else 
		{
			RTE_set_tank_level(Tank_level);
			RTE_set_blancher_level(Blancher_level);
		}
		vTaskDelay(500/portTICK_PERIOD_MS) ;
	}
}





