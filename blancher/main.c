#define F_CPU 16000000UL

#define  LCD			DEVICE_0
#define  INVERTER   	DEVICE_1

#include <avr/io.h>
#include <util/delay.h>
#include "RTOS_Includes.h"
#include "MCAL/UART.h"
#include "ECUAL/LCD.h"
#include "ECUAl/Drum.h"
#include "ECUAL/Inverter.h"
#include "utils/Millis.h"
#include "MCAL/DIO.h"
#include "Services/LCD_Tasks.h"
#include "RTE/RTE_main.h"
#include "System.h"
#include "application/sequance.h"
#include "Services/tank_operation.h"
#include "application/Temp_monitor.h"
#include "application/errors.h"
#include "application/Level_monitor.h"
#include "ECUAL/levels.h"
#include "Services/Level_Task.h"
#include "Services/TEMP_Task.h"
#include "Services/Ignition_operation.h"
#include "Tasks.h"
#ifdef DEBUG

uint8_t debug_send_lcd[11];
uint8_t debug_rece_lcd[7];

#endif

static void vTask1(void* pvParameters);
static void vTask2(void* pvParameters);
static void vTask3(void* pvParameters);
static void vTask4(void* pvParameters);
static void vTask5(void* pvParameters);
static void vTask6(void* pvParameters);
static void vTask7(void* pvParameters);

#define STACK_SIZE 500
/* Structure that will hold the TCB of the task being created. */
StaticTask_t xTask1Buffer,xTask2Buffer,xTask3Buffer,xTask4Buffer , xTask5Buffer, xTask6Buffer, xTask7Buffer ;
/* Buffer that the task being created will use as its stack. Note this is an array of
StackType_t variables. The size of StackType_t is dependent on the RTOS port. */
StackType_t xStack1[ STACK_SIZE ],xStack2[ STACK_SIZE ],xStack3[ STACK_SIZE ],xStack4[ STACK_SIZE ] , xStack5[ STACK_SIZE ],xStack6[ STACK_SIZE ], xStack7[ STACK_SIZE ];


TaskHandle_t xHandle1 = NULL , xHandle2 = NULL ,xHandle3 = NULL , xHandle4 = NULL ,  xHandle5 = NULL,  xHandle6 = NULL, xHandle7 = NULL;

// VARIABLES TO HOLD LCD RESPONSE IN SELECT MODE PICS
uint16_t select_mode_response ;
uint8_t Wash_flag = 0 , Calibrate_flag = 0 ;


