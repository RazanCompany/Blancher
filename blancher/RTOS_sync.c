/*
 * RTOS_sync.c
 *
 * Created: 07/10/2018 03:04:59 م
 *  Author: ENG
 */ 


#include "RTOS_sync.h"


SemaphoreHandle_t LCD_mutex_handle;
static StaticSemaphore_t LCD_mutex_Buffer;



void RTOS_sync_init(void)
{
   // LCD_mutex_handle = xSemaphoreCreateBinaryStatic( &LCD_mutex_Buffer );
}