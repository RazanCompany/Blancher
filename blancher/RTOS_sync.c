/*
 * RTOS_sync.c
 *
 * Created: 07/10/2018 03:04:59 م
 *  Author: ENG
 */ 


#include "RTOS_sync.h"


SemaphoreHandle_t LCD_mutex_handle;
static StaticSemaphore_t LCD_mutex_Buffer;

SemaphoreHandle_t level_monitor_semaphore_handle;
static StaticSemaphore_t level_monitor_semaphore_buffer;

SemaphoreHandle_t temperature_monitor_semaphore_handle;
static StaticSemaphore_t temperature_monitor_semaphore_buffer;

SemaphoreHandle_t Blancher_ready_semaphore_handle;
static StaticSemaphore_t Blancher_ready_semaphore_buffer;

SemaphoreHandle_t System_on_temp_main_start_handle;
static StaticSemaphore_t System_on_temp_main_start_buffer;

// SemaphoreHandle_t System_on_level_main_start_handle;
// static StaticSemaphore_t System_on_level_main_start_buffer;

SemaphoreHandle_t System_off_temp_main_start_handle;
static StaticSemaphore_t System_off_temp_main_start_buffer;

SemaphoreHandle_t System_off_level_main_start_handle;
static StaticSemaphore_t System_off_level_main_start_buffer;

SemaphoreHandle_t Sequence_main_start_handle;
static StaticSemaphore_t Sequence_main_start_buffer;


void RTOS_sync_init(void)
{
    LCD_mutex_handle = xSemaphoreCreateBinaryStatic( &LCD_mutex_Buffer );
	xSemaphoreGive(LCD_mutex_handle);
	
	level_monitor_semaphore_handle = xSemaphoreCreateBinaryStatic( &level_monitor_semaphore_buffer );
	temperature_monitor_semaphore_handle = xSemaphoreCreateBinaryStatic( &temperature_monitor_semaphore_buffer );
	Blancher_ready_semaphore_handle = xSemaphoreCreateBinaryStatic( &Blancher_ready_semaphore_buffer );
	System_on_temp_main_start_handle = xSemaphoreCreateBinaryStatic( &System_on_temp_main_start_buffer );
//	System_on_level_main_start_handle = xSemaphoreCreateBinaryStatic( &System_on_level_main_start_buffer );
	System_off_temp_main_start_handle = xSemaphoreCreateBinaryStatic( &System_off_temp_main_start_buffer );
	System_off_level_main_start_handle =  xSemaphoreCreateBinaryStatic( &System_off_level_main_start_buffer );
	Sequence_main_start_handle = xSemaphoreCreateBinaryStatic( &Sequence_main_start_buffer );
}