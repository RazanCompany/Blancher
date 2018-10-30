/*
 * LCD_tasks.h
 *
 * Created: 9/20/2018 5:45:57 AM
 *  Author: Mohab Adel
 */ 


#ifndef LCD_TASKS_H_
#define LCD_TASKS_H_

#include <stdint.h>

#define  LCD_READING_TIMEOUT_MATURE																5	//5 * periodicity of LCD main
#define  LCD_WRITING_TIMEOUT_MATURE																5


#define LCD_main_wait_error_response  LCD_main_wait_response

void LCD_main_err_Init( void(*callback_read_timeout)(void) , void(*callback_write_timeout)(void));
void LCD_main(void* pvParameters);
uint8_t LCD_main_Report_error_warning(uint16_t PIC_ID);
uint8_t LCD_main_wait_response(uint16_t Response_address, uint16_t* response);

#endif /* LCD_TASKS_H_ */