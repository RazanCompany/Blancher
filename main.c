#define F_CPU 16000000UL

#define LCD			DEVICE_0
#define INVERTER	DEVICE_1

#include <avr/io.h>
#include <util/delay.h>


// #include "ECUAL/Modbus/Modbus_master.h"
// #include "RAL/HW_types.h"
// #include "utils/Millis.h"
// #include "ECUAL/LCD.h"
// #include "DEBUG.h"
// #include <string.h>
#include "RTOS_Includes.h"
#include "MCAL/UART.h"
#include "ECUAL/LCD.h"
#include "utils/Millis.h"
#include "MCAL/DIO.h"
#include "Services/LCD_Tasks.h"
#include "RTE/RTE_main.h"
#include "System.h"

#ifdef DEBUG
uint8_t debug_send_lcd[11];
uint8_t debug_rece_lcd[7];

#endif

static void vTask1(void* pvParameters);
static void vTask2(void* pvParameters);

#define STACK_SIZE 200
/* Structure that will hold the TCB of the task being created. */
StaticTask_t xTask1Buffer,xTask2Buffer;
/* Buffer that the task being created will use as its stack. Note this is an array of
StackType_t variables. The size of StackType_t is dependent on the RTOS port. */
StackType_t xStack1[ STACK_SIZE ],xStack2[ STACK_SIZE ];


TaskHandle_t xHandle1 = NULL , xHandle2 = NULL;


int main(void) {
	DDRE = 0xFF;
	UART0_init(9600); //for debug
    System_init();
		
	
	/* Create the task without using any dynamic memory allocation. */
	xHandle1 = xTaskCreateStatic(
					vTask1, /* Function that implements the task. */
					"Task1", /* Text name for the task. */
					STACK_SIZE, /* The number of indexes in the xStack array. */
					NULL, /* Parameter passed into the task. */
					2,/* Priority at which the task is created. */
					xStack1, /* Array to use as the task's stack. */
					&xTask1Buffer); /* Variable to hold the task's data structure. */
	
	xHandle2 = xTaskCreateStatic(
				vTask2, /* Function that implements the task. */
				"Task2", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				2,/* Priority at which the task is created. */
				xStack2, /* Array to use as the task's stack. */
				&xTask2Buffer); /* Variable to hold the task's data structure. */


// 	char x=0;
// 	uint8_t xy=0;
// 	uint16_t DEBUG_array[16];
// 	while (1)
// 	{
// 		RTE_set_Drum_speed(xy++);
// 		RTE_set_Current_temperature(xy);
// 		LCD_main(&x);
// 		
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
// 		
// 		_delay_ms(500);
// 		
// 	}
// 	

	  // Start scheduler.
	  vTaskStartScheduler();

	while (1)
	{
	}
}



static void vTask1(void* pvParameters)
{
	char x=0;
	LCD_main(&x);
	
// 	while(1)
// 	{
// 		UART0_puts("Vtask1 receives data \n");
// 		xSemaphoreTake(Sema_Test_handle,portMAX_DELAY);
// 		UART0_puts("Vtask1 Released data= ");
// 		UART0_OutUDec(Test);
// 		UART0_putc('\n');
// 	}
}
static void vTask2(void* pvParameters)
{
	uint8_t x=0;
	uint16_t RTE_data=0;
	UART0_puts("Enter Task2");
	while(1){
		UART0_puts("Task2 set current temp with =");
		UART0_OutUDec(x);
		UART0_putc('\n');
		RTE_set_Current_temperature(++x);
		UART0_puts("Task2 Requires ");
		RTE_data = RTE_get_RPM_max();
		UART0_puts("Task2 RTE_data = ");
		UART0_OutUDec(RTE_data);
		UART0_putc('\n');
		
		
	}
	
}

// 
// uint16_t x=0;
// void vApplicationIdleHook(void){
// 	UART0_putc('y');	
// 	UART0_putc('\n');
// }
// 



