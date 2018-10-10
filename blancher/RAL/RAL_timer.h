/*
 * Encoder_RAL.h
 * This register abstraction layer for Timer 1,2,3,4,5 for ATmega 2560
 * Timer 2 is not defined as external counter it isn't have a Externel pin counter
 *  Created on: Aug 14, 2018
 *      Author: M.nagah
 */

#include <avr/io.h>



#ifndef RAL_TIMER_H_
#define RAL_TIMER_H_
/******************Timer1 config Register ***************************************/

#define TIMER1_PIN              PD6
#define TIMER1_CONGFIG_A		TCCR1A
#define TIMER1_CONGFIG_B		TCCR1B
#define TIMER1_COUNT		    TCNT1
#define TIMER1_COUNT_L		    TCNT1L
#define TIMER1_COUNT_H		    TCNT1H
#define TIMER1_COMPARE		    OCR1A
#define TIMER1_INTERUPT		    TIMSK1
#define TIMER1_COMPARE_INT		OCIE1A

/*********************************************************************************/
/******************Timer1 config Register ***************************************/


#define TIMER2_CONGFIG_A		TCCR2A
#define TIMER2_CONGFIG_B		TCCR2B
#define TIMER2_COUNT		    TCNT2
#define TIMER2_COUNT_L		    TCNT2L
#define TIMER2_COUNT_H		    TCNT2H
#define TIMER2_COMPARE		    OCR2A
#define TIMER2_INTERUPT		    TIMSK2
#define TIMER2_COMPARE_INT		OCIE2A

/*********************************************************************************/

/******************Timer3 config Register ****************************************/

#define TIMER3_PIN              PE6
#define TIMER3_CONGFIG_A		TCCR3A
#define TIMER3_CONGFIG_B		TCCR3B
#define TIMER3_COUNT		    TCNT3
#define TIMER3_COUNT_L		    TCNT3L
#define TIMER3_COUNT_H		    TCNT3H
#define TIMER3_COMPARE		    OCR3A
#define TIMER3_INTERUPT		    TIMSK3
#define TIMER3_COMPARE_INT		OCIE3A

/*********************************************************************************/
/******************Timer4 config Register ****************************************/

#define TIMER4_PIN              PH7
#define TIMER4_CONGFIG_A		TCCR4A
#define TIMER4_CONGFIG_B		TCCR4B
#define TIMER4_COUNT		    TCNT4
#define TIMER4_COUNT_L		    TCNT4L
#define TIMER4_COUNT_H		    TCNT4H
#define TIMER4_COMPARE		    OCR4A
#define TIMER4_INTERUPT		    TIMSK4
#define TIMER4_COMPARE_INT		OCIE4A

/*********************************************************************************/
/******************Timer5 config Register ****************************************/

#define TIMER5_PIN              PL2
#define TIMER5_CONGFIG_A		TCCR5A
#define TIMER5_CONGFIG_B		TCCR5B
#define TIMER5_COUNT		    TCNT5
#define TIMER5_COUNT_L		    TCNT5L
#define TIMER5_COUNT_H		    TCNT5H
#define TIMER5_COMPARE		    OCR5A
#define TIMER5_INTERUPT		    TIMSK5
#define TIMER5_COMPARE_INT		OCIE5A



#endif /* _RAL_TIMER_H_ */
