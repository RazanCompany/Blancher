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


/***************************************** LCD Error define ***************************************************/
#define  LCD_OK																			0
#define	 LCD_READ_ERROR																    0x09
#define  LCD_RESPONCE_TIMED_OUT															RESPONCE_TIMED_OUT


/**** Addresses for Error PICs *************************************/
#define SALT_ERROR_PIC  8
#define SALT_MOTOR_ERROR_PIC   7 
#define DRUM_MOTOR_ERROR_PIC    12  
#define CONVEYOR_MOTOR_ERROR_PIC    11
#define INLET_FLOW_ERROR_PIC    9
#define OUTLET_FLOW_ERROR_PIC    10


/**** Addresses for reply on error PICs *******************************/
#define SALT_ERROR_RESPONSE    0x0A00
#define SALT_MOTOR_ERROR_RESPONSE   0x0A05
#define DRUM_MOTOR_ERROR_RESPONSE    0x0A04
#define CONVEYOR_MOTOR_ERROR_RESPONSE    0x0A03
#define INLET_FLOW_ERROR_RESPONSE    0x0A01
#define OUTLET_FLOW_ERROR_RESPONSE    0x0A02 






/*****************************************  LCD ADDRESSES ******************************************************/
#define  LCD_BUZZER_REG       													    0x0002
#define  LCD_CURRENT_PIC_REG     												    0x0003
#define  LCD_CURRENT_ENCODER														0x0F02
#define  LCD_TEMP_DATA																0x0009
#define	 LCD_START_READ_ADDRESS														0x0001
#define  LCD_START_WRITE_ADDRESS													0x0F00
#define  LCD_READ_REGS_NUMBER													    17
#define  LCD_WRITE_REGS_NUMBER														2
/***************************************** FUNCTIONS PROTOTYPES ***********************************************/
void Lcd_init(UART_Modules uart_n,uint32_t baudrate,uint8_t slaveID);
uint16_t Lcd_Read(uint16_t address,uint16_t *pData);
void Lcd_Write(uint16_t address, uint16_t value);
uint8_t Lcd_Write_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY);
uint8_t Lcd_Read_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY);
void lcd_Jump_to(uint16_t pic_id);
void lcd_set_buzzer(uint16_t value);
#endif /* LCD_H_ */