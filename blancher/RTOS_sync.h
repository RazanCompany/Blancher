/*
 * RTOS_sync.h
 *
 * Created: 07/10/2018 03:05:16 م
 *  Author: ENG
 */ 


#ifndef RTOS_SYNC_H_
#define RTOS_SYNC_H_


#include "RTOS_Includes.h"

extern SemaphoreHandle_t LCD_mutex_handle ; 

void RTOS_sync_init(void);



#endif /* RTOS_SYNC_H_ */