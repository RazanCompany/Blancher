/*
 * Modbus_master.h
 *
 *  Created on: Aug 15, 2018
 *      Author: Muhammad
 */

/**
C library for communicating with Modbus slaves over RS232/485 (via RTU protocol).

 setup ModbusMaster Object Instantiation/Initialization
 buffer ModbusMaster Buffer Management
 discrete Modbus Function Codes for Discrete Coils/Inputs
 register Modbus Function Codes for Holding/Input Registers
 constant Modbus Function Codes, Exception Codes
 Modbus_master.h - C library for communicating with Modbus slaves
 over RS232/485 (via RTU protocol).
*/






#ifndef ECUAL_MODBUS_MODBUS_MASTER_H_
#define ECUAL_MODBUS_MODBUS_MASTER_H_


#include <stdint.h>

#include "../../MCAL/UART.h"
/* _____Defines _____________________________________________________ */

//device defines
//
//#define LCD_DEVICE_MODBUS    		0
//#define INVERTER_DEVICE_MODBUS 		1

#include "../../CONFIG.h"

/*

#define DEVICE_0 					0
#define DEVICE_1 					1

*/

// Modbus exception codes

#define _ERROR 0xFFFF
/** Modbus protocol illegal function exception.
The function code received in the query is not an allowable action for
the server (or slave). This may be because the function code is only
applicable to newer devices, and was not implemented in the unit
selected. It could also indicate that the server (or slave) is in the
wrong state to process a request of this type, for example because it is
unconfigured and is being asked to return register values.*/
#define ILLEGAL_FUNCTION			(0x01)



/** Modbus protocol illegal data address exception.
The data address received in the query is not an allowable address for the server (or slave). More specifically, the combination of reference
number and transfer length is invalid. For a controller with 100 registers, the ADU addresses the first register as 0, and the last one
as 99. If a request is submitted with a starting register address of 96 and a quantity of registers of 4, then this request will successfully
operate (address-wise at least) on registers 96, 97, 98, 99. If a request is submitted with a starting register address of 96 and a
quantity of registers of 5, then this request will fail with Exception Code 0x02 "Illegal Data Address" since it attempts to operate on
registers 96, 97, 98, 99 and 100, and there is no register with address 100. */
#define ILLEGAL_DATA_ADDRESS		(0x02)


/** Modbus protocol illegal data value exception. A value contained in the query data field is not an allowable value for
server (or slave). This indicates a fault in the structure of the remainder of a complex request, such as that the implied length is
incorrect. It specifically does NOT mean that a data item submitted for storage in a register has a value outside the expectation of the
application program, since the MODBUS protocol is unaware of the significance of any particular value of any particular register.*/
#define ILLEGAL_DATA_VALUE			(0x03)

/**Modbus protocol slave device failure exception.
An unrecoverable error occurred while the server (or slave) was
attempting to perform the requested action.*/
#define SLAVE_DEVICE_FAILURE		(0x04)

/** ModbusMaster success. Modbus transaction was successful; the following checks were valid:
  - slave ID
  - function code
  - response code
  - data
  - CRC */
#define SUCCESS						(0x00)

/** ModbusMaster invalid response slave ID exception.
The slave ID in the response does not match that of the request.*/
#define INVALID_SLAVE_ID			(0xE0)

/** ModbusMaster invalid response function exception.
The function code in the response does not match that of the request.*/
#define	INVALID_FUNCTION			(0xE1)

/** ModbusMaster response timed out exception.
The entire response was not received within the timeout period,
ModbusMaster::ku8MBResponseTimeout.*/
#define RESPONCE_TIMED_OUT			(0xE2)

/** ModbusMaster invalid response CRC exception.
The CRC in the response does not match the one calculated.*/
#define INVALID_CRC					(0xE3)


#define INVALID_DEVICE				(0xE4)


