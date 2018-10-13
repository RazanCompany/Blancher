/*
 * sequance.c
 *
 * Created: 07/10/2018 01:18:24 م
 *  Author: ENG
 */ 
#define  F_CPU 16000000
#include "sequance.h"
#include "../GLOBAL.h"
#include "../MCAL/DIO.h"

#include "../Services/tank_operation.h"
#include "../ECUAL/Inverter.h"
#include "../ECUAL/Drum.h"
#include "../ECUAL/PowderIF.h"
#include "util/delay.h"
#include "../ECUAL/LCD.h"
#include "../RTOS_Includes.h"
#include "../RTOS_sync.h"




#include "../DEBUG.h"


g_Inveter_Config Inverter_check_config;
gSystemError errors ;

void Sequance_task(void* pvParameters)
{	
#ifdef SALT_EXIST_CHECK 
 	if (Salt_exist() != 1)
 	{
 		UART0_puts("salt error \n");
 		uint16_t response  = 0;
		xSemaphoreTake( LCD_mutex_handle , portMAX_DELAY );
		UART0_puts("S T M\n");
		lcd_Jump_to( SALT_ERROR_PIC );
 		while(response == 0 )
 		{
			vTaskDelay(200/portTICK_PERIOD_MS);
 			Lcd_Read(SALT_ERROR_RESPONSE,&response);
			
 		}
		xSemaphoreGive(LCD_mutex_handle);
		UART0_puts("S R M\n");
		
	}
	
 #endif	
 #ifdef POWDER_DROP_CHECK  
 	if( Powder_drop(2) == E_Fail){
 		uint16_t response  = 0;
 		UART0_puts(" powder error \n");
		xSemaphoreTake( LCD_mutex_handle , portMAX_DELAY ) ;
		UART0_puts("P T M\n");
 		lcd_Jump_to(DRUM_MOTOR_ERROR_PIC  );
 		while(response == 0 )
 		{
		    vTaskDelay(200/portTICK_PERIOD_MS); 
 			Lcd_Read(DRUM_MOTOR_ERROR_RESPONSE,&response);
 		}
		xSemaphoreGive(LCD_mutex_handle);
		UART0_puts("P R M\n");
	}
#endif
#ifdef TANK_FEED_CHECK  
	if( Tank_feed_operation(2) == E_Fail){
		uint16_t response  = 0;
		UART0_puts(" feed error \n");
		xSemaphoreTake( LCD_mutex_handle , portMAX_DELAY ) ;
		UART0_puts("TF T M\n");
		lcd_Jump_to(INLET_FLOW_ERROR_PIC  );
		
		while(response == 0 )
		{
			vTaskDelay(200/portTICK_PERIOD_MS);
			Lcd_Read(INLET_FLOW_ERROR_RESPONSE,&response);
		}
		xSemaphoreGive(LCD_mutex_handle);
		UART0_puts("TF R M\n");
	}
#endif
#ifdef TANK_OUT_CHECK  

 	if( Tank_out_operation(2) == E_Fail){
 		uint16_t response  = 0;
 	    UART0_puts(" Tank out error\n");
 	
		xSemaphoreTake( LCD_mutex_handle , portMAX_DELAY ) ;
		UART0_puts("TO T M\n");
		lcd_Jump_to(OUTLET_FLOW_ERROR_PIC  );
 		while(response == 0 )
 		{
			vTaskDelay(200/portTICK_PERIOD_MS);
 			Lcd_Read(OUTLET_FLOW_ERROR_RESPONSE,&response);
 		}
		xSemaphoreGive(LCD_mutex_handle);
		UART0_puts("TO R M\n");
	}
#endif
#ifdef DRUM_CONVEYOR_CHECK   
	Inverter_check_config.distance = distance ;
	Inverter_check_config.gear_ratio=gear_ratio;
	Inverter_check_config.gear_diameter = gear_diameter;
	Inverter_check_config.motor_rpm_max = motor_rpm_max;
	Inverter_check_config.time_user_M = 0;
	Inverter_check_config.time_user_S = 5 ;
			
	// check inverter & conveyor
	Inverter_set_Freq(&Inverter_check_config);
	vTaskDelay(1000/portTICK_PERIOD_MS);
	Inverter_change_state(HIGH);
	Conveyor_motor_change_state(HIGH);
	vTaskDelay(15000/portTICK_PERIOD_MS);
	if( Drum_speed() == 0){
		UART0_puts(" Drum speed Err \n");
		Inverter_change_state(LOW);
 		uint16_t response  = 0;
		xSemaphoreTake( LCD_mutex_handle , portMAX_DELAY ) ;
		UART0_puts("D T M\n");
		lcd_Jump_to(DRUM_MOTOR_ERROR_PIC );
		vTaskDelay(200/portTICK_PERIOD_MS);
 		while(response == 0 )
 		{
			Lcd_Read(DRUM_MOTOR_ERROR_RESPONSE,&response);
			vTaskDelay(200/portTICK_PERIOD_MS);
 		}
		UART0_puts("Response = ");
		UART0_OutUDec(response);
		UART0_putc('\n');
		xSemaphoreGive(LCD_mutex_handle);
		UART0_puts("D R M\n");
	}
 	Inverter_change_state(LOW);
 	
//  	if( Get_conveyor_state() == 0){
//  		//UART0_puts(" con Error \n");
//  	
//  		Conveyor_motor_change_state(LOW);
// 		uint16_t response  = 0;
//  		xSemaphoreTake( LCD_mutex_handle , portMAX_DELAY ) ;
// 		UART0_puts("C T M\n");
//  		lcd_Jump_to(CONVEYOR_MOTOR_ERROR_PIC );
// 		_delay_ms(200);
//  		while(response == 0 )
//  		{
// 			Lcd_Read(CONVEYOR_MOTOR_ERROR_RESPONSE,&response);
// 			_delay_ms(200);
//  		}
//  		xSemaphoreGive(LCD_mutex_handle);
// 		UART0_puts("C R M\n");
// 	 }
//  	Conveyor_motor_change_state(LOW);	
#endif
	while (1) 
	{
		UART0_puts(" inside seq \n");
		vTaskDelay(500/portTICK_PERIOD_MS);
		
	}
}

