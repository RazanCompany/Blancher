
/* _____PROJECT INCLUDES_____________________________________________________ */
#include "Modbus_master.h"

// functions to calculate Modbus Application Data Unit CRC
#include "../../utils/CRC16.h"


#include "../../utils/Millis.h"
#include "../../RAL/HW_types.h"
#include <stdint.h>
#include <util/delay.h>
#include <util/atomic.h>

/*#define DEBUG_RECE */
/**********Private Function Prototypes*************************************************************/
static uint8_t Modbus_mster_transaction(uint8_t device, uint8_t u8MBFunction);


//************************************************************************Temp
#define millis() Get_millis()

#define lowByte(w) ((uint8_t) ((w) & 0xff)) // GET_LOW_BYTE
#define highByte(w) ((uint8_t) ((w) >> 8))	// GET_HIGH_BYTE
/*_______________________________________ Global Variables  _____________________________________________*/


//______________________________ MOD_0 parameters _______________________________________

static uint8_t  g_mod0_slave;                                  ///< Modbus slave (1..255) initialized in begin()
static UART_Modules  g_mod0_uart_no;
static uint32_t  g_mod0_baud_rate;

static uint16_t g_mod0_read_address;                           ///< slave register from which to read
static uint16_t g_mod0_read_qty;                               ///< quantity of words to read
static uint16_t volatile g_mod0_response_buffer[MAX_BUFFER_SIZE];       ///< buffer to store Modbus slave response; read via GetResponseBuffer()
static uint16_t g_mod0_write_address;                          ///< slave register to which to write
static uint16_t g_mod0_write_qty;                              ///< quantity of words to write
static uint16_t volatile	g_mod0_transmit_buffer[MAX_BUFFER_SIZE];       ///< buffer containing data to transmit to Modbus slave; set via SetTransmitBuffer()

static uint8_t g_mod0_transmit_buffer_index;
static uint16_t g_mod0_transmit_buffer_length;

static uint8_t g_mod0_response_buffer_index;
static uint8_t g_mod0_response_buffer_length;


// idle callback function; gets called during idle time between TX and RX
static void (*g_mod0_idle)(void);
// preTransmission callback function; gets called before writing a Modbus message
static void (*g_mod0_pre_transmission)(void);
// postTransmission callback function; gets called after a Modbus message has been sent
static void (*g_mod0_post_transmission)(void);
//serial functions
static void (*g_mod0_Serial_putc)(uint8_t);
static uint16_t (*g_mod0_Serial_getc)(void);
static void (*g_mod0_Serial_flush)(void);
static uint16_t (*g_mod0_Serial_peek)(void);
static uint16_t (*g_mod0_Serial_available)(void);
static void (*g_mod0_Serial_puts)(const char*);
static void (*g_mod0_Serial_puts_p)(const char*);
//______________________________ MOD_1 parameters _______________________________________

//Stream* _serial;                                             ///< reference to serial port object

static uint8_t  g_mod1_slave;                                  ///< Modbus slave (1..255) initialized in begin()
static UART_Modules  g_mod1_uart_no;
static uint32_t  g_mod1_baud_rate;

static uint16_t g_mod1_read_address;                           ///< slave register from which to read
static uint16_t g_mod1_read_qty;                               ///< quantity of words to read
static uint16_t volatile g_mod1_response_buffer[MAX_BUFFER_SIZE];       ///< buffer to store Modbus slave response; read via GetResponseBuffer()
static uint16_t g_mod1_write_address;                          ///< slave register to which to write
static uint16_t g_mod1_write_qty;                              ///< quantity of words to write
static uint16_t volatile g_mod1_transmit_buffer[MAX_BUFFER_SIZE];       ///< buffer containing data to transmit to Modbus slave; set via SetTransmitBuffer()

static uint8_t g_mod1_transmit_buffer_index;
static uint16_t g_mod1_transmit_buffer_length;

static uint8_t g_mod1_response_buffer_index;
static uint8_t g_mod1_response_buffer_length;



// idle callback function; gets called during idle time between TX and RX
static void (*g_mod1_idle)(void);
// preTransmission callback function; gets called before writing a Modbus message
static void (*g_mod1_pre_transmission)(void);
// postTransmission callback function; gets called after a Modbus message has been sent
static void (*g_mod1_post_transmission)(void);
//serial functions
static void (*g_mod1_Serial_putc)(uint8_t);
static uint16_t (*g_mod1_Serial_getc)(void);
static uint16_t (*g_mod1_Serial_peek)(void);
static void (*g_mod1_Serial_puts)(const char*);
static void (*g_mod1_Serial_puts_p)(const char*);
static uint16_t (*g_mod1_Serial_available)(void);
static void (*g_mod1_Serial_flush)(void);


/**
Initialize modbu.

Assigns the Modbus slave ID and serial port and modbus config struct.
Call once , typically within setup().

*/


