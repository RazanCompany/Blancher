/*
 * ADC.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ENG
 */
#define F_CPU 16000000
#include "ADC.h"
#include "../RAL/RAL.h"
#include "../RAL/HW_types.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"


 volatile uint16_t  g_analog_data = 0;
 char g_converted = 0 ;


void ADC_init(uint8_t channel)
{
	/*
	 * this function configure ADC module and
	 * you  pass the channel you work with from 0 to 7
	 */

   // make the ADC pin as input.
  CLR_BIT(ADC_DIRECTION_REG ,channel );
  //   external ref .
  CLR_HIGH_NIBBLE(ADC_MULTIPLEXER_SELECTION_REG);
  //   operated channel ( channel ) .
  PUT_VAL_LOW_NIBBLE(ADC_MULTIPLEXER_SELECTION_REG , channel);
  //  enable ADC  & enable interrupt && ps / 128.
  PUT_VAL_reg(ADC_CONTROL_STATUS_A_REG , 0x8f);

  // enable global interrupt.
  sei();


}

void ADC_enable_reading(void)
{
	// restart the conversion .
	SET_BIT(ADC_CONTROL_STATUS_A_REG , ADC_START_CONVERSION_bit);
}

uint16_t ADC_read(void)
{
	// re-start the conversion .
	ADC_enable_reading();
	static uint16_t returned_data;
	g_converted = 0 ;
	// the conversion takes about 260 us so we will wait 4800 ticks till it ends .
	uint16_t time_out = 4800 ;
	while(!g_converted && 0 != time_out ){time_out --; }
	returned_data = g_analog_data ;
	return returned_data ;
}


ISR(ADC_vect)
{
	   uint8_t The_low_adc_reg = ADC_DATA_REG_LOW ;
	  // get 10 bits out of the high and low register .
	  g_analog_data =  The_low_adc_reg | (ADC_DATA_REG_HIGH <<8);
	  UART0_OutUDec(g_analog_data);
	  g_converted = 1 ;
}








