#ifndef UART_H
#define UART_H

/************************************************************************
Title:    Interrupt UART library with receive/transmit circular buffers
Author:   Andy Gock
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: any AVR with built-in UART, tested on AT90S8515 & ATmega8 at 4 Mhz
License:  GNU General Public License 
Usage:    see README.md and Doxygen manual

Based on original library by Peter Fluery, Tim Sharpe, Nicholas Zambetti.

https://github.com/andygock/avr-UART

LICENSE:

	Copyright (C) 2012 Andy Gock
	Copyright (C) 2006 Peter Fleury

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

************************************************************************/

/************************************************************************
UART_available, UART_flush, UART1_available, and UART1_flush functions
were adapted from the Arduino HardwareSerial.h library by Tim Sharpe on 
11 Jan 2009.  The license info for HardwareSerial.h is as follows:

  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
************************************************************************/

/** 
 *  @defgroup avr-UART UART Library
 *  @code #include <UART.h> @endcode
 * 
 *  @brief Interrupt UART library using the built-in UART with transmit and receive circular buffers.
 *  @see README.md
 *
 *  This library can be used to transmit and receive data through the built in UART. 
 *
 *  An interrupt is generated when the UART has finished transmitting or
 *  receiving a byte. The interrupt handling routines use circular buffers
 *  for buffering received and transmitted data.
 *
 *  The UART_RXn_BUFFER_SIZE and UART_TXn_BUFFER_SIZE constants define
 *  the size of the circular buffers in bytes. Note that these constants must be a power of 2.
 *
 *  You need to define these buffer sizes as a symbol in your compiler settings or in UART.h
 *
 *  See README.md for more detailed information. Especially that relating to symbols: USARTn_ENABLED and USARTn_LARGE_BUFFER
 *
 *  @author Andy Gock <andy@gock.net>
 *  @note Based on Atmel Application Note AVR306 and original library by Peter Fleury and Tim Sharpe.
 */
 
/**@{*/
#include <stdint.h>
#include <avr/io.h>

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*
 * constants and macros
 */

/* Enable USART 1, 2, 3 as required */
/* Can be defined in compiler symbol setup with -D option (preferred) */
#ifndef USART0_ENABLED
	#define USART0_ENABLED /**< Enable USART0 */
#endif
#define USART1_ENABLED
#define USART2_ENABLED
//#define USART3_ENABLED

/* Set size of receive and transmit buffers */

#ifndef UART_RX0_BUFFER_SIZE
	#define UART_RX0_BUFFER_SIZE 128 /**< Size of the circular receive buffer, must be power of 2 */
#endif
#ifndef UART_RX1_BUFFER_SIZE
	#define UART_RX1_BUFFER_SIZE 128 /**< Size of the circular receive buffer, must be power of 2 */
#endif
#ifndef UART_RX2_BUFFER_SIZE
	#define UART_RX2_BUFFER_SIZE 128 /**< Size of the circular receive buffer, must be power of 2 */
#endif
#ifndef UART_RX3_BUFFER_SIZE
	#define UART_RX3_BUFFER_SIZE 128 /**< Size of the circular receive buffer, must be power of 2 */
#endif

#ifndef UART_TX0_BUFFER_SIZE
	#define UART_TX0_BUFFER_SIZE 128 /**< Size of the circular transmit buffer, must be power of 2 */
#endif
#ifndef UART_TX1_BUFFER_SIZE
	#define UART_TX1_BUFFER_SIZE 128 /**< Size of the circular transmit buffer, must be power of 2 */
#endif
#ifndef UART_TX2_BUFFER_SIZE
	#define UART_TX2_BUFFER_SIZE 128 /**< Size of the circular transmit buffer, must be power of 2 */
#endif
#ifndef UART_TX3_BUFFER_SIZE
	#define UART_TX3_BUFFER_SIZE 128 /**< Size of the circular transmit buffer, must be power of 2 */
#endif

/* Check buffer sizes are not too large for 8-bit positioning */

#if (UART_RX0_BUFFER_SIZE > 256 & !defined(USART0_LARGE_BUFFER))
	#error "Buffer too large, please use -DUSART0_LARGE_BUFFER switch in compiler options"
#endif

#if (UART_RX1_BUFFER_SIZE > 256 & !defined(USART1_LARGE_BUFFER))
	#error "Buffer too large, please use -DUSART1_LARGE_BUFFER switch in compiler options"
#endif