void Modbus_init(uint8_t device_num, modbus_config* mod){

	//
	static uint8_t UART1_used=0;
	static uint8_t UART2_used=0;
	static uint8_t UART3_used=0;
	if(device_num  == 0){
		g_mod0_slave = mod->slave_address;
		g_mod0_uart_no = mod->uart_num;
		g_mod0_baud_rate = mod->baud_rate;

		g_mod0_pre_transmission = mod->pre_transmission;
		g_mod0_post_transmission = mod->post_transmission;

		g_mod0_idle = mod->modbus_idle_task;
		g_mod0_response_buffer_index = 0;
		g_mod0_response_buffer_length = 0;
		if(UART1 == g_mod0_uart_no){
			if(0 == UART1_used){//uart1 not used
				UART1_used = 1;
				
				UART1_init(g_mod0_baud_rate);
				g_mod0_Serial_available = UART1_available;
				g_mod0_Serial_peek = UART1_peek;
				g_mod0_Serial_flush = UART1_flush;
				g_mod0_Serial_puts = UART1_puts;
				g_mod0_Serial_getc = UART1_getc;
				g_mod0_Serial_putc = UART1_putc;
				g_mod0_Serial_puts_p = UART1_puts_p;
			}
			else {
				//error uart1 used before
			}
		}
		else if(UART2 == g_mod0_uart_no){
			if(0 == UART2_used){//uart2 not used
				UART2_used = 1;
				UART2_init(g_mod0_baud_rate);
				g_mod0_Serial_available = UART2_available;
				g_mod0_Serial_peek = UART2_peek;
				g_mod0_Serial_flush = UART2_flush;
				g_mod0_Serial_puts = UART2_puts;
				g_mod0_Serial_getc = UART2_getc;
				g_mod0_Serial_putc = UART2_putc;
				g_mod0_Serial_puts_p = UART2_puts_p;
			}
			else{
				//error uart2 used before
			}
		}
		else if(UART3 == g_mod0_uart_no){
			if(0 == UART3_used){//uart2 not used
				UART3_used = 1;
				UART3_init(g_mod0_baud_rate);
				g_mod0_Serial_available = UART3_available;
				g_mod0_Serial_peek = UART3_peek;
				g_mod0_Serial_flush = UART3_flush;
				g_mod0_Serial_puts = UART3_puts;
				g_mod0_Serial_getc = UART3_getc;
				g_mod0_Serial_putc = UART3_putc;
				g_mod0_Serial_puts_p = UART3_puts_p;
			}
			else{
				//error uart3 used before
			}
			
		}
		else{
			//error uart number is not corect;
		}




	}
	else if(device_num == 1){
		g_mod1_slave = mod->slave_address;
		g_mod1_uart_no = mod->uart_num;
		g_mod1_baud_rate = mod->baud_rate;

		g_mod1_pre_transmission = mod->pre_transmission;
		g_mod1_post_transmission = mod->post_transmission;

		g_mod1_idle = mod->modbus_idle_task;
		g_mod1_response_buffer_index = 0;
		g_mod1_response_buffer_length = 0;
		if(UART1 == g_mod1_uart_no){
			if(0 == UART1_used){//uart1 not used
				UART1_used = 1;		
				UART1_init(g_mod1_baud_rate);
				g_mod1_Serial_available = UART1_available;
				g_mod1_Serial_peek = UART1_peek;
				g_mod1_Serial_flush = UART1_flush;
				g_mod1_Serial_puts = UART1_puts;
				g_mod1_Serial_getc = UART1_getc;
				g_mod1_Serial_putc = UART1_putc;
				g_mod1_Serial_puts_p = UART1_puts_p;

			}
			else {
				//error uart1 used before
			}
		}
		else if(UART2 == g_mod1_uart_no){
			if(0 == UART2_used){//uart2 not used
				UART2_used = 1;
				UART2_init(g_mod1_baud_rate);
				g_mod1_Serial_available = UART2_available;
				g_mod1_Serial_peek = UART2_peek;
				g_mod1_Serial_flush = UART2_flush;
				g_mod1_Serial_puts = UART2_puts;
				g_mod1_Serial_getc = UART2_getc;
				g_mod1_Serial_putc = UART2_putc;
				g_mod1_Serial_puts_p = UART2_puts_p;
			}
			else{
				//error uart2 used before
			}
		}
		else{
			//error uart number is not corect;
		}


	}
}



void Modbus_Begin_transmission(uint8_t device, uint16_t address)
{
	if( DEVICE_0 == device ){
		g_mod0_write_address = address;
		g_mod0_transmit_buffer_index = 0;
		g_mod0_transmit_buffer_length = 0;

	}
	else if( DEVICE_1 == device ){
		g_mod1_write_address = address;
		g_mod1_transmit_buffer_index = 0;
		g_mod1_transmit_buffer_length = 0;

	}

}

void Modbus_Send_16(uint8_t device, uint16_t data)
{

	if(DEVICE_0 == device){

		if (g_mod0_transmit_buffer_index < MAX_BUFFER_SIZE)
		{
			g_mod0_transmit_buffer[g_mod0_transmit_buffer_index++] = data;
			g_mod0_transmit_buffer_length = g_mod0_transmit_buffer_index << 4;
		}

	}
	else if(DEVICE_1 == device){

		if (g_mod1_transmit_buffer_index < MAX_BUFFER_SIZE)
		{
			g_mod1_transmit_buffer[g_mod1_transmit_buffer_index++] = data;
			g_mod1_transmit_buffer_length = g_mod1_transmit_buffer_index << 4;
		}

	}

}


void Modbus_Send_8(uint8_t device, uint8_t data){
	uint16_t data_16 = data;
	Modbus_Send_16(device, data_16);

}


void Modbus_Send_32(uint8_t device, uint32_t data){

	Modbus_Send_16(device, GET_LOW_WORD(data));
	Modbus_Send_16(device, GET_HIGH_WORD(data));
}


uint8_t Modbus_Available(uint8_t device)
{
	if(DEVICE_0 == device){
		return g_mod0_response_buffer_length - g_mod0_response_buffer_index;
	}
	else if(DEVICE_1 == device){
		return g_mod1_response_buffer_length - g_mod1_response_buffer_index;
	}

	return 0;

}

uint16_t Modbus_Receive(uint8_t device)
{
	if(DEVICE_0 == device){

		if (g_mod0_response_buffer_index < g_mod0_response_buffer_length)
		{
			return g_mod0_response_buffer[g_mod0_response_buffer_length++];
		}
		else
		{
			return 0xFFFF;
		}
	}
	else if(DEVICE_1 == device){

		if (g_mod1_response_buffer_index < g_mod1_response_buffer_length)
		{
			return g_mod1_response_buffer[g_mod1_response_buffer_length++];
		}
		else
		{
			return 0xFFFF;
		}
	}


	return 0xFFFF;

}

/**
Set idle time callback function (cooperative multitasking).

This function gets called in the idle time between transmission of data
and response from slave. Do not call functions that read from the serial
buffer that is used by ModbusMaster. Use of i2c/TWI, 1-Wire, other
serial ports, etc. is permitted within callback function.

@see ModbusMaster::ModbusMasterTransaction()
*/
void Modbus_Idle(uint8_t device, void (*idle)(void))
{
	if(DEVICE_0 == device){
		g_mod0_idle = idle;
	}
	else if(DEVICE_1 == device){
		g_mod1_idle = idle;
	}

}

