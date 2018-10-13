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

#include "ECUAL/levels.h"
#include "Services/Level_Task.h"
#include "Services/TEMP_Task.h"
#ifdef DEBUG

uint8_t debug_send_lcd[11];
uint8_t debug_rece_lcd[7];

#endif

static void vTask1(void* pvParameters);
static void vTask2(void* pvParameters);
static void vTask3(void* pvParameters);
static void vTask4(void* pvParameters);
static void vTask5(void* pvParameters);


#define STACK_SIZE 500
/* Structure that will hold the TCB of the task being created. */
StaticTask_t xTask1Buffer,xTask2Buffer,xTask3Buffer,xTask4Buffer , xTask5Buffer;
/* Buffer that the task being created will use as its stack. Note this is an array of
StackType_t variables. The size of StackType_t is dependent on the RTOS port. */
StackType_t xStack1[ STACK_SIZE ],xStack2[ STACK_SIZE ],xStack3[ STACK_SIZE ],xStack4[ STACK_SIZE ] , xStack5[ STACK_SIZE ];


TaskHandle_t xHandle1 = NULL , xHandle2 = NULL ,xHandle3 = NULL , xHandle4 = NULL , xHandle5 = NULL ;




int main(void) {
	DDRE = 0xFF;
	UART0_init(9600); //for debug
    System_init();
	
	//Lcd_init(UART3,115200,1);
	UART0_puts("start \n");
// 	g_Inveter_Config confg;
// 	confg.gear_diameter = 6;
// 	confg.gear_ratio = 80;
// 	confg.distance = 210;
// 	confg.motor_rpm_max = 900;
// 	confg.time_user_M = 0;
// 	confg.time_user_S = 5;
//   while (1)
//   {
//   	UART0_puts("SALT ");
// 	UART0_OutUDec(Salt_dropped_successfully());
// 	UART0_putc('\n');
// 	_delay_ms(1000);
// 
//  }
	//Temp_main_init();
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

/*uint16_t res=0;*/
uint8_t watchdog =0 , output=0;
uint16_t count=0;
	while(1){
		count++;
		//watchdog^=1;
// 		Lcd_Read(LCD_IGNITION_TYPE_ADDRESS,&res);
// 		UART0_puts("res = ");
// 		UART0_OutUDec(res);
// 		UART0_putc('\n');
// 		_delay_ms(1000);
		for (uint16_t i =0 ; i<8  ; i++)
		{
			watchdog^=1;
			Watch_dog_change_state(watchdog);
			_delay_ms(1000);
		}
		output ^=1;
// 		Conveyor_motor_change_state(output);
// 		Spark_change_state(output);
	//	Gas_valve_change_state(output);
	//	Main_gas_valve_change_state(output); //error
	//	Sareen_change_state(output);
	//	Powder_motor_change_state(output);
		Pump_change_state(output);
	//	Tank_valve_1_change_state(output	
	//	Tank_valve_2_change_state(output);
	//	Blancher_valve_change_state(output);		
		
	}
// 	

	  // Start scheduler.
	  //Tank_operation_init();
	  vTaskStartScheduler();

}





static void vTask1(void* pvParameters)
{
//	char x=0;
	UART0_puts("Sequence Task1 \n");
//	Level_main(&x);
 //   Sequance_task(&x);
  while (1)
  {
	 //  UART0_puts("task1 alive\n");
	 vTaskDelay(200/portTICK_PERIOD_MS);
  }

}
static void vTask2(void* pvParameters)
{
	//char x=0;
	//LCD_main(&x);
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
}

static void vTask4(void* pvParameters)
{
	UART0_puts("Enter Task4\n");
	//uint16_t response =0 ;
		while (1)
		{
			
// 			LCD_main_Report_error(DRUM_MOTOR_ERROR_PIC);
// 			LCD_main_wait_error_response(DRUM_MOTOR_ERROR_RESPONSE,&response);
// 			UART0_puts("RESPONSE = ");
// 			UART0_OutUDec(response);
// 			UART0_putc('\n');
 			vTaskDelay(300/portTICK_PERIOD_MS);
		}
	// 	uint16_t DEBUG_array[16];
	// 	while(1)
	// 	{
	// 		DEBUG_array[0]=RTE_get_Threshold_set_temperature();
	// 		DEBUG_array[1]=RTE_get_Threshold_sleep_temperature();
	// 		DEBUG_array[2]=RTE_get_Positive_offset_temperature();
	// 		DEBUG_array[3]=RTE_get_Negative_offset_temperature();
	// 		DEBUG_array[4]=RTE_get_Conveyor_length();
	// 		DEBUG_array[5]=RTE_get_Set_temperature();
	// 		DEBUG_array[6]=RTE_get_Sleep_temperature();
	// 		DEBUG_array[7]=RTE_get_Wash_Operation();
	// 		DEBUG_array[8]=RTE_get_System_on();
	// 		DEBUG_array[9]=RTE_get_Tank_Calibration_Operation();
	// 		DEBUG_array[10]=RTE_get_Start_blancher_Operation();
	// 		DEBUG_array[11]=RTE_get_Gear_ratio();
	// 		DEBUG_array[12]=RTE_get_Driver_diameter();
	// 		DEBUG_array[13]=RTE_get_RPM_max();
	// 		DEBUG_array[14]=RTE_get_Time_minute();
	// 		DEBUG_array[15]=RTE_get_Time_second();
	//
	//
	// 		for (uint8_t i=0;i<16;i++)
	// 		{
	// 			UART0_puts("DEBUG_array[");
	// 			UART0_OutUDec(i);
	// 			UART0_puts("] = ");
	// 			UART0_OutUDec(DEBUG_array[i]);
	// 			UART0_putc('\n');
	// 		}
	// 		vTaskDelay(500/portTICK_PERIOD_MS);
	//
	// 	}
	
	
}


static void vTask5(void* pvParameters)
{
	// watch dog pin .
	while(1)
	{
// 		Watch_dog_change_state(HIGH);
// 		Watch_dog_change_state(LOW);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}	
	
}
