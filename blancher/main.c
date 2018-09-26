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

#include "RTE/RTE_encoders.h" //drum speed w
#include "RTE/RTE_invertersetting.h"
#include "RTE/RTE_temperature.h"
#include "RTE/RTE_operations.h"
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


#define STORAGE_SIZE_BYTES 100
/* Defines the memory that will actually hold the messages within the message
buffer. Should be one more than the value passed in the xBufferSizeBytes
parameter. */
static uint8_t ucStorageBuffer[ STORAGE_SIZE_BYTES ];
/* The variable used to hold the message buffer structure. */
StaticMessageBuffer_t xMessageBufferStruct;
MessageBufferHandle_t xMessageBuffer;


static SemaphoreHandle_t Sema_Test_handle;
static StaticSemaphore_t Sema_Test_Buffer;
static uint16_t Test;

int main(void) {
	DDRE = 0xFF;
	UART0_init(9600);
	millis_init();
	DIO_init();
	Lcd_init(UART3,115200,1);
		
	TaskHandle_t xHandle1 = NULL , xHandle2 = NULL;
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
				&xTask2Buffer ); /* Variable to hold the task's data structure. */

	Sema_Test_handle = xSemaphoreCreateBinaryStatic(&Sema_Test_Buffer);

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

	
	while(1)
	{
		UART0_puts("Vtask1 receives data \n");
		xSemaphoreTake(Sema_Test_handle,portMAX_DELAY);
		UART0_puts("Vtask1 Released data= ");
		UART0_OutUDec(Test);
		UART0_putc('\n');
	}
}
static void vTask2(void* pvParameters)
{
	while(1){
		Test++;
		UART0_puts("Vtask2 sends data = ");
		UART0_OutUDec(Test);
		UART0_putc('\n');
		xSemaphoreGive(Sema_Test_handle);
		UART0_puts("Vtask2 Gives the semaphore\n");
		vTaskDelay(4000/portTICK_PERIOD_MS);
	}
	
}

// 
// uint16_t x=0;
// void vApplicationIdleHook(void){
// 	UART0_putc('y');	
// 	UART0_putc('\n');
// }
// 




