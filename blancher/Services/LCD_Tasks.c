/*
 * LCD_tasks.c
 *
 * Created: 9/20/2018 5:45:47 AM
 *  Author: Mohab Adel
 */ 

/*
Must init modbus for the LCD

*/
#define  F_CPU		16000000
#include "LCD_Tasks.h"
#include "../RTOS_Includes.h"
#include "../RTE/RTE_encoders.h" //drum speed w
#include "../RTE/RTE_invertersetting.h"
#include "../RTE/RTE_temperature.h"
#include "../RTE/RTE_operations.h"
#include "../ECUAL/LCD.h"

#include "../utils/Millis.h"

#include <util/delay.h>
/*************** LCD_READ_Parameters ************************/
/*
	Read multiple registers from the LCD .. saves this parameters 



*/
#define  LCD_DATA_READ_ELEMENTS_NUMBER			 15
#define  LCD_DATA_WRITE_ELEMENTS_NUMBER			 3
typedef struct LCD_DATA_READ{
	uint16_t System_on; //system on
	uint16_t Start_blancher_operation; //blancher start
	uint16_t Wash_operation; //wash operation
	uint16_t Tank_calibration_operation;	//calibration operation
	uint16_t Sleep_temp; //sleep temperature
	uint16_t Set_temp; //set temperature
	uint16_t Threshold_set_temp; //threshold set temperature
	uint16_t Threshold_sleep_temp; //threshold sleep temperature
	uint16_t Positive_offset_temp;	//temperature offset + 
	uint16_t Negative_offset_temp; //temperature offset -
	uint16_t Gear_ratio; //gear ratio
	uint16_t Conveyor_length; //conveyor length
	uint16_t Driver_diameter;  //gear diameter
	uint16_t RPM_max; //maximum RPM
	uint16_t Time_minute; //time minute
	uint16_t Time_second; //time second
	
	//no padding !!
}s_LCD_DATA_READ_t;

typedef struct LCD_DATA_WRITE{
	uint16_t Drum_speed; //drum speed 
	uint16_t Current_temperature; //current temperature

	//no padding !!
}s_LCD_DATA_WRITE_t;

s_LCD_DATA_READ_t   s_Lcd_data_read;
s_LCD_DATA_WRITE_t   s_Lcd_data_write;

void (*g_callback_read_timeout)(void) = NULL;
void (*g_callback_write_timeout)(void) = NULL;

void LCD_main_err_Init( void(*callback_read_timeout)(void) , void(*callback_write_timeout)(void)){
	g_callback_read_timeout = callback_read_timeout;
	g_callback_write_timeout = callback_write_timeout;
}


static uint8_t LCD_READ_Parameters(void){
	//call LCD_read_mutliple regs (fill the struct) and check for the errors //s_Lcd_data_read
	//set rte parameters
	return Lcd_Read_multiple_data(LCD_START_READ_ADDRESS,(uint16_t*)&s_Lcd_data_read,LCD_READ_REGS_NUMBER);

}


static uint8_t LCD_WRITE_Parameters(void){
	return Lcd_Write_multiple_data(LCD_START_WRITE_ADDRESS,(uint16_t*)&s_Lcd_data_write,LCD_WRITE_REGS_NUMBER);
	
}

//drum speed & current temp
//s_Lcd_data_read
static void LCD_RTE_FEED(void){
	RTE_set_Set_temperature(s_Lcd_data_read.Set_temp);
	RTE_set_Sleep_temperature(s_Lcd_data_read.Sleep_temp);
	RTE_set_Threshold_set_temperature(s_Lcd_data_read.Threshold_set_temp);
	RTE_set_Threshold_sleep_temperature(s_Lcd_data_read.Threshold_sleep_temp);
	RTE_set_Negative_offset_temperature(s_Lcd_data_read.Negative_offset_temp);
	RTE_set_Positive_offset_temperature(s_Lcd_data_read.Positive_offset_temp);
	RTE_set_System_on(s_Lcd_data_read.System_on);
	RTE_set_Wash_Operation(s_Lcd_data_read.Wash_operation);
	RTE_set_Tank_Calibration_Operation(s_Lcd_data_read.Tank_calibration_operation);
	RTE_set_Gear_ratio(s_Lcd_data_read.Gear_ratio);
	RTE_set_Conveyor_length(s_Lcd_data_read.Conveyor_length);
	RTE_set_Driver_diameter(s_Lcd_data_read.Driver_diameter);
	RTE_set_Time_minute(s_Lcd_data_read.Time_minute);
	RTE_set_Time_second(s_Lcd_data_read.Time_second);
	RTE_set_RPM_max(s_Lcd_data_read.RPM_max);
	RTE_set_Start_blancher_Operation(s_Lcd_data_read.Start_blancher_operation);
}


static void LCD_RTE_COLLECT(void){
		s_Lcd_data_write.Drum_speed = RTE_get_Drum_speed();
		s_Lcd_data_write.Current_temperature = RTE_get_Current_temperature();
}

//#define __DEBUG
void LCD_main(void* pvParameters){
	#ifdef __DEBUG
	uint16_t *Debug_read;
	#endif
	uint8_t r_err, w_err;
	static uint8_t read_err_counter = 0 ,write_err_counter = 0 ;
    Lcd_init(UART3,115200,1);
	unsigned int x_time = 0;
	while(1){
		
		x_time = Get_millis();
		//UART0_puts("LCD alive \n");
		r_err =  LCD_READ_Parameters();
 		if(LCD_RESPONCE_TIMED_OUT == r_err)
 		{
			 read_err_counter++;
			 if(LCD_READING_TIMEOUT_MATURE == read_err_counter){
				//  callback error notification for reading timeout
				if(g_callback_read_timeout == NULL){
					//no entry
				}
				else
				{
					g_callback_read_timeout();
				}
				
			 
			 }
			 
 		}
	    else{
 			LCD_RTE_FEED();	
			read_err_counter = 0;
 		}
 		
  		LCD_RTE_COLLECT();
 		w_err = LCD_WRITE_Parameters();
		if(LCD_RESPONCE_TIMED_OUT == w_err)
		{
			write_err_counter++;
			if( LCD_WRITING_TIMEOUT_MATURE == write_err_counter){
				//callback error notification for writing timeout
				if(g_callback_write_timeout == NULL){
					//no entry
				}
				else{
					g_callback_write_timeout();
				}	
			}
		}
		else{
			write_err_counter = 0;
		}
		
		#ifdef __DEBUG
		Debug_read=(uint16_t*)&s_Lcd_data_read;
			for (uint8_t i=0;i<LCD_DATA_WRITE_ELEMENTS_NUMBER;i++){
				
				UART0_puts("s_Lcd_data_read[");
				UART0_OutUDec(i+1);
				UART0_puts("]= ");
				UART0_OutUDec(Debug_read[i]);
				UART0_puts("\n");
				
			}
		#endif
		x_time =  Get_millis() - x_time;
		UART0_puts("LCD Exe time = ");
		UART0_OutUDec(x_time);
		UART0_putc('\n');
		_delay_ms(1000);
		vTaskDelay(40/portTICK_PERIOD_MS);
		//_delay_ms(2000);
	}
}



