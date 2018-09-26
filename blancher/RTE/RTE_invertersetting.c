/*
 * RTE_invertersetting.c
 *
 * Created: 9/20/2018 3:14:40 AM
 *  Author: Mohab Adel
 */ 
// gear ratio r
// rpm max  r
// Conveyor_length  r //
// Driver diameter  r
// time minute r
// time second  r
#include "../RTOS_Includes.h"
#include "RTE_invertersetting.h"
static SemaphoreHandle_t Sema_Gear_ratio_handle;
static StaticSemaphore_t Sema_Gear_ratio_Buffer;
static uint16_t Gear_ratio;

static SemaphoreHandle_t Sema_RPM_max_handle;
static StaticSemaphore_t Sema_RPM_max_Buffer;
static uint16_t RPM_max;

static SemaphoreHandle_t Sema_Conveyor_length_handle;
static StaticSemaphore_t Sema_Conveyor_length_Buffer;
static uint16_t Conveyor_length;

static SemaphoreHandle_t Sema_Driver_diameter_handle;
static StaticSemaphore_t Sema_Driver_diameter_Buffer;
static uint16_t Driver_diameter;

static SemaphoreHandle_t Sema_Time_minute_handle;
static StaticSemaphore_t Sema_Time_minute_Buffer;
static uint16_t Time_minute;

static SemaphoreHandle_t Sema_Time_second_handle;
static StaticSemaphore_t Sema_Time_second_Buffer;
static uint16_t Time_second;

void RTE_invertersetting_init(void){
	Sema_Gear_ratio_handle = xSemaphoreCreateBinaryStatic(&Sema_Gear_ratio_Buffer);
	Sema_RPM_max_handle = xSemaphoreCreateBinaryStatic(&Sema_RPM_max_Buffer);
	Sema_Conveyor_length_handle =  xSemaphoreCreateBinaryStatic(&Sema_Conveyor_length_Buffer);
	Sema_Driver_diameter_handle =  xSemaphoreCreateBinaryStatic(&Sema_Driver_diameter_Buffer);
	Sema_Time_minute_handle =  xSemaphoreCreateBinaryStatic(&Sema_Time_minute_Buffer);
	Sema_Time_second_handle =  xSemaphoreCreateBinaryStatic(&Sema_Time_second_Buffer);
}




void RTE_set_Gear_ratio(uint16_t u16GearRatio){
	Gear_ratio = u16GearRatio;
	//xSemaphoreGive(Sema_Gear_ratio_handle);
}

uint16_t RTE_get_Gear_ratio(void){
	//xSemaphoreTake(Sema_Gear_ratio_handle,portMAX_DELAY);
	return Gear_ratio;
}




void RTE_set_RPM_max(uint16_t u16RPMmax){
	RPM_max = u16RPMmax;
	//xSemaphoreGive(Sema_RPM_max_handle);
}

uint16_t RTE_get_RPM_max(void){
	//xSemaphoreTake(Sema_RPM_max_handle,portMAX_DELAY);
	return RPM_max;
}


void RTE_set_Conveyor_length(uint16_t u16ConveyorLength){
	Conveyor_length = u16ConveyorLength;
	//xSemaphoreGive(Sema_Conveyor_length_handle);
}
uint16_t RTE_get_Conveyor_length(void){
	//xSemaphoreTake(Sema_Conveyor_length_handle,portMAX_DELAY);
	return Conveyor_length;
}


void RTE_set_Driver_diameter(uint16_t u16Driverdiameter){
	Driver_diameter = u16Driverdiameter;
	//xSemaphoreGive(Sema_Driver_diameter_handle);
}

uint16_t RTE_get_Driver_diameter(void){
	//xSemaphoreTake(Sema_Driver_diameter_handle,portMAX_DELAY);
	return Driver_diameter;
}



void RTE_set_Time_minute(uint16_t u16Timeminute){
	Time_minute = u16Timeminute;
	//xSemaphoreGive(Sema_Time_minute_handle);
}

uint16_t RTE_get_Time_minute(void){
	//xSemaphoreTake(Sema_Time_minute_handle,portMAX_DELAY);
	return Time_minute;
}

void RTE_set_Time_second(uint16_t u16Timesecond){
	Time_second = u16Timesecond;
	//xSemaphoreGive(Sema_Time_second_handle);
}

uint16_t RTE_get_Time_second(void){
	//xSemaphoreTake(Sema_Time_second_handle,portMAX_DELAY);
	return Time_second;
}