// Modbus function codes for bit access
#define READ_COILS						(0x01)			 ///< Modbus function 0x01 Read Coils
#define READ_DISCRETE_INPUTS			(0x02)			 ///< Modbus function 0x02 Read Discrete Inputs
#define WRITE_SINGLE_COIL				(0x05)			 ///< Modbus function 0x05 Write Single Coil
#define WRITE_MULTIPLE_COILS			(0x0F)			 ///< Modbus function 0x0F Write Multiple Coils
#define OUR_WRITE_MULTIPLE_COILS		(0xFF)			 ///< <
#define READ_HOLDING_REGISTERS			(0x03)			 ///< Modbus function 0x03 Read Holding Registers
#define READ_INPUT_REGISTERS			(0x04)			 ///< Modbus function 0x04 Read Input Registers
#define WRITE_SINGLE_REGISTER 			(0x06)			 ///< Modbus function 0x06 Write Single Register
#define WRITE_MULTIPLE_REGISTERS		(0x10)			 ///< Modbus function 0x10 Write Multiple Registers
#define MASK_WRITE_REGISTER				(0x16)			 ///< Modbus function 0x16 Mask Write Register
#define READ_WRITE_MULTIPLE_REGISTERS 	(0x17)			 ///< Modbus function 0x17 Read Write Multiple Registers
#define RESPONCE_TIME_OUT				 2000			     //< Modbus timeout [milliseconds]

// static const uint8_t ku8MaxBufferSize                = 64;   ///< size of response/transmit buffers
#define MAX_BUFFER_SIZE					64

// Modbus initail struct
typedef struct{
	uint8_t slave_address;
	UART_Modules uart_num;
	uint32_t baud_rate;
	void (*pre_transmission)();
	void (*post_transmission)();
} modbus_config;


// __Public Functions__________________________________________________________________


void Modbus_init(uint8_t device_num, modbus_config* mod);
void Modbus_Begin_transmission(uint8_t device, uint16_t address);
//uint8_t Modbus_Request_from(uint8_t device, uint16_t address, uint16_t quantity);
void Modbus_Send_16(uint8_t device, uint16_t data);
void Modbus_Send_8(uint8_t device, uint8_t data);
void Modbus_Send_32(uint8_t device, uint32_t data);
uint8_t Modbus_Available(uint8_t device);
uint16_t Modbus_Receive(uint8_t device);
void Modbus_Idle(uint8_t device, void (*idle)());
uint16_t Modbus_Get_response_buffer(uint8_t device, uint8_t u8Index);
void Modbus_Clear_response_buffer(uint8_t device);
uint8_t Modbus_Set_transmit_buffer(uint8_t device, uint8_t u8Index, uint16_t u16Value);
void Modbus_Clear_transmit_buffer(uint8_t device);
uint8_t Modbus_Read_coils(uint8_t device, uint16_t u16ReadAddress, uint16_t u16BitQty);
uint8_t Modbus_Read_discrete_inputs(uint8_t device, uint16_t u16ReadAddress, uint16_t u16BitQty);
uint8_t Modbus_Read_holding_registers(uint8_t device, uint16_t u16ReadAddress, uint16_t u16ReadQty);
uint8_t Modbus_Read_input_registers(uint8_t device, uint16_t u16ReadAddress, uint8_t u16ReadQty);
uint8_t Modbus_Write_single_coil(uint8_t device, uint16_t u16WriteAddress, uint8_t u8State);
uint8_t Modbus_Write_single_register(uint8_t device, uint16_t u16WriteAddress, uint16_t u16WriteValue);
uint8_t Modbus_Write_multiple_coils(uint8_t device, uint16_t u16WriteAddress, uint16_t u16BitQty);
uint8_t Modbus_Our_write_multiple_coils(uint8_t device, uint16_t u16WriteAddress, uint16_t u16BitQty);
uint8_t Modbus_Write_multiple_registers(uint8_t device,uint16_t u16WriteAddress, uint16_t u16WriteQty);
uint8_t Modbus_Mask_write_register(uint8_t device, uint16_t u16WriteAddress, uint16_t u16AndMask, uint16_t u16OrMask);
uint8_t Modbus_Read_write_multiple_registers(uint8_t device, uint16_t u16ReadAddress, uint16_t u16ReadQty, uint16_t u16WriteAddress, uint16_t u16WriteQty);







// _Private_Functions_________________________________________________________________

// master function that conducts Modbus transactions
//static uint8_t Modbus_mster_transaction(uint8_t device, uint8_t u8MBFunction);










#endif /* ECUAL_MODBUS_MODBUS_MASTER_H_ */
