/*
 * Level_Task.h
 *
 * Created: 26/09/2018 01:00:35 م
 *  Author: ENG
 */ 


#ifndef LEVEL_TASK_H_
#define LEVEL_TASK_H_
#include <inttypes.h>


 void Level_main_err_init( void (*callback_level_sensor_fail) (void) );
void Level_main(void* pvParameters );


#endif /* LEVEL_TASK_H_ */