/**
Retrieve data from response buffer.

@see ModbusMaster::clearResponseBuffer()
@param u8Index index of response buffer array (0x00..0x3F)
@return value in position u8Index of response buffer (0x0000..0xFFFF)
@ingroup buffer
*/
uint16_t Modbus_Get_response_buffer(uint8_t device, uint8_t u8Index)
{
	if(DEVICE_0 == device){
		if (u8Index < MAX_BUFFER_SIZE)
		{
			return g_mod0_response_buffer[u8Index];
		}
		else
		{
			return 0xFFFF;
		}
	}
	else if(DEVICE_1 == device){
		if (u8Index < MAX_BUFFER_SIZE)
		{
			return g_mod1_response_buffer[u8Index];
		}
		else
		{
			return 0xFFFF;
		}
	}

	return 0xFFFF;
}



/**
Clear Modbus response buffer.

@see ModbusMaster::getResponseBuffer(uint8_t u8Index)
@ingroup buffer
*/
void Modbus_Clear_response_buffer(uint8_t device)
{
	if(DEVICE_0 == device){

		uint8_t i;
		for (i = 0; i < MAX_BUFFER_SIZE; i++)
		{
		  g_mod0_response_buffer[i] = 0;
		}

	}
	else if(DEVICE_1 == device){

		uint8_t i;
		for (i = 0; i < MAX_BUFFER_SIZE; i++)
		{
		  g_mod1_response_buffer[i] = 0;
		}

	}
}

/**
Place data in transmit buffer.

@see ModbusMaster::clearTransmitBuffer()
@param u8Index index of transmit buffer array (0x00..0x3F)
@param u16Value value to place in position u8Index of transmit buffer (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup buffer
*/
uint8_t Modbus_Set_transmit_buffer(uint8_t device, uint8_t u8Index, uint16_t u16Value)
{
	if(DEVICE_0 == device){

		if (u8Index < MAX_BUFFER_SIZE)
		{
			g_mod0_transmit_buffer[u8Index] = u16Value;
			return SUCCESS;
		}
		else
		{
			return ILLEGAL_DATA_ADDRESS;
		}
	}
	else if(DEVICE_1 == device){

		if (u8Index < MAX_BUFFER_SIZE)
		{
			g_mod1_transmit_buffer[u8Index] = u16Value;
			return SUCCESS;
		}
		else
		{
			return ILLEGAL_DATA_ADDRESS;
		}

	}

	return ILLEGAL_DATA_ADDRESS;

}


/**
Clear Modbus transmit buffer.

@see ModbusMaster::setTransmitBuffer(uint8_t u8Index, uint16_t u16Value)
@ingroup buffer
*/
void Modbus_Clear_transmit_buffer(uint8_t device)
{
	if(DEVICE_0 == device){
		uint8_t i;
		for (i = 0; i < MAX_BUFFER_SIZE; i++)
		{
			g_mod0_transmit_buffer[i] = 0;
		}
	}
	else if(DEVICE_1 == device){

		uint8_t i;
		for (i = 0; i < MAX_BUFFER_SIZE; i++)
		{
			g_mod1_transmit_buffer[i] = 0;
		}
	}
}


