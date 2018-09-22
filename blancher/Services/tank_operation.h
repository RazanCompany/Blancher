/*
 * tank_operation.h
 *
 * Created: 20/09/2018 02:45:48 م
 *  Author: ENG
 */ 


#ifndef TANK_OPERATION_H_
#define TANK_OPERATION_H_
#include <inttypes.h>

void Tank_operation_init();

/*
*	this function takes the amount of liters you want to pass to the tank .
*  
*/
void Tank_feed_operation(uint16_t liters);
/*
*	this function let the water goes out from the tank .
*/
void Tank_out_operation(uint16_t liters);






#endif /* TANK_OPERATION_H_ */