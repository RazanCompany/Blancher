/*
 * LCD_tasks.c
 *
 * Created: 9/20/2018 5:45:47 AM
 *  Author: Mohab Adel
 */ 

/*
Must init modbus for the LCD

*/

#include "../RTOS_Includes.h"
#include "../ECUAL/LCD.h"

/*************** LCD_READ_Parameters ************************/
/*
	Read multiple registers from the LCD .. saves this parameters 



*/
#define LCD_DATA_READ_ELEMENTS_NUMBER   4
#define LCD_DATA_WRITE_ELEMENTS_NUMBER   4
typedef struct LCD_DATA_READ{
	uint16_t data1; //temp
	uint16_t data2; 
	uint16_t data3;
	uint16_t data4;
	//no padding !!
}s_LCD_DATA_READ_t;

typedef struct LCD_DATA_WRITE{
	uint16_t data1; //temp
	uint16_t data2;
	uint16_t data3;
	uint16_t data4;
	//no padding !!
}s_LCD_DATA_WRITE_t;

s_LCD_DATA_READ_t   s_Lcd_data_read;
s_LCD_DATA_WRITE_t   s_Lcd_data_write;

static void LCD_READ_Parameters(void){
	//call LCD_read_mutliple regs (fill the struct) and check for the errors //s_Lcd_data_read
	//set rte parameters
}


static void LCD_WRITE_Parameters(void){
	//get rte data non blocking //s_Lcd_data_write
	//call write multiple regs (check for errors)
	
}


void LCD_main(void* pvParameters){
	
	while(1){
// 		LCD_READ_Parameters();
// 		LCD_WRITE_Parameters();
	vTaskDelay(200/portTICK_PERIOD_MS);
		
	}
}



