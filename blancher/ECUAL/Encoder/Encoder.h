
#ifndef ENCODER_H_
#define ENCODER_H


#include <avr/interrupt.h>
#include "../../RAL/HW_types.h"
#include "../../RAL/RAL_timer.h"
#include "../../utils/Millis.h"
#include <util/delay.h>


/**********************8Declaration*******************************************/
//Timer  configration parameters that contain the Ticks number and call back ISR function and timer number
// each timer must have call this struct from upper Layer
typedef struct configration
{
	int ticks;                      // number of ticks of Encoder Slots
	void (*isr_call_back)(uint32_t ); // time_between_ticks this call back function on ISR
	char timer_number;              // timer Number select
}g_Timer_Config;

/*****************************************************************************/



/*********************PROTO TYPES****************************************/
//init the Encoder timer parameters
uint8_t timers_init(g_Timer_Config *config);
/***********************************************************************/




#endif /* ENCODER_H_ */