/**
Modbus function 0x01 Read Coils.

This function code is used to read from 1 to 2000 contiguous status of
coils in a remote device. The request specifies the starting address,
i.e. the address of the first coil specified, and the number of coils.
Coils are addressed starting at zero.

The coils in the response buffer are packed as one coil per bit of the
data field. Status is indicated as 1=ON and 0=OFF. The LSB of the first
data word contains the output addressed in the query. The other coils
follow toward the high order end of this word and from low order to high
order in subsequent words.

If the returned quantity is not a multiple of sixteen, the remaining
bits in the final data word will be padded with zeros (toward the high
order end of the word).

@param u16ReadAddress address of first coil (0x0000..0xFFFF)
@param u16BitQty quantity of coils to read (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t Modbus_Read_coils(uint8_t device, uint16_t u16ReadAddress, uint16_t u16BitQty)
{
	if(DEVICE_0 == device){
		g_mod0_read_address = u16ReadAddress;
		g_mod0_read_qty = u16BitQty;
		return Modbus_mster_transaction(device, READ_COILS);
	}
	else if(DEVICE_1 == device){
		g_mod1_read_address = u16ReadAddress;
		g_mod1_read_qty = u16BitQty;
		return Modbus_mster_transaction(device, READ_COILS);
	}

	return INVALID_DEVICE; //error
}



/**
Modbus function 0x02 Read Discrete Inputs.

This function code is used to read from 1 to 2000 contiguous status of
discrete inputs in a remote device. The request specifies the starting
address, i.e. the address of the first input specified, and the number
of inputs. Discrete inputs are addressed starting at zero.

The discrete inputs in the response buffer are packed as one input per
bit of the data field. Status is indicated as 1=ON; 0=OFF. The LSB of
the first data word contains the input addressed in the query. The other
inputs follow toward the high order end of this word, and from low order
to high order in subsequent words.

If the returned quantity is not a multiple of sixteen, the remaining
bits in the final data word will be padded with zeros (toward the high
order end of the word).

@param u16ReadAddress address of first discrete input (0x0000..0xFFFF)
@param u16BitQty quantity of discrete inputs to read (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t Modbus_Read_discrete_inputs(uint8_t device, uint16_t u16ReadAddress, uint16_t u16BitQty)
{
	if(DEVICE_0 == device){
		g_mod0_read_address = u16ReadAddress;
		g_mod0_read_qty = u16BitQty;
		return Modbus_mster_transaction(device, READ_DISCRETE_INPUTS);
	}
	else if(DEVICE_1== device){
		g_mod1_read_address = u16ReadAddress;
		g_mod1_read_qty = u16BitQty;
		return Modbus_mster_transaction(device, READ_DISCRETE_INPUTS);
	}
	return INVALID_DEVICE; //error
}

/**
Modbus function 0x03 Read Holding Registers.

This function code is used to read the contents of a contiguous block of
holding registers in a remote device. The request specifies the starting
register address and the number of registers. Registers are addressed
starting at zero.

The register data in the response buffer is packed as one word per
register.

@param u16ReadAddress address of the first holding register (0x0000..0xFFFF)
@param u16ReadQty quantity of holding registers to read (1..125, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t Modbus_Read_holding_registers(uint8_t device, uint16_t u16ReadAddress, uint16_t u16ReadQty)
{
	if(DEVICE_0 == device){
		g_mod0_read_address = u16ReadAddress;
		g_mod0_read_qty = u16ReadQty;
		return Modbus_mster_transaction(device, READ_HOLDING_REGISTERS);

	}
	else if(DEVICE_1 == device){
		g_mod1_read_address = u16ReadAddress;
		g_mod1_read_qty = u16ReadQty;
		return Modbus_mster_transaction(device, READ_HOLDING_REGISTERS);
	}
	return INVALID_DEVICE; //error
}


/**
Modbus function 0x04 Read Input Registers.

This function code is used to read from 1 to 125 contiguous input
registers in a remote device. The request specifies the starting
register address and the number of registers. Registers are addressed
starting at zero.

The register data in the response buffer is packed as one word per
register.

@param u16ReadAddress address of the first input register (0x0000..0xFFFF)
@param u16ReadQty quantity of input registers to read (1..125, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t Modbus_Read_input_registers(uint8_t device, uint16_t u16ReadAddress, uint8_t u16ReadQty)
{
	if(DEVICE_0 == device){
		g_mod0_read_address = u16ReadAddress;
		g_mod0_read_qty = u16ReadQty;
		return Modbus_mster_transaction(device, READ_INPUT_REGISTERS);

	}
	else if(DEVICE_1 == device){
		g_mod1_read_address = u16ReadAddress;
		g_mod1_read_qty = u16ReadQty;
		return Modbus_mster_transaction(device, READ_INPUT_REGISTERS);

	}
	return INVALID_DEVICE; //error
}


/**
Modbus function 0x05 Write Single Coil.

This function code is used to write a single output to either ON or OFF
in a remote device. The requested ON/OFF state is specified by a
constant in the state field. A non-zero value requests the output to be
ON and a value of 0 requests it to be OFF. The request specifies the
address of the coil to be forced. Coils are addressed starting at zero.

@param u16WriteAddress address of the coil (0x0000..0xFFFF)
@param u8State 0=OFF, non-zero=ON (0x00..0xFF)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t Modbus_Write_single_coil(uint8_t device, uint16_t u16WriteAddress, uint8_t u8State)
{
	if(DEVICE_0 == device){
		g_mod0_write_address = u16WriteAddress;
		g_mod0_write_qty = (u8State ? 0xFF00 : 0x0000);
		return Modbus_mster_transaction(device, WRITE_SINGLE_COIL);

	}
	else if(DEVICE_1 == device){
		g_mod1_write_address = u16WriteAddress;
		g_mod1_write_qty = (u8State ? 0xFF00 : 0x0000);
		return Modbus_mster_transaction(device, WRITE_SINGLE_COIL);
	}
	return INVALID_DEVICE; //error
}



/**
Modbus function 0x06 Write Single Register.

This function code is used to write a single holding register in a
remote device. The request specifies the address of the register to be
written. Registers are addressed starting at zero.

@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16WriteValue value to be written to holding register (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t Modbus_Write_single_register(uint8_t device, uint16_t u16WriteAddress, uint16_t u16WriteValue)
{
	if(DEVICE_0 == device){
		g_mod0_write_address = u16WriteAddress;
		g_mod0_write_qty = 0;
		g_mod0_transmit_buffer[0] = u16WriteValue;
		return Modbus_mster_transaction(device, WRITE_SINGLE_REGISTER);

	}
	else if(DEVICE_1 == device){
		g_mod1_write_address = u16WriteAddress;
		g_mod1_write_qty = 0;
		g_mod1_transmit_buffer[0] = u16WriteValue;
		return Modbus_mster_transaction(device, WRITE_SINGLE_REGISTER);
	}
	return INVALID_DEVICE; //error
}


/**
Modbus function 0x0F Write Multiple Coils.

This function code is used to force each coil in a sequence of coils to
either ON or OFF in a remote device. The request specifies the coil
references to be forced. Coils are addressed starting at zero.

The requested ON/OFF states are specified by contents of the transmit
buffer. A logical '1' in a bit position of the buffer requests the
corresponding output to be ON. A logical '0' requests it to be OFF.

@param u16WriteAddress address of the first coil (0x0000..0xFFFF)
@param u16BitQty quantity of coils to write (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t Modbus_Write_multiple_coils(uint8_t device, uint16_t u16WriteAddress, uint16_t u16BitQty)
{
	if(DEVICE_0 == device){
		g_mod0_write_address = u16WriteAddress;
		g_mod0_write_qty = u16BitQty;
		return Modbus_mster_transaction(device, WRITE_MULTIPLE_COILS);
	}
	else if(DEVICE_1 == device){
		g_mod1_write_address = u16WriteAddress;
		g_mod1_write_qty = u16BitQty;
		return Modbus_mster_transaction(device, WRITE_MULTIPLE_COILS);
	}
	return INVALID_DEVICE; //error
}

/** Our write multiple coils  **/
uint8_t Modbus_Our_write_multiple_coils(uint8_t device, uint16_t u16WriteAddress, uint16_t u16BitQty)
{
	if(DEVICE_0 == device){
		g_mod0_write_address = u16WriteAddress;
		g_mod0_write_qty = u16BitQty;
		return Modbus_mster_transaction(device, OUR_WRITE_MULTIPLE_COILS);

	}
	else if(DEVICE_1 == device){
		g_mod1_write_address = u16WriteAddress;
		g_mod1_write_qty = u16BitQty;
		return Modbus_mster_transaction(device, OUR_WRITE_MULTIPLE_COILS);
	}
	return INVALID_DEVICE; //error
}

