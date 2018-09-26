/*
 * TEMP_Task.c
 *
 * Created: 9/22/2018 4:24:23 PM
 *  Author: M.nagah
 */ 
#include "TEMP_Task.h"
#include "../ECUAL/Temperature.h"
#include "../ECUAL/LCD.h"
#include <util/delay.h>
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
		//set on RTE
		//vTaskDelay()
		_delay_ms(1000);
	}

}
