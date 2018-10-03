/*
 * Encoder_Task.H
 *
 * Created: 9/20/2018 3:08:33 AM
 *  Author: M.Nagah
 */ 
#ifndef DRUM_SPEED_TASK_H_
#define DRUM_SPEED_TASK_H_
#include <stdint.h>
/*
 * set_up the Drum config 
 * parameters@ Nothing
 * return@ Nothing
 */
void Drum_speed_Tasks_init(void);


void Drum_speed_periodic_task(void);


#endif /* DRUM_SPEED_TASK_H_ */