//mohab add
/**
Modbus function 0x10 Write Multiple Registers.

This function code is used to write a block of contiguous registers (1 
to 123 registers) in a remote device.

The requested written values are specified in the transmit buffer. Data 
is packed as one word per register.

@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16WriteQty quantity of holding registers to write (1..123, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t Modbus_Write_multiple_registers(uint8_t device,uint16_t u16WriteAddress, uint16_t u16WriteQty)
{
	if(DEVICE_0 == device){
	
		g_mod0_write_address = u16WriteAddress;
		g_mod0_write_qty = u16WriteQty;
		return Modbus_mster_transaction(device, WRITE_MULTIPLE_REGISTERS);
	}
	else if(DEVICE_1 == device){
		g_mod1_write_address = u16WriteAddress;
		g_mod1_write_qty = u16WriteQty;
		return Modbus_mster_transaction(device, WRITE_MULTIPLE_REGISTERS);
	}
	return  INVALID_DEVICE;
}



/**
Modbus function 0x16 Mask Write Register.

This function code is used to modify the contents of a specified holding 
register using a combination of an AND mask, an OR mask, and the 
register's current contents. The function can be used to set or clear 
individual bits in the register.

The request specifies the holding register to be written, the data to be 
used as the AND mask, and the data to be used as the OR mask. Registers 
are addressed starting at zero.

The function's algorithm is:

Result = (Current Contents && And_Mask) || (Or_Mask && (~And_Mask))

@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16AndMask AND mask (0x0000..0xFFFF)
@param u16OrMask OR mask (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t Modbus_Mask_write_register(uint8_t device, uint16_t u16WriteAddress, uint16_t u16AndMask, uint16_t u16OrMask)
{
	if(DEVICE_0 == device){
		g_mod0_write_address = u16WriteAddress;
		g_mod0_transmit_buffer[0] = u16AndMask;
		g_mod0_transmit_buffer[1] = u16OrMask;
	   return Modbus_mster_transaction(device, MASK_WRITE_REGISTER);
	}
	else if(DEVICE_1 == device){
	    g_mod1_write_address = u16WriteAddress;
	    g_mod1_transmit_buffer[0] = u16AndMask;
	    g_mod1_transmit_buffer[1] = u16OrMask;
	    return Modbus_mster_transaction(device, MASK_WRITE_REGISTER);
		
	}
	return INVALID_DEVICE; //error

}



/**
Modbus function 0x17 Read Write Multiple Registers.

This function code performs a combination of one read operation and one 
write operation in a single MODBUS transaction. The write operation is 
performed before the read. Holding registers are addressed starting at 
zero.

The request specifies the starting address and number of holding 
registers to be read as well as the starting address, and the number of 
holding registers. The data to be written is specified in the transmit 
buffer.

@param u16ReadAddress address of the first holding register (0x0000..0xFFFF)
@param u16ReadQty quantity of holding registers to read (1..125, enforced by remote device)
@param u16WriteAddress address of the first holding register (0x0000..0xFFFF)
@param u16WriteQty quantity of holding registers to write (1..121, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t Modbus_Read_write_multiple_registers(uint8_t device, uint16_t u16ReadAddress,
						uint16_t u16ReadQty, uint16_t u16WriteAddress, uint16_t u16WriteQty)
{
	if(DEVICE_0 == device){
	    g_mod0_read_address = u16ReadAddress;
	    g_mod0_read_qty = u16ReadQty;
	    g_mod0_write_address = u16WriteAddress;
	    g_mod0_write_qty = u16WriteQty;
	    return Modbus_mster_transaction(device, READ_WRITE_MULTIPLE_REGISTERS);
	}
	else if(DEVICE_1 == device){
	    g_mod1_read_address = u16ReadAddress;
	    g_mod1_read_qty = u16ReadQty;
	    g_mod1_write_address = u16WriteAddress;
	    g_mod1_write_qty = u16WriteQty;
	    return Modbus_mster_transaction(device, READ_WRITE_MULTIPLE_REGISTERS);
	}
	return INVALID_DEVICE;//error
}




/* _____PRIVATE FUNCTIONS____________________________________________________ */
/**
Modbus transaction engine.
Sequence:
  - assemble Modbus Request Application Data Unit (ADU),
    based on particular function called
  - transmit request over selected serial port
  - wait for/retrieve response
  - evaluate/disassemble response
  - return status (success/exception)

@param u8MBFunction Mod bus function (0x01..0xFF)
@return 0 on success; exception number on failure
*/

