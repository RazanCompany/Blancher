/*
 * LCD.h
 *
 * Created: 9/9/2018 12:08:13 PM
 *  Author: Mohab
 */ 


#ifndef LCD_H_
#define LCD_H_
#include <stdint.h>
#include "Modbus/Modbus_master.h"
/*#include ""*/

/***************************************** LCD Error define ***************************************************/
#define  LCD_OK																			0
#define	 LCD_READ_ERROR																    0x09


/*****************************************  LCD ADDRESSES ******************************************************/
#define LCD_BUZZER_REG       													    0x0002
#define LCD_CURRENT_PIC_REG     												    0x0003
#define  LCD_CURRENT_ENCODER														0x0F02

/***************************************** FUNCTIONS PROTOTYPES ***********************************************/
void Lcd_init(UART_Modules uart_n,uint32_t baudrate,uint8_t slaveID);
uint16_t Lcd_Read(uint16_t address,uint16_t *pData);
void Lcd_Write(uint16_t address, uint16_t value);
void Lcd_Write_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY);
uint16_t Lcd_Read_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY);
void lcd_Jump_to(uint16_t pic_id);
void lcd_Open_buzzer(uint16_t value);
#endif /* LCD_H_ */