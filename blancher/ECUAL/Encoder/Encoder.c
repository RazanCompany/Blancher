/*
 *õ  Encoderõ.c
 *
 *  Created: 14/8/2018 1:56:34 PM
 *  Author: M.Nagah
 *  this file used to init timer in CTC mode to get time between Ticks using ISR
 *
 */

#include "Encoder.h"
#include <avr/interrupt.h>
#include "../../MCAL/UART.h"

/*
 * Encoder_Task.c
 *
 * Created: 9/20/2018 3:08:33 AM
 *  Author: M.Nagah
 */

#include "Encoder.h"
#include "../../MCAL/Timer.h"

g_Timer_Config  Encoder_1_confg;

/*
 * set_up the Drum config 
 * parameters@ Nothing
 * return@ Nothing
 */

void Encoder_init(void (*pISR_callback)(uint32_t),uint8_t timer_number,uint16_t ticks_number )
{
	//encoder of Drum on timer 5
	Encoder_1_confg.timer_number = timer_number;
	// number of ticks 16 to interrupted
	Encoder_1_confg.ticks = ticks_number;
	//Call back Function 
	Encoder_1_confg.isr_call_back = pISR_callback ; 
    timers_init(&Encoder_1_confg);
}



