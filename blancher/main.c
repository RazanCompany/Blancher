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

int main(void) {
	DDRE = 0xFF;
	UART0_init(9600);
	millis_init();
	DIO_init();
	Lcd_init(UART3,115200,1);
		
// 	TaskHandle_t xHandle1 = NULL , xHandle2 = NULL;
// 	/* Create the task without using any dynamic memory allocation. */
// 	xHandle1 = xTaskCreateStatic(
// 					vTask1, /* Function that implements the task. */
// 					"Task1", /* Text name for the task. */
// 					STACK_SIZE, /* The number of indexes in the xStack array. */
// 					NULL, /* Parameter passed into the task. */
// 					2,/* Priority at which the task is created. */
// 					xStack1, /* Array to use as the task's stack. */
// 					&xTask1Buffer); /* Variable to hold the task's data structure. */
// 	
// 	xHandle2 = xTaskCreateStatic(
// 				vTask2, /* Function that implements the task. */
// 				"Task2", /* Text name for the task. */
// 				STACK_SIZE, /* The number of indexes in the xStack array. */
// 				NULL, /* Parameter passed into the task. */
// 				2,/* Priority at which the task is created. */
// 				xStack2, /* Array to use as the task's stack. */
// 				&xTask2Buffer ); /* Variable to hold the task's data structure. */
// 
// 		xMessageBuffer = xMessageBufferCreateStatic( sizeof( ucStorageBuffer ),
// 														ucStorageBuffer, &xMessageBufferStruct );

	char x=0;
	uint8_t xy=0;
	uint16_t DEBUG_array[16];
	while (1)
	{
		RTE_set_Drum_speed(xy++);
		RTE_set_Current_temperature(xy);
		LCD_main(&x);
		
		DEBUG_array[0]=RTE_get_Threshold_set_temperature();
		DEBUG_array[1]=RTE_get_Threshold_sleep_temperature();
		DEBUG_array[2]=RTE_get_Positive_offset_temperature();
		DEBUG_array[3]=RTE_get_Negative_offset_temperature();
		DEBUG_array[4]=RTE_get_Conveyor_length();
		DEBUG_array[5]=RTE_get_Set_temperature();
		DEBUG_array[6]=RTE_get_Sleep_temperature();
		DEBUG_array[7]=RTE_get_Wash_Operation();
		DEBUG_array[8]=RTE_get_System_on();
		DEBUG_array[9]=RTE_get_Tank_Calibration_Operation();
		DEBUG_array[10]=RTE_get_Start_blancher_Operation(); 
		DEBUG_array[11]=RTE_get_Gear_ratio();
		DEBUG_array[12]=RTE_get_Driver_diameter();
		DEBUG_array[13]=RTE_get_RPM_max(); 
		DEBUG_array[14]=RTE_get_Time_minute();
		DEBUG_array[15]=RTE_get_Time_second();
	
		
		for (uint8_t i=0;i<16;i++)
		{
			UART0_puts("DEBUG_array[");
			UART0_OutUDec(i);
			UART0_puts("] = ");
			UART0_OutUDec(DEBUG_array[i]);
			UART0_putc('\n');
		}
		
		_delay_ms(500);
		
	}
	

	  // Start scheduler.
	  vTaskStartScheduler();

	while (1){}
}



static void vTask1(void* pvParameters)
{
	uint8_t ucArrayToSend[] = { 5, 6, 9, 1 };
	while(1)
	{
			size_t xBytesSent;
		
			for(uint8_t i =0 ;i<4;i++){
				++ucArrayToSend[i];
			}
		const TickType_t x100ms = pdMS_TO_TICKS( 100 );
		/* Send an array to the message buffer, blocking for a maximum of 100ms to
		wait for enough space to be available in the message buffer. */
		UART0_puts("Vtask1 sends data\n");
		for(uint8_t i =0 ; i<4;i++){
				UART0_OutUDec(ucArrayToSend[i]);
				UART0_putc(',');
		}
		UART0_putc('\n');
		xBytesSent = xMessageBufferSend( xMessageBuffer,
										( void * ) ucArrayToSend,
										sizeof( ucArrayToSend ),
										0 );
		UART0_puts("Vtask1 sent_____R data\n");
	    vTaskDelay(4000/portTICK_PERIOD_MS);
										
		
	}
}
static void vTask2(void* pvParameters)
{
	while(1){
		
// 		PORTE |=(1<<1);
// 		UART0_puts("Vtask2 B\n");
// 		vTaskDelay(2000/portTICK_PERIOD_MS);
// 		PORTE &=~(1<<1);
// 		UART0_puts("Vtask2 A\n");
// 		vTaskDelay(2000/portTICK_PERIOD_MS);
		uint8_t ucRxData[ 4 ];
		size_t xReceivedBytes;
		const TickType_t xBlockTime = pdMS_TO_TICKS( 100 );
		/* Receive the next message from the message buffer. Wait in the Blocked
		state (so not using any CPU processing time) for a maximum of 100ms for
		a message to become available. */
		UART0_puts("Vtask2 requires data\n");
		xReceivedBytes = xMessageBufferReceive( xMessageBuffer,
												( void * ) ucRxData,
												sizeof( ucRxData ),
												xBlockTime );
		if(xReceivedBytes==0){
			UART0_puts("NO data\n");
		}
		else{
			UART0_puts("Vtask2 receives data\n");
			for(uint8_t i =0 ; i<4;i++){
				UART0_OutUDec(ucRxData[i]);
				UART0_putc(',');
			}
			UART0_putc('\n');
			//vTaskDelay(1000/portTICK_PERIOD_MS);
		
		}
	
	}
}
// 
// uint16_t x=0;
// void vApplicationIdleHook(void){
// 	UART0_putc('y');	
// 	UART0_putc('\n');
// }
// 




