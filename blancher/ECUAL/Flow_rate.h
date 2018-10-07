#ifndef FLOW_RATE_H_
#define FLOW_RATE_H

#include <stdint.h>
/*
* this function will initialize the timer with the right config .
* it takes the callbacks functions  .
*/
void Flow_rate_init(uint8_t flowrate1_timer_number,uint8_t flowrate2_timer_number,void (*callback1)(void) , void (*callback2)(void)) ;


#endif /* FLOW_RATE_H_ */