int main(void) {
	DDRE = 0xFF;
	UART0_init(9600); //for debug
    System_init();

/*---------------------- this code will be executed once the machine is on */
while (select_mode_response != READY_MODE)
{
	// 1- the first pic have three values  ready << 1 , caliprate << 2 , wash << 3 .
	LCD_main_wait_select_mode_response(SYSTEM_STATE_RESPONSE , &select_mode_response ) ;
	if (select_mode_response == CALIBRATE_MODE)
	{
		if (Tank_Calibrate() == E_Fail)
		{
			//lcd_Jump_to();    // error in tank calibrate
		}
		else
		{
			lcd_Jump_to(SYSTEM_STATE_CALIBRATE_DONE_PIC);
			_delay_ms(30000);
			// check if calibration is done before .
			if (!Wash_flag)
			{
				Calibrate_flag = 1 ;
				lcd_Jump_to(SYSTEM_STATE_WASH_READY_PIC);
			}
			else  { lcd_Jump_to(SYSTEM_STATE_READY_PIC);}
		}
	}
	else if (select_mode_response == WASH_MODE)
	{
		if (Wash(3) == E_Fail)
		{ /*lcd_Jump_to();    // error in wash */}
		else
		{
			lcd_Jump_to(SYSTEM_STATE_WASH_DONE_PIC);
			_delay_ms(15000);
			// check if WASH is done before .
			if (!Calibrate_flag)
			{
				Wash_flag = 1 ;
				lcd_Jump_to(SYSTEM_STATE_CALIBRATE_READY_PIC);
			}
			else  {lcd_Jump_to(SYSTEM_STATE_READY_PIC) ;}
		}
	}
	else if(select_mode_response == READY_MODE)
	break;
}
lcd_Jump_to(MAIN_SCREEN) ;
	

	/* Create the task without using any dynamic memory allocation. */
	xHandle1 = xTaskCreateStatic( //print LCD data from RTE lowest priority
					vTask1, /* Function that implements the task. */
					"Task1", /* Text name for the task. */
					STACK_SIZE, /* The number of indexes in the xStack array. */
					NULL, /* Parameter passed into the task. */
					2,/* Priority at which the task is created. */
					xStack1, /* Array to use as the task's stack. */
					&xTask1Buffer); /* Variable to hold the task's data structure. */
	
	xHandle2 = xTaskCreateStatic( //LCD highest priority
				vTask2, /* Function that implements the task. */
				"Task2", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				2,/* Priority at which the task is created. */
				xStack2, /* Array to use as the task's stack. */
				&xTask2Buffer); /* Variable to hold the task's data structure. */
				
	xHandle3 = xTaskCreateStatic( //temp mid priority
				vTask3, /* Function that implements the task. */
				"Task3", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				2,/* Priority at which the task is created. */
				xStack3, /* Array to use as the task's stack. */
				&xTask3Buffer); /* Variable to hold the task's data structure. */
	
	xHandle4 = xTaskCreateStatic(
				vTask4, /* Function that implements the task. */
				"Task4", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				2,/* Priority at which the task is created. */
				xStack4, /* Array to use as the task's stack. */
				&xTask4Buffer); /* Variable to hold the task's data structure. */
				
				
	xHandle5 = xTaskCreateStatic(
				vTask5, /* Function that implements the task. */
				"Task5", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				5,/* Priority at which the task is created. */
				xStack5, /* Array to use as the task's stack. */
				&xTask5Buffer); /* Variable to hold the task's data structure. */
	
	
	xHandle6 = xTaskCreateStatic( //print LCD data from RTE lowest priority
					vTask6, /* Function that implements the task. */
					"Task6", /* Text name for the task. */
					STACK_SIZE, /* The number of indexes in the xStack array. */
					NULL, /* Parameter passed into the task. */
					2,/* Priority at which the task is created. */
					xStack6, /* Array to use as the task's stack. */
					&xTask6Buffer); /* Variable to hold the task's data structure. */
					
	xHandle7 = xTaskCreateStatic( //print LCD data from RTE lowest priority
				vTask7, /* Function that implements the task. */
				"Task7", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				2,/* Priority at which the task is created. */
				xStack7, /* Array to use as the task's stack. */
				&xTask7Buffer); /* Variable to hold the task's data structure. */

	  // Start scheduler.
	  //Tank_operation_init();
	  vTaskStartScheduler();


}





static void vTask1(void* pvParameters)
{
	char x=0;
	UART0_puts("Sequence Task1 \n");
//	Level_main(&x);
 //   Sequance_task(&x);
  // Temp_monitor_main(&x);

  while (1)
  {
	 //  UART0_puts("task1 alive\n");
	 vTaskDelay(4000/portTICK_PERIOD_MS);
  }

}
static void vTask2(void* pvParameters)
{
	char x=0;
	LCD_main(&x);
	while(1){
		//Tank_feed_operation(2);
		
		vTaskDelay(4000/portTICK_PERIOD_MS);
	}
}


static void vTask3(void* pvParameters)
{
	char x=0;
	UART0_puts("LEVEL Task3 \n");
	Temp_main(&x);
	while(1){
		vTaskDelay(4000/portTICK_PERIOD_MS);
	}
}

static void vTask4(void* pvParameters)
{
	char x = 0 ;
	UART0_puts("Enter Task4\n");
	//Error_monitor_main(&x);
		while (1)
		{
 			vTaskDelay(300/portTICK_PERIOD_MS);
		}

	
	
}



static void vTask6(void* pvParameters)
{
	char x=0;
	Level_main(&x);
	while (1)
	{	
		vTaskDelay(4000/portTICK_PERIOD_MS);
	}
}




static void vTask7(void* pvParameters){
	char x=0;
	Level_monitor_task(&x);
	while (1)
	{
		vTaskDelay(4000/portTICK_PERIOD_MS);
	}
}







static void vTask5(void* pvParameters)
{
	// watch dog pin .
	while(1)
	{
 		Watch_dog_change_state(HIGH);
		vTaskDelay(250/portTICK_PERIOD_MS);
 		Watch_dog_change_state(LOW);
		vTaskDelay(250/portTICK_PERIOD_MS);
	}	
	
}