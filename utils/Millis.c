/*
 *õ  Millisõ.c
 *
 *  Created: 15/8/2018 1:56:34 PM
 *  Author: M.Nagah
 *  this file used to get time from the MC start by MilSEC
 */

#include "Millis.h"
//interrupt counter miilis time
volatile unsigned long timer1_millis;

//init the timer on ctc mode to calvulate millis
void millis_init()
{
	//CTC mode
	TIMER2_CONGFIG_A = 0x02;
	// Clock/64
	TIMER2_CONGFIG_B = 0x04;
    // Load into the output compare
    TIMER2_COMPARE = CTC_MATCH_OVERFLOW;
    // Enable the compare match interrupt
    SET_BIT(TIMER2_INTERUPT, TIMER2_COMPARE_INT);

}//millis_init


/*
 * Get The Time From the MC start
 * return the millis sec
 *
 */
unsigned long Get_millis()
{
	//return the millis time
    unsigned long millis_return;

    // Ensure this cannot be disrupted
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
    	// copy the ISR counter
        millis_return = timer1_millis;
    }

    return millis_return;
}//Get_millis



ISR (TIMER2_COMPA_vect)
{
	//MILLI SEC
    timer1_millis++;
}//ISR
