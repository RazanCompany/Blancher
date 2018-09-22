/*
 * LCD_tasks.c
 *
 * Created: 9/20/2018 5:45:47 AM
 *  Author: Mohab Adel
 */ 

/*
Must init modbus for the LCD

*/
#define  F_CPU 16000000
#include "../RTOS_Includes.h"
#include "../ECUAL/LCD.h"
#include <util/delay.h>
/*************** LCD_READ_Parameters ************************/
/*
	Read multiple registers from the LCD .. saves this parameters 



*/
#define LCD_DATA_READ_ELEMENTS_NUMBER   15
#define LCD_DATA_WRITE_ELEMENTS_NUMBER   3
typedef struct LCD_DATA_READ{
	uint16_t data1; //gear ratio
	uint16_t data2; //Motor distance
	uint16_t data3; //gear diameter
	uint16_t data4;	//RPM maximum
	uint16_t data5;
	uint16_t data6; 
	uint16_t data7; 
	uint16_t data8; 
	uint16_t data9;	
	uint16_t data10;
	uint16_t data11; 
	uint16_t data12; 
	uint16_t data13; 
	uint16_t data14;
	uint16_t data15;
	//no padding !!
}s_LCD_DATA_READ_t;

typedef struct LCD_DATA_WRITE{
	uint16_t data1; //temp 
	uint16_t data2; //lvl
	uint16_t data3; //encoder

	//no padding !!
}s_LCD_DATA_WRITE_t;

s_LCD_DATA_READ_t   s_Lcd_data_read;
s_LCD_DATA_WRITE_t   s_Lcd_data_write;

static void LCD_READ_Parameters(void){
	//call LCD_read_mutliple regs (fill the struct) and check for the errors //s_Lcd_data_read
	//set rte parameters
	Lcd_Read_multiple_data(LCD_START_READ_ADDRESS,(uint16_t*)&s_Lcd_data_read,LCD_READ_REGS_NUMBER);
	
}


static void LCD_WRITE_Parameters(void){
	Lcd_Write_multiple_data(LCD_START_WRITE_ADDRESS,(uint16_t*)&s_Lcd_data_write,LCD_WRITE_REGS_NUMBER);
	
}

#define __DEBUG
void LCD_main(void* pvParameters){
	#ifdef __DEBUG
	uint16_t *Debug_read;
	#endif
	while(1){
		#ifdef __DEBUG
			s_Lcd_data_write.data1++;
			s_Lcd_data_write.data2++;
			s_Lcd_data_write.data3++;
			
		#endif
		LCD_READ_Parameters();
		LCD_WRITE_Parameters();
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
		//vTaskDelay(200/portTICK_PERIOD_MS);
		_delay_ms(2000);
		
	}
}



