/*
 * error_callbacks.c
 *
 * Created: 9/29/2018 6:18:15 AM
 *  Author: Mohab Adel
 */ 
#include "error_callbacks.h"
#include "Services/LCD_Tasks.h"
#include "Services/TEMP_Task.h"
#include "Services/Level_Task.h"
#include "Services/tank_operation.h"
#include "Services/Encoder_Tasks.h"

//debug
#include "MCAL/UART.h"
/******* LCD callback functions for errors callbacks ***********************************************/
static void LCD_readTimeout(void){
	UART0_puts("LCD_READ_TIMEOUT \n");
}

static void LCD_writeTimeout(void){
	UART0_puts("LCD_WRITE_TIMEOUT \n");
	
}

/******* Level sensors functions for error callbacks **********************************************/
static void Level_sensor_error_callback(void){
	UART0_puts("Level_sensor_error_callback \n");
}

/******* Over Temp functions for error callbacks **********************************************/
static void Temperature_over_temp(void){
	UART0_puts("Temperature_over_temp \n");
	
}


void Service_error_init(void){
		LCD_main_err_Init(LCD_readTimeout,LCD_writeTimeout);
		Level_main_err_init(Level_sensor_error_callback);
		Temp_main_err_init(Temperature_over_temp);
}