#if (UART_RX2_BUFFER_SIZE > 256 & !defined(USART2_LARGE_BUFFER))
	#error "Buffer too large, please use -DUSART2_LARGE_BUFFER switch in compiler options"
#endif

#if (UART_RX3_BUFFER_SIZE > 256 & !defined(USART3_LARGE_BUFFER))
	#error "Buffer too large, please use -DUSART3_LARGE_BUFFER switch in compiler options"
#endif

/* Check buffer sizes are not too large for *_LARGE_BUFFER operation (16-bit positioning) */

#if (UART_RX0_BUFFER_SIZE > 32768)
	#error "Buffer too large, maximum allowed is 32768 bytes"
#endif

#if (UART_RX1_BUFFER_SIZE > 32768)
	#error "Buffer too large, maximum allowed is 32768 bytes"
#endif

#if (UART_RX2_BUFFER_SIZE > 32768)
	#error "Buffer too large, maximum allowed is 32768 bytes"
#endif

#if (UART_RX3_BUFFER_SIZE > 32768)
	#error "Buffer too large, maximum allowed is 32768 bytes"
#endif

/** @brief  UART Baudrate Expression
 *  @param  xtalCpu  system clock in Mhz, e.g. 4000000L for 4Mhz          
 *  @param  baudRate baudrate in bps, e.g. 1200, 2400, 9600     
 */
#define UART_BAUD_SELECT(baudRate,xtalCpu) (((xtalCpu)+8UL*(baudRate))/(16UL*(baudRate))-1UL)

/** @brief  UART Baudrate Expression for ATmega double speed mode
 *  @param  xtalCpu  system clock in Mhz, e.g. 4000000L for 4Mhz           
 *  @param  baudRate baudrate in bps, e.g. 1200, 2400, 9600     
 */
#define UART_BAUD_SELECT_DOUBLE_SPEED(baudRate,xtalCpu) ((((xtalCpu)+4UL*(baudRate))/(8UL*(baudRate))-1)|0x8000)

/* test if the size of the circular buffers fits into SRAM */

#if defined(USART0_ENABLED) && ( (UART_RX0_BUFFER_SIZE+UART_TX0_BUFFER_SIZE) >= (RAMEND-0x60))
	#error "size of UART_RX0_BUFFER_SIZE + UART_TX0_BUFFER_SIZE larger than size of SRAM"
#endif

#if defined(USART1_ENABLED) && ( (UART_RX1_BUFFER_SIZE+UART_TX1_BUFFER_SIZE) >= (RAMEND-0x60))
	#error "size of UART_RX1_BUFFER_SIZE + UART_TX1_BUFFER_SIZE larger than size of SRAM"
#endif

#if defined(USART2_ENABLED) && ( (UART_RX2_BUFFER_SIZE+UART_RX2_BUFFER_SIZE) >= (RAMEND-0x60))
	#error "size of UART_RX2_BUFFER_SIZE + UART_TX2_BUFFER_SIZE larger than size of SRAM"
#endif

#if defined(USART3_ENABLED) && ( (UART_RX3_BUFFER_SIZE+UART_RX3_BUFFER_SIZE) >= (RAMEND-0x60))
	#error "size of UART_RX3_BUFFER_SIZE + UART_TX3_BUFFER_SIZE larger than size of SRAM"
#endif

/* 
** high byte error return code of UART_getc()
*/
#define UART_FRAME_ERROR      0x0800              /**< Framing Error by UART       */
#define UART_OVERRUN_ERROR    0x0400              /**< Overrun condition by UART   */
#define UART_BUFFER_OVERFLOW  0x0200              /**< receive ringbuffer overflow */
#define UART_NO_DATA          0x0100              /**< no receive data available   */

/* Macros, to allow use of legacy names */

/** @brief Macro to initialize USART0 (only available on selected ATmegas) @see UART0_init */
#define UART_init(b)      UART0_init(b)

/** @brief Macro to get received byte of USART0 from ringbuffer. (only available on selected ATmega) @see UART0_getc */
#define UART_getc()       UART0_getc()

/** @brief Macro to peek at next byte in USART0 ringbuffer */
#define UART_peek()       UART0_peek()

/** @brief Macro to put byte to ringbuffer for transmitting via USART0 (only available on selected ATmega) @see UART0_putc */
#define UART_putc(d)      UART0_putc(d)

/** @brief Macro to put string to ringbuffer for transmitting via USART0 (only available on selected ATmega) @see UART0_puts */
#define UART_puts(s)      UART0_puts(s)

