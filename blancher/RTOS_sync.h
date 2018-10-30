/*
 * RTOS_sync.h
 *
 * Created: 07/10/2018 03:05:16 م
 *  Author: ENG
 */ 


#ifndef RTOS_SYNC_H_
#define RTOS_SYNC_H_


#include "RTOS_Includes.h"

extern SemaphoreHandle_t LCD_mutex_handle;
 
extern SemaphoreHandle_t level_monitor_semaphore_handle;
extern SemaphoreHandle_t temperature_monitor_semaphore_handle;
extern SemaphoreHandle_t Blancher_ready_semaphore_handle;
extern SemaphoreHandle_t System_on_temp_main_start_handle;
//extern SemaphoreHandle_t System_on_level_main_start_handle;
extern SemaphoreHandle_t System_off_temp_main_start_handle;
extern SemaphoreHandle_t System_off_level_main_start_handle;
extern SemaphoreHandle_t Sequence_main_start_handle;

void RTOS_sync_init(void);



#endif /* RTOS_SYNC_H_ */