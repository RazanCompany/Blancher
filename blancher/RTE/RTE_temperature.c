/*
 * RTE_temperature.c
 *
 * Created: 9/20/2018 3:09:34 AM
 *  Author: Mohab Adel
 */ 
// sleep temp r
// set temp r
// set temp threshold r
// sleep temp threshold r   
// offset+ r
// offset- r
// current temp w
#include "../RTOS_Includes.h"
#include "RTE_temperature.h"

static SemaphoreHandle_t Sema_Sleep_temp_handle;
static StaticSemaphore_t Sema_Sleep_temp_Buffer;
static uint16_t Sleep_temp;

static SemaphoreHandle_t Sema_Set_temp_handle;
static StaticSemaphore_t Sema_Set_temp_Buffer;
static uint16_t Set_temp;

static SemaphoreHandle_t Sema_threshold_set_temp_handle;
static StaticSemaphore_t Sema_threshold_set_temp_Buffer;
static uint16_t Threshold_set_temp;

static SemaphoreHandle_t Sema_threshold_sleep_temp_handle;
static StaticSemaphore_t Sema_threshold_sleep_temp_Buffer;
static uint16_t Threshold_sleep_temp;

static SemaphoreHandle_t Sema_Positive_offset_temp_handle;
static StaticSemaphore_t Sema_Positive_offset_temp_Buffer;
static uint16_t Positive_offset_temp;

static SemaphoreHandle_t Sema_Negative_offset_temp_handle;
static StaticSemaphore_t Sema_Negative_offset_temp_Buffer;
static uint16_t Negative_offset_temp;


static uint16_t Current_temperature;


void RTE_temperature_init(void){
	Sema_Sleep_temp_handle = xSemaphoreCreateBinaryStatic(&Sema_Sleep_temp_Buffer);
	Sema_Set_temp_handle = xSemaphoreCreateBinaryStatic(&Sema_Set_temp_Buffer);
	Sema_threshold_set_temp_handle = xSemaphoreCreateBinaryStatic(&Sema_threshold_set_temp_Buffer);
	Sema_threshold_sleep_temp_handle = xSemaphoreCreateBinaryStatic(&Sema_threshold_sleep_temp_Buffer);
	Sema_Positive_offset_temp_handle = xSemaphoreCreateBinaryStatic(&Sema_Positive_offset_temp_Buffer);
	Sema_Negative_offset_temp_handle = xSemaphoreCreateBinaryStatic(&Sema_Negative_offset_temp_Buffer);
	
}



void RTE_set_Sleep_temperature(uint16_t u16sleepTemp){
	Sleep_temp = u16sleepTemp;
	xSemaphoreGive(Sema_Sleep_temp_handle);
}

uint16_t RTE_get_Sleep_temperature(void){
	xSemaphoreTake(Sema_Sleep_temp_handle,portMAX_DELAY);
	return Sleep_temp;
}



void RTE_set_Set_temperature(uint16_t u16setTemp){
	Set_temp = u16setTemp;
	xSemaphoreGive(Sema_Set_temp_handle);
}

uint16_t RTE_get_Set_temperature(void){
	xSemaphoreTake(Sema_Set_temp_handle,portMAX_DELAY);
	return Set_temp;
}




void RTE_set_Threshold_set_temperature(uint16_t u16thresholdsetTemp){
	Threshold_set_temp = u16thresholdsetTemp;
	xSemaphoreGive(Sema_threshold_set_temp_handle);
}

uint16_t RTE_get_Threshold_set_temperature(void){
	xSemaphoreTake(Sema_threshold_set_temp_handle,portMAX_DELAY);
	return Threshold_set_temp;
}



void RTE_set_Threshold_sleep_temperature(uint16_t u16thresholdsleepTemp){
	Threshold_sleep_temp = u16thresholdsleepTemp;
	xSemaphoreGive(Sema_threshold_sleep_temp_handle);
}

uint16_t RTE_get_Threshold_sleep_temperature(void){
	xSemaphoreTake(Sema_threshold_sleep_temp_handle,portMAX_DELAY);
	return Threshold_sleep_temp;
}



void RTE_set_Positive_offset_temperature(uint16_t u16positiveOffsetTemp){
	Positive_offset_temp = u16positiveOffsetTemp;
	xSemaphoreGive(Sema_Positive_offset_temp_handle);
}

uint16_t RTE_get_Positive_offset_temperature(void){
	xSemaphoreTake(Sema_Positive_offset_temp_handle,portMAX_DELAY);
	return Positive_offset_temp;
}


void RTE_set_Negative_offset_temperature(uint16_t u16negativeOffsetTemp){
	Negative_offset_temp = u16negativeOffsetTemp;
	xSemaphoreGive(Sema_Negative_offset_temp_handle);
}

uint16_t RTE_get_Negative_offset_temperature(void){
	xSemaphoreTake(Sema_Negative_offset_temp_handle,portMAX_DELAY);
	return Negative_offset_temp;
}




void RTE_set_Current_temperature(uint16_t u16Currenttemp){
	Current_temperature = u16Currenttemp;
}

uint16_t RTE_get_Current_temperature(void){
	return Current_temperature;
}
