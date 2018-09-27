/*
 * LCD_tasks.h
 *
 * Created: 9/20/2018 5:45:57 AM
 *  Author: Mohab Adel
 */ 


#ifndef LCD_TASKS_H_
#define LCD_TASKS_H_

#include "../ECUAL/LCD.h"
#define  LCD_READING_TIMEOUT_MATURE																5	//5 * perodicity of lcd main
#define  LCD_WRITING_TIMEOUT_MATURE																5

void LCD_main_Init( void(*callback_read_timeout)(void) , void(*callback_write_timeout)(void));
void LCD_main(void* pvParameters);


#endif /* LCD_TASKS_H_ */