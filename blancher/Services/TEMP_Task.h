/*
 * TEMP_Task.h
 *
 * Created: 9/22/2018 4:24:51 PM
 *  Author: M.nagah
 */ 


#ifndef TEMP_TASK_H_
#define TEMP_TASK_H_


#define TEMP_OVER_TEMP					50
#define TEMP_OVER_TEMP_STILL_TIME		6

void Temp_main_err_init( void(*callback_over_temp)(void) );
void Temp_main(void* pvParameters);




#endif /* TEMP_TASK_H_ */