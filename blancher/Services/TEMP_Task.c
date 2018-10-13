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
#include "../utils/Millis.h"
/*static uint16_t s_current_temp;*/
/*
*Set the Temperatur on RTE
*Parameters @ Nothing
*return Nothing 
*/
void (*over_temp_callback)(void) = NULL;
void Temp_main_err_init( void (*callback_over_temp) (void) ){
	over_temp_callback = callback_over_temp;
}

void Temp_main(void* pvParameters){
	uint16_t current_temp=0;
	uint8_t count=0;
	//uint16_t x_time = 0;
	while (1)
	{
		UART0_puts("Temp task alive\n");
		//x_time = Get_millis();
		current_temp = temp_read();
		//UART0_puts("current temp = ");
 		//UART0_OutUDec(current_temp);
 		//UART0_putc('\n');
		if(current_temp > TEMP_OVER_TEMP){
			count++;
			if(count >= TEMP_OVER_TEMP_STILL_TIME){
				//callback
				if(over_temp_callback == NULL){
					
				}
				else
				{
					 over_temp_callback();
				}
			}
			RTE_set_app_Current_temperature(INVALID_DATA);
			
		}
		else{
		// set temp for LCD 
				// set the temp for the application .

			RTE_set_app_Current_temperature(current_temp);
			RTE_set_Current_temperature(current_temp);
		}
		//
		//x_time =  Get_millis() - x_time ;
		//UART0_puts("temp ex time = ");
		//UART0_OutUDec(x_time);
		//UART0_putc('\n');
		vTaskDelay(50/portTICK_PERIOD_MS) ;
	}

}