/** @brief Macro to put string from program memory to ringbuffer for transmitting via USART0 (only available on selected ATmega) @see UART0_puts_p */
#define UART_puts_p(s)    UART0_puts_p(s)

/** @brief Macro to return number of bytes waiting in the receive buffer of USART0 @see UART0_available */
#define UART_available()  UART0_available()

/** @brief Macro to flush bytes waiting in receive buffer of USART0 @see UART0_flush */
#define UART_flush()      UART0_flush()

/*
** function prototypes
*/

/**
   @brief   Initialize UART and set baudrate 
   @param   baudrate Specify baudrate using macro UART_BAUD_SELECT()
   @return  none
*/
typedef enum UART_M{
	UART0=0,
	UART1,
	UART2
}UART_Modules;


/*
 * UART_Init : this function initialize UART modules
 * @param: UART_module - the number of the UART module
 * 		   baudrate  - the baudrate required to initialze the UART module
 *
 * @retrun : void
 * @todo : testing
 * @bug : ......
 */

void UART_Init(UART_Modules UART_module, uint32_t baudrate); //new

extern void UART0_init(uint32_t baudrate);



void UART0_OutUDec(uint32_t n);

/**
 *  @brief   Get received byte from ringbuffer
 *
 * Returns in the lower byte the received character and in the 
 * higher byte the last receive error.
 * UART_NO_DATA is returned when no data is available.
 *
 *  @return  lower byte:  received byte from ringbuffer
 *  @return  higher byte: last receive status
 *           - \b 0 successfully received data from UART
 *           - \b UART_NO_DATA           
 *             <br>no receive data available
 *           - \b UART_BUFFER_OVERFLOW   
 *             <br>Receive ringbuffer overflow.
 *             We are not reading the receive buffer fast enough, 
 *             one or more received character have been dropped 
 *           - \b UART_OVERRUN_ERROR     
 *             <br>Overrun condition by UART.
 *             A character already present in the UART UDR register was 
 *             not read by the interrupt handler before the next character arrived,
 *             one or more received characters have been dropped.
 *           - \b UART_FRAME_ERROR       
 *             <br>Framing Error by UART
 */
extern uint16_t UART0_getc(void);

/**
 *  @brief   Peek at next byte in ringbuffer
 *
 * Returns the next byte (character) of incoming UART data without removing it from the
 * internal ring buffer. That is, successive calls to UARTN_peek() will return the same
 * character, as will the next call to UARTN_getc().
 *
 * UART_NO_DATA is returned when no data is available.
 *
 *  @return  lower byte:  next byte in ringbuffer
 *  @return  higher byte: last receive status
 *           - \b 0 successfully received data from UART
 *           - \b UART_NO_DATA           
 *             <br>no receive data available
 *           - \b UART_BUFFER_OVERFLOW   
 *             <br>Receive ringbuffer overflow.
 *             We are not reading the receive buffer fast enough, 
 *             one or more received character have been dropped 
 *           - \b UART_OVERRUN_ERROR     
 *             <br>Overrun condition by UART.
 *             A character already present in the UART UDR register was 
 *             not read by the interrupt handler before the next character arrived,
 *             one or more received characters have been dropped.
 *           - \b UART_FRAME_ERROR       
 *             <br>Framing Error by UART
 */
extern uint16_t UART0_peek(void);

/**
 *  @brief   Put byte to ringbuffer for transmitting via UART
 *  @param   data byte to be transmitted
 *  @return  none
 */
extern void UART0_putc(uint8_t data);


/**
 *  @brief   Put string to ringbuffer for transmitting via UART
 *
 *  The string is buffered by the UART library in a circular buffer
 *  and one character at a time is transmitted to the UART using interrupts.
 *  Blocks if it can not write the whole string into the circular buffer.
 * 
 *  @param   s string to be transmitted
 *  @return  none
 */
extern void UART0_puts(const char *s);


/**
 * @brief    Put string from program memory to ringbuffer for transmitting via UART.
 *
 * The string is buffered by the UART library in a circular buffer
 * and one character at a time is transmitted to the UART using interrupts.
 * Blocks if it can not write the whole string into the circular buffer.
 *
 * @param    s program memory string to be transmitted
 * @return   none
 * @see      UART0_puts_P
 */
extern void UART0_puts_p(const char *s);

/**
 * @brief    Macro to automatically put a string constant into program memory
 * \param    __s string in program memory
 */
#define UART_puts_P(__s)       UART0_puts_p(PSTR(__s))

