#ifndef FLOW_RATE_H_
#define FLOW_RATE_H

#include <inttypes.h>
/*
* this function will initialize the timer with the right config .
* it takes the callbacks functions  .
*/
void Flow_rate_init(void (*callback1)() , void (*callback2)()) ;


#endif /* FLOW_RATE_H_ */