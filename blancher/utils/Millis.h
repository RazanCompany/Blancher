/*
 * Millis.h
 * time from The MC start
 *  Created on: Aug 14, 2018
 *      Author: M.nagah
 */
#ifndef MILLIS_H_
#define MILLIS_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "../RAL/RAL_timer.h"
#include "../RAL/HW_types.h"
// 16MHz Clock
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// Calculate the value needed for
// the CTC match value in OCR1A.
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 64)





//init the timer on ctc mode to calvulate millis
void millis_init();

//return the millis sec
unsigned long Get_millis();









#endif /* MILLIS_H_ */