/** @brief  Macro to automatically put a string constant into program memory */
#define UART0_puts_P(__s)      UART0_puts_p(PSTR(__s))

/**
 *  @brief   Return number of bytes waiting in the receive buffer
 *  @return  bytes waiting in the receive buffer
 */
extern uint16_t UART0_available(void);

/**
 *  @brief   Flush bytes waiting in receive buffer
 */
extern void UART0_flush(void);


/** @brief  Initialize USART1 (only available on selected ATmegas) @see UART_init */
extern void UART1_init(uint32_t baudrate);


void UART1_OutUDec(uint32_t n);
/** @brief  Get received byte of USART1 from ringbuffer. (only available on selected ATmega) @see UART_getc */
extern uint16_t UART1_getc(void);

/** @brief  Peek at next byte in USART1 ringbuffer */
extern uint16_t UART1_peek(void);

/** @brief  Put byte to ringbuffer for transmitting via USART1 (only available on selected ATmega) @see UART_putc */
extern void UART1_putc(uint8_t data);

/** @brief  Put string to ringbuffer for transmitting via USART1 (only available on selected ATmega) @see UART_puts */
extern void UART1_puts(const char *s);

/** @brief  Put string from program memory to ringbuffer for transmitting via USART1 (only available on selected ATmega) @see UART_puts_p */
extern void UART1_puts_p(const char *s);

/** @brief  Macro to automatically put a string constant into program memory of USART1 @see UART1_puts_p */
#define UART1_puts_P(__s)       UART1_puts_p(PSTR(__s))

/** @brief  Return number of bytes waiting in the receive buffer of USART1 */
extern uint16_t UART1_available(void);

/** @brief  Flush bytes waiting in receive buffer of USART1 */
extern void UART1_flush(void);


/** @brief  Initialize USART2 (only available on selected ATmegas) @see UART_init */
extern void UART2_init(uint32_t baudrate);

void UART2_OutUDec(uint32_t n);
/** @brief  Get received byte of USART2 from ringbuffer. (only available on selected ATmega) @see UART_getc */
extern uint16_t UART2_getc(void);

/** @brief  Peek at next byte in USART2 ringbuffer */
extern uint16_t UART2_peek(void);

/** @brief  Put byte to ringbuffer for transmitting via USART2 (only available on selected ATmega) @see UART_putc */
extern void UART2_putc(uint8_t data);

/** @brief  Put string to ringbuffer for transmitting via USART2 (only available on selected ATmega) @see UART_puts */
extern void UART2_puts(const char *s);

/** @brief  Put string from program memory to ringbuffer for transmitting via USART2 (only available on selected ATmega) @see UART_puts_p */
extern void UART2_puts_p(const char *s);

/** @brief  Macro to automatically put a string constant into program memory of USART2 @see UART2_puts_p */
#define UART2_puts_P(__s)       UART2_puts_p(PSTR(__s))

/** @brief  Return number of bytes waiting in the receive buffer of USART2 */
extern uint16_t UART2_available(void);

/** @brief  Flush bytes waiting in receive buffer of USART2 */
extern void UART2_flush(void);


/** @brief  Initialize USART3 (only available on selected ATmegas) @see UART_init */
extern void UART3_init(uint32_t baudrate);

void UART3_OutUDec(uint32_t n);
/** @brief  Get received byte of USART3 from ringbuffer. (only available on selected ATmega) @see UART_getc */
extern uint16_t UART3_getc(void);

/** @brief  Peek at next byte in USART3 ringbuffer */
extern uint16_t UART3_peek(void);

/** @brief  Put byte to ringbuffer for transmitting via USART3 (only available on selected ATmega) @see UART_putc */
extern void UART3_putc(uint8_t data);

/** @brief  Put string to ringbuffer for transmitting via USART3 (only available on selected ATmega) @see UART_puts */
extern void UART3_puts(const char *s);

/** @brief  Put string from program memory to ringbuffer for transmitting via USART3 (only available on selected ATmega) @see UART_puts_p */
extern void UART3_puts_p(const char *s);

/** @brief  Macro to automatically put a string constant into program memory of USART3 @see UART3_puts_p */
#define UART3_puts_P(__s)       UART3_puts_p(PSTR(__s))

/** @brief  Return number of bytes waiting in the receive buffer of USART3 */
extern uint16_t UART3_available(void);

/** @brief  Flush bytes waiting in receive buffer of USART3 */
extern void UART3_flush(void);

/**@}*/

#endif // UART_H 

