#ifndef FLOW_RATE_H_
#define FLOW_RATE_H

#include <inttypes.h>
/*
* this function will initialize the timer with the right config .
* it takes the timer number .
*/
void Flow_rate_init(uint8_t timer_num);

/*
*	this function takes the amount of liters you want to pass to the tank .
*   returns 1 if this process is done , -1 if not . 
*/
uint8_t Tank_feed (float liters) ;

/*
*	this function is called back from the isr to increment the liters counter .
*/
void Liters_count (uint32_t time);




#endif /* FLOW_RATE_H_ */