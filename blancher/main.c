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
 #include "rtos/FreeRTOS.h"
#include "rtos/task.h"
#include "MCAL/UART.h"


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





int main() {
	DDRE = 0xFF;
	UART0_init(9600);
	TaskHandle_t xHandle1 = NULL , xHandle2 = NULL ;
	//UART2_init(115200);
	/* Create the task without using any dynamic memory allocation. */
	xHandle1 = xTaskCreateStatic(
					vTask1, /* Function that implements the task. */
					"Task1", /* Text name for the task. */
					STACK_SIZE, /* The number of indexes in the xStack array. */
					NULL, /* Parameter passed into the task. */
					2,/* Priority at which the task is created. */
					xStack1, /* Array to use as the task's stack. */
					&xTask1Buffer ); /* Variable to hold the task's data structure. */
	
	xHandle2 = xTaskCreateStatic(
				vTask2, /* Function that implements the task. */
				"Task2", /* Text name for the task. */
				STACK_SIZE, /* The number of indexes in the xStack array. */
				NULL, /* Parameter passed into the task. */
				2,/* Priority at which the task is created. */
				xStack2, /* Array to use as the task's stack. */
				&xTask2Buffer ); /* Variable to hold the task's data structure. */
	
// 	  xTaskCreateStatic(vTask1, "task1", 300, NULL, 2, NULL);
// 	  xTaskCreateStatic(vTask2, "task2", 300, NULL, 2, NULL);

	  // Start scheduler.
	  vTaskStartScheduler();
	//DIO_init();
	//millis_init();
	//01100f0200010200019972
// 	debug_send_lcd[0]=0x01;
// 	debug_send_lcd[1]=0x10;
// 	debug_send_lcd[2]=0x0f; 
// 	debug_send_lcd[3]=0x02;
// 	debug_send_lcd[4]=0x00;
// 	debug_send_lcd[5]=0x01;
// 	debug_send_lcd[6]=0x02;
// 	
// 	debug_send_lcd[7]=0x00;
// 	debug_send_lcd[8]=0x05;
// 	debug_send_lcd[9]=0x98;
// 	debug_send_lcd[10]=0xB1;
	

//	Lcd_init(UART2,115200,0x01);
	//UART0_puts("START\n");
//	uint16_t rece;
	while (1) {
		
		//PORTE ^=0xFF;
		//_delay_ms(1000);
	//	UART0_puts("START\n");
		//LCD_pre_transmission();
		//_delay_ms(2000);
// 		for(uint8_t i=0;i<11;i++){
// 			UART2_putc(debug_send_lcd[i]);
// 		}
	//	UART2_flush();
	//	_delay_us(100);
	//	UART0_puts("HERE \n");
	//	LCD_post_transmission();
// 	Lcd_Write(LCD_CURRENT_ENCODER,30);
// 		   _delay_ms(2000);
// 	Lcd_Read(0x0009,&rece);
// 	UART0_puts("Receive = ");
// 	UART0_OutUDec(rece);
// 	UART0_putc('\n');
// 	_delay_ms(3000);
// 	lcd_Open_buzzer(500);
// 	lcd_Jump_to(2);
// 	_delay_ms(5000);
// 	
// 	

	}
}
static void vTask1(void* pvParameters)
{
	while(1)
	{
		PORTE |=(1<<0);
		UART0_puts("Vtask1 B\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
		PORTE &=~(1<<0);
		UART0_puts("Vtask1 A\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
		
		
	}
}
static void vTask2(void* pvParameters)
{
	while(1){
		
		PORTE |=(1<<1);
		UART0_puts("Vtask2 B\n");
		vTaskDelay(2000/portTICK_PERIOD_MS);
		PORTE &=~(1<<1);
		UART0_puts("Vtask2 A\n");
		vTaskDelay(2000/portTICK_PERIOD_MS);
	}
	
}
// 
// uint16_t x=0;
// void vApplicationIdleHook(void){
// 	UART0_putc('y');	
// 	UART0_putc('\n');
// }
// 




