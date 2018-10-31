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

/**** Systems Error Pic Addresses *******************************/
#define DRUM_ERROR_PIC				  20
#define OVER_TEMP_ERROR_PIC		   	  21
#define CONVEYOR_ERROR_PIC			  22
#define iGNITION_TYPE_PIC			  23
#define GAS_ERROR_PIC				  24
#define TANK_FEED_OPERATION_FAIL_PIC	25 //flow rate or water off 
#define POWDER_TANK_FAIL_PIC			26 // salt not exist powder drop sensor fail + motor + encoder
#define LEVEL_SENSORS_FAIL_PIC			27 //call back or level monitor set that error through error monitor function
#define TANK_LEVEL_2_FAIL_PIC			28
#define TANK_LEVEL_1_FAIL_PIC			29
#define TANK_SHOULD_BE_EMPTY_PIC		30
#define TANK_OUT_FAIL_PIC				31
#define BLANCHER_EMPTY_AND_TANK_ERROR_WITH_WATER_INLET_PIC	 32
#define BLANCHER_LEVEL_EMPTY_AND_TANK_POWDER_DROP_ERROR_PIC	 33
#define SYSTEM_STATE_WASH_CALIBRATE_READY_PIC		56
#define SYSTEM_STATE_WASH_READY_PIC					57
#define SYSTEM_STATE_CALIBRATE_READY_PIC			58
#define SYSTEM_STATE_READY_PIC						59
#define SYSTEM_STATE_WASH_DONE_PIC					61
#define SYSTEM_STATE_CALIBRATE_DONE_PIC				63
// #define SYSTEM_STATE_CALIBRATING_PIC
// #define SYSTEM_STATE_WASHING_PIC
/**** Addresses for reply on error PICs *******************************/
#define SALT_ERROR_RESPONSE    0x0A00
#define SALT_MOTOR_ERROR_RESPONSE   0x0A05
#define DRUM_MOTOR_ERROR_RESPONSE    0x0A04
#define CONVEYOR_MOTOR_ERROR_RESPONSE    0x0A03
#define INLET_FLOW_ERROR_RESPONSE    0x0A01
#define OUTLET_FLOW_ERROR_RESPONSE    0x0A02 
#define SYSTEM_STATE_RESPONSE		0x0A06

/**** Addresses for mode selection at the beginng of the machine .****/
#define  MAIN_SCREEN                         50
#define  WASH_READY_PIC                      57
#define  CALIBRATE_READY_PIC                 58
#define  READY_PIC                           59
#define  CALIBRATION_DONE_PIC                63
#define  WASH_DONE_PIC                       61


/**** Addresses for reply on mode selection PICs ***/
#define  CALIBRATE_WASH_READY_RESPONSE      0X0A06







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
uint8_t Lcd_Write(uint16_t address, uint16_t value);
uint8_t Lcd_Write_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY);
uint8_t Lcd_Read_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY);
uint8_t lcd_Jump_to(uint16_t pic_id);
uint8_t lcd_set_buzzer(uint16_t value);
#endif /* LCD_H_ */