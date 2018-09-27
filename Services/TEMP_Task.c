/*
 * TEMP_Task.c
 *
 * Created: 9/22/2018 4:24:23 PM
 *  Author: M.nagah
 */ 

#include "TEMP_Task.h"
#include "../ECUAL/Temperature.h"
#include "../ECUAL/LCD.h"
#include "../RTOS_Includes.h"
#include "../RTE/RTE_temperature.h"
static uint16_t s_current_temp;
/*
*Set the Temperatur on RTE
*Parameters @ Nothing
*return Nothing 
*/
void Temp_main(void* pvParameters){
	temp_init(0);
	while (1)
	{
		s_current_temp = temp_read();
		// set temp for LCD 
		RTE_set_Current_temperature(s_current_temp);
		// set the temp for the application .
		RTE_set_app_Current_temperature(s_current_temp);
		vTaskDelay(200/portTICK_PERIOD_MS) ;
	}

}