static uint8_t Modbus_mster_transaction(uint8_t device, uint8_t u8MBFunction){

	if(DEVICE_0 == device){

		uint8_t u8_mod0_ADU[256];
		uint8_t u8_mod0_ADU_size = 0;
		uint8_t mod0_i, u8_mod0_Qty;
		uint16_t u16_mod0_CRC;
		uint32_t u32_mod0_start_time;
		uint8_t u8_mod0_bytes_left = 8;
		uint8_t u8MB_mod0_status = SUCCESS;

		/*------------------------------------------------------------------------------------------*/
		// assemble Mod bus Request Application Data Unit
		u8_mod0_ADU[u8_mod0_ADU_size++] = g_mod0_slave;
		if(u8MBFunction == 0xFF){
			u8_mod0_ADU[u8_mod0_ADU_size++] = 0x0F;
		}
		else{
			u8_mod0_ADU[u8_mod0_ADU_size++] = u8MBFunction;
		}

		switch(u8MBFunction)
		{
		case READ_COILS:
		case READ_DISCRETE_INPUTS:
		case READ_INPUT_REGISTERS:
		case READ_HOLDING_REGISTERS:
		case READ_WRITE_MULTIPLE_REGISTERS:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_read_address);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_read_address);
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_read_qty);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_read_qty);
			break;
		}

		switch(u8MBFunction)
		{
		case WRITE_SINGLE_COIL:
		case MASK_WRITE_REGISTER:
		case WRITE_MULTIPLE_COILS:
		case WRITE_SINGLE_REGISTER:
		case WRITE_MULTIPLE_REGISTERS:
		case READ_WRITE_MULTIPLE_REGISTERS:
		case OUR_WRITE_MULTIPLE_COILS:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_write_address);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_write_address);
			break;
		}

		switch(u8MBFunction)
		{
		case WRITE_SINGLE_COIL:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_write_qty);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_write_qty);
			break;

		case WRITE_SINGLE_REGISTER:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_transmit_buffer[0]);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_transmit_buffer[0]);
		 	break;

		case WRITE_MULTIPLE_COILS:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_write_qty);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_write_qty);
			u8_mod0_Qty = (g_mod0_write_qty % 8) ? ((g_mod0_write_qty >> 3) + 1) : (g_mod0_write_qty >> 3);
			u8_mod0_ADU[u8_mod0_ADU_size++] = u8_mod0_Qty;
			for (mod0_i = 0; mod0_i < u8_mod0_Qty; mod0_i++)
			{
				switch(mod0_i % 2)
				{
					case 0: // mod0_i is even
						u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_transmit_buffer[mod0_i >> 1]);
						break;

					case 1: // mod0_i is odd
						u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_transmit_buffer[mod0_i >> 1]);
						break;
				}
			}
			break;

		case OUR_WRITE_MULTIPLE_COILS:
		case WRITE_MULTIPLE_REGISTERS:
		case READ_WRITE_MULTIPLE_REGISTERS:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_write_qty);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_write_qty);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_write_qty << 1);


		  for (mod0_i = 0; mod0_i < lowByte(g_mod0_write_qty); mod0_i++)
		  {
			  u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_transmit_buffer[mod0_i]);
			  u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_transmit_buffer[mod0_i]);
		  }
		  break;

		case MASK_WRITE_REGISTER:
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_transmit_buffer[0]);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_transmit_buffer[0]);
			u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(g_mod0_transmit_buffer[1]);
			u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(g_mod0_transmit_buffer[1]);
			break;
		}



		// append CRC
		u16_mod0_CRC = 0xFFFF;
		for (mod0_i = 0; mod0_i < u8_mod0_ADU_size; mod0_i++)
		{
			u16_mod0_CRC = crc16_update(u16_mod0_CRC, u8_mod0_ADU[mod0_i]);
		}
		u8_mod0_ADU[u8_mod0_ADU_size++] = lowByte(u16_mod0_CRC);
		u8_mod0_ADU[u8_mod0_ADU_size++] = highByte(u16_mod0_CRC);
		u8_mod0_ADU[u8_mod0_ADU_size] = 0;

		// flush receive buffer before transmitting request
		// mohab add

		while( g_mod0_Serial_getc() != UART_NO_DATA  );



		// transmit request
		if (g_mod0_pre_transmission)
		{
			g_mod0_pre_transmission();
		}



		for (mod0_i = 0; mod0_i < u8_mod0_ADU_size; mod0_i++)
		{
			g_mod0_Serial_putc(u8_mod0_ADU[mod0_i]);
		}

		u8_mod0_ADU_size = 0;
		g_mod0_Serial_flush();		   // flush transmit buffer
		_delay_us(100);
		if (g_mod0_post_transmission)
		{
			g_mod0_post_transmission();
		}

		// loop until we run out of time or bytes, or an error occurs
		/*_delay_ms(1000);*/
		u32_mod0_start_time = millis();

		while (u8_mod0_bytes_left && !u8MB_mod0_status)
		{

			if ( g_mod0_Serial_available() ) // _serial->available()
			{
				u8_mod0_ADU[u8_mod0_ADU_size++] = g_mod0_Serial_getc();
				u8_mod0_bytes_left--;
			}
			else
			{
				if (g_mod0_idle)
				{
					g_mod0_idle();
				}
			}

			// evaluate slave ID, function code once enough bytes have been read
			if (u8_mod0_ADU_size == 5)
			{
				// verify response is for correct Modbus slave
				if (u8_mod0_ADU[0] != g_mod0_slave)
				{
					u8MB_mod0_status = INVALID_SLAVE_ID;
					break;
				}

				// verify response is for correct Modbus function code (mask exception bit 7)
				if ((u8_mod0_ADU[1] & 0x7F) != u8MBFunction)
				{
					u8MB_mod0_status = INVALID_FUNCTION;
					break;
				}

				// check whether Modbus exception occurred; return Modbus Exception Code
				if (GET_BIT(u8_mod0_ADU[1], 7))
				{
					u8MB_mod0_status = u8_mod0_ADU[2];
					break;
				}

				// evaluate returned Modbus function codeprintdfdfdf
				switch(u8_mod0_ADU[1])
				{
				case READ_COILS:
				case READ_DISCRETE_INPUTS:
				case READ_INPUT_REGISTERS:
				case READ_HOLDING_REGISTERS:
				case READ_WRITE_MULTIPLE_REGISTERS:
					u8_mod0_bytes_left = u8_mod0_ADU[2];
					break;

				case WRITE_SINGLE_COIL:
				case WRITE_MULTIPLE_COILS:
				case WRITE_SINGLE_REGISTER:
				case WRITE_MULTIPLE_REGISTERS:
				case OUR_WRITE_MULTIPLE_COILS:
					u8_mod0_bytes_left = 3;
					break;

				case MASK_WRITE_REGISTER:
					u8_mod0_bytes_left = 5;
					break;
				}
			}
			if ((millis() - u32_mod0_start_time) > RESPONCE_TIME_OUT)
			{
 				UART0_puts("RESPONCE_TIMED_OUT\n");
 			
				u8MB_mod0_status = RESPONCE_TIMED_OUT;
			}

		}// end_of_while


		// verify response is large enough to inspect further
		if (!u8MB_mod0_status && u8_mod0_ADU_size >= 5)
		{

			u16_mod0_CRC = 0xFFFF;
			for (mod0_i = 0; mod0_i < (u8_mod0_ADU_size - 2); mod0_i++)
			{
			  u16_mod0_CRC = crc16_update(u16_mod0_CRC, u8_mod0_ADU[mod0_i]);
			}

			// verify CRC
			if (!u8MB_mod0_status && (lowByte(u16_mod0_CRC) != u8_mod0_ADU[u8_mod0_ADU_size - 2] ||
			  highByte(u16_mod0_CRC) != u8_mod0_ADU[u8_mod0_ADU_size - 1]))
			{
			  u8MB_mod0_status = INVALID_CRC;
			 
			}
		}

		// disassemble ADU into words'
		if (!u8MB_mod0_status)
		{
		// evaluate returned Modbus function code
			switch(u8_mod0_ADU[1])
			{
			  case READ_COILS:
			  case READ_DISCRETE_INPUTS:
				// load bytes into word; response bytes are ordered L, H, L, H, ...
				for (mod0_i = 0; mod0_i < (u8_mod0_ADU[2] >> 1); mod0_i++)
				{
				  if (mod0_i < MAX_BUFFER_SIZE)
				  {
						g_mod0_response_buffer[mod0_i] = MAKE_WORD(u8_mod0_ADU[2 * mod0_i + 4], u8_mod0_ADU[2 * mod0_i + 3]);
				  }

				  g_mod0_response_buffer_length = mod0_i;
				}

				// in the event of an odd number of bytes, load last byte into zero-padded word
				if (u8_mod0_ADU[2] % 2)
				{
				  if (mod0_i < MAX_BUFFER_SIZE)
				  {
					g_mod0_response_buffer[mod0_i] = MAKE_WORD(0, u8_mod0_ADU[2 * mod0_i + 3]);

				  }

				  g_mod0_response_buffer_length = mod0_i + 1;
				}
				break;

			  case READ_INPUT_REGISTERS:
			  case READ_HOLDING_REGISTERS:
			  case READ_WRITE_MULTIPLE_REGISTERS:
				// load bytes into word; response bytes are ordered H, L, H, L, ...
				for (mod0_i = 0; mod0_i < (u8_mod0_ADU[2] >> 1); mod0_i++)
				{
				  if (mod0_i < MAX_BUFFER_SIZE)
				  {
					 g_mod0_response_buffer[mod0_i] = MAKE_WORD(u8_mod0_ADU[2 * mod0_i + 3], u8_mod0_ADU[2 * mod0_i + 4]);
				  }

				  g_mod0_response_buffer_length = mod0_i;
				}
				break;
			}
		}

		g_mod0_transmit_buffer_index = 0;
		g_mod0_transmit_buffer_length = 0;
		g_mod0_response_buffer_index = 0;
		/*---------------------------------------------------------------------------------------------------*/
		return u8MB_mod0_status;



	}
	else if(DEVICE_1 == device){
		uint8_t u8_mod1_ADU[256];
		uint8_t u8_mod1_ADU_size = 0;
		uint8_t mod1_i, u8_mod1_Qty;
		uint16_t u16_mod1_CRC;
		uint32_t u32_mod1_start_time;
		uint8_t u8_mod1_bytes_left = 8;
		uint8_t u8MB_mod1_status = SUCCESS;

		/*------------------------------------------------------------------------------------------*/
		// assemble Mod bus Request Application Data Unit
		u8_mod1_ADU[u8_mod1_ADU_size++] = g_mod1_slave;
		if(u8MBFunction == 0xFF){
			u8_mod1_ADU[u8_mod1_ADU_size++] = 0x0F;
		}
		else{
			u8_mod1_ADU[u8_mod1_ADU_size++] = u8MBFunction;
		}


		switch(u8MBFunction)
		{
		case READ_COILS:
		case READ_DISCRETE_INPUTS:
		case READ_INPUT_REGISTERS:
		case READ_HOLDING_REGISTERS:
		case READ_WRITE_MULTIPLE_REGISTERS:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_read_address);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_read_address);
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_read_qty);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_read_qty);
			break;
		}

		switch(u8MBFunction)
		{
		case WRITE_SINGLE_COIL:
		case MASK_WRITE_REGISTER:
		case WRITE_MULTIPLE_COILS:
		case WRITE_SINGLE_REGISTER:
		case WRITE_MULTIPLE_REGISTERS:
		case READ_WRITE_MULTIPLE_REGISTERS:
		case OUR_WRITE_MULTIPLE_COILS:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_write_address);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_write_address);
			break;
		}

		switch(u8MBFunction)
		{
		case WRITE_SINGLE_COIL:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_write_qty);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_write_qty);
			break;

		case WRITE_SINGLE_REGISTER:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_transmit_buffer[0]);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_transmit_buffer[0]);
		 	break;

		case WRITE_MULTIPLE_COILS:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_write_qty);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_write_qty);
			u8_mod1_Qty = (g_mod1_write_qty % 8) ? ((g_mod1_write_qty >> 3) + 1) : (g_mod1_write_qty >> 3);
			u8_mod1_ADU[u8_mod1_ADU_size++] = u8_mod1_Qty;
			for (mod1_i = 0; mod1_i < u8_mod1_Qty; mod1_i++)
			{
				switch(mod1_i % 2)
				{
					case 0: // mod1_i is even
						u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_transmit_buffer[mod1_i >> 1]);
						break;

					case 1: // mod1_i is odd
						u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_transmit_buffer[mod1_i >> 1]);
						break;
				}
			}
			break;

		case OUR_WRITE_MULTIPLE_COILS:
		case WRITE_MULTIPLE_REGISTERS:
		case READ_WRITE_MULTIPLE_REGISTERS:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_write_qty);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_write_qty);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_write_qty << 1);

		  for (mod1_i = 0; mod1_i < lowByte(g_mod1_write_qty); mod1_i++)
		  {
			  u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_transmit_buffer[mod1_i]);
			  u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_transmit_buffer[mod1_i]);
		  }
		  break;

		case MASK_WRITE_REGISTER:
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_transmit_buffer[0]);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_transmit_buffer[0]);
			u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(g_mod1_transmit_buffer[1]);
			u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(g_mod1_transmit_buffer[1]);
			break;
		}

		// append CRC
		u16_mod1_CRC = 0xFFFF;
		for (mod1_i = 0; mod1_i < u8_mod1_ADU_size; mod1_i++)
		{
			u16_mod1_CRC = crc16_update(u16_mod1_CRC, u8_mod1_ADU[mod1_i]);
		}
		u8_mod1_ADU[u8_mod1_ADU_size++] = lowByte(u16_mod1_CRC);
		u8_mod1_ADU[u8_mod1_ADU_size++] = highByte(u16_mod1_CRC);
		u8_mod1_ADU[u8_mod1_ADU_size] = 0;

		// flush receive buffer before transmitting request
		//while (_serial->read() != -1);
		while( g_mod1_Serial_getc() != UART_NO_DATA  );


		// transmit request
		if (g_mod1_pre_transmission)
		{
			g_mod1_pre_transmission();
		}

		for (mod1_i = 0; mod1_i < u8_mod1_ADU_size; mod1_i++)
		{
			//_serial->write(u8_mod1_ADU[i]);
			g_mod1_Serial_putc(u8_mod1_ADU[mod1_i]);
		}


		u8_mod1_ADU_size = 0;
		//_serial->flush();    // flush transmit buffer
		g_mod1_Serial_flush();		   // flush transmit buffer
		_delay_us(450);
		if (g_mod1_post_transmission)
		{
			g_mod1_post_transmission();
		}

		// loop until we run out of time or bytes, or an error occurs
		u32_mod1_start_time = millis();
		while (u8_mod1_bytes_left && !u8MB_mod1_status)
		{
		if ( g_mod1_Serial_available() ) // _serial->available()
		{
		  u8_mod1_ADU[u8_mod1_ADU_size++] = g_mod1_Serial_getc();//_serial->read()
		  u8_mod1_bytes_left--;
		}
		else
		{

		  if (g_mod1_idle)
		  {
			  g_mod1_idle();
		  }

		}

		// evaluate slave ID, function code once enough bytes have been read
		if (u8_mod1_ADU_size == 5)
		{
		  // verify response is for correct Modbus slave
		  if (u8_mod1_ADU[0] != g_mod1_slave)
		  {
			u8MB_mod1_status = INVALID_SLAVE_ID;
			break;
		  }

		  // verify response is for correct Modbus function code (mask exception bit 7)
		  if ((u8_mod1_ADU[1] & 0x7F) != u8MBFunction)
		  {
			u8MB_mod1_status = INVALID_FUNCTION;
			break;
		  }

		  // check whether Modbus exception occurred; return Modbus Exception Code
		  if (GET_BIT(u8_mod1_ADU[1], 7))
		  {
// 			UART0_puts("Error = ");
// 			UART0_OutUDec(u8_mod1_ADU[2]);
// 			UART0_putc('\n');
			u8MB_mod1_status = u8_mod1_ADU[2];
			break;
		  }

		  // evaluate returned Modbus function code
		  switch(u8_mod1_ADU[1])
		  {
			case READ_COILS:
			case READ_DISCRETE_INPUTS:
			case READ_INPUT_REGISTERS:
			case READ_HOLDING_REGISTERS:
			case READ_WRITE_MULTIPLE_REGISTERS:
			  u8_mod1_bytes_left = u8_mod1_ADU[2];
			  break;

			case WRITE_SINGLE_COIL:
			case WRITE_MULTIPLE_COILS:
			case WRITE_SINGLE_REGISTER:
			case WRITE_MULTIPLE_REGISTERS:
			case OUR_WRITE_MULTIPLE_COILS:
			  u8_mod1_bytes_left = 3;
			  break;

			case MASK_WRITE_REGISTER:
			  u8_mod1_bytes_left = 5;
			  break;
		  }
		}
		if ((millis() - u32_mod1_start_time) > RESPONCE_TIME_OUT)
		{
		  u8MB_mod1_status = RESPONCE_TIMED_OUT;
		  UART0_puts("RESPONCE_TIMED_OUT\n");
		}
		}

		// verify response is large enough to inspect further
		if (!u8MB_mod1_status && u8_mod1_ADU_size >= 5)
		{
		// calculate CRC
		u16_mod1_CRC = 0xFFFF;
		for (mod1_i = 0; mod1_i < (u8_mod1_ADU_size - 2); mod1_i++)
		{
		  u16_mod1_CRC = crc16_update(u16_mod1_CRC, u8_mod1_ADU[mod1_i]);
		}

		// verify CRC
		if (!u8MB_mod1_status && (lowByte(u16_mod1_CRC) != u8_mod1_ADU[u8_mod1_ADU_size - 2] ||
		  highByte(u16_mod1_CRC) != u8_mod1_ADU[u8_mod1_ADU_size - 1]))
		{
		  u8MB_mod1_status = INVALID_CRC;
		}
		}

		// disassemble ADU into words
		if (!u8MB_mod1_status)
		{
		// evaluate returned Modbus function code
		switch(u8_mod1_ADU[1])
		{
		  case READ_COILS:
		  case READ_DISCRETE_INPUTS:
			// load bytes into word; response bytes are ordered L, H, L, H, ...
			for (mod1_i = 0; mod1_i < (u8_mod1_ADU[2] >> 1); mod1_i++)
			{
			  if (mod1_i < MAX_BUFFER_SIZE)
			  {
				g_mod1_response_buffer[mod1_i] = MAKE_WORD(u8_mod1_ADU[2 * mod1_i + 4], u8_mod1_ADU[2 * mod1_i + 3]);
			  }

			  g_mod1_response_buffer_length = mod1_i;
			}

			// in the event of an odd number of bytes, load last byte into zero-padded word
			if (u8_mod1_ADU[2] % 2)
			{
			  if (mod1_i < MAX_BUFFER_SIZE)
			  {
				g_mod1_response_buffer[mod1_i] = MAKE_WORD(0, u8_mod1_ADU[2 * mod1_i + 3]);
			  }

			  g_mod1_response_buffer_length = mod1_i + 1;
			}
			break;

		  case READ_INPUT_REGISTERS:
		  case READ_HOLDING_REGISTERS:
		  case READ_WRITE_MULTIPLE_REGISTERS:
			// load bytes into word; response bytes are ordered H, L, H, L, ...
			for (mod1_i = 0; mod1_i < (u8_mod1_ADU[2] >> 1); mod1_i++)
			{
			  if (mod1_i < MAX_BUFFER_SIZE)
			  {
				g_mod1_response_buffer[mod1_i] = MAKE_WORD(u8_mod1_ADU[2 * mod1_i + 3], u8_mod1_ADU[2 * mod1_i + 4]);
			  }

			  g_mod1_response_buffer_length = mod1_i;
			}
			break;
		}
		}

		g_mod1_transmit_buffer_index = 0;
		g_mod1_transmit_buffer_length = 0;
		g_mod1_response_buffer_index = 0;
		/*---------------------------------------------------------------------------------------------------*/
		return u8MB_mod1_status;

	}
	return INVALID_DEVICE; //error



}







