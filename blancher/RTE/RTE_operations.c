/*
 * RTE_operations.c
 *
 * Created: 9/20/2018 3:12:47 AM
 *  Author: Mohab Adel
 */ 

//operations required by the user
// System on  r
// start blancher	r
// wash	r	
// calibration tank lvl  r
#include "../RTOS_Includes.h"
#include "RTE_operations.h"


static SemaphoreHandle_t Sema_System_on_handle;
static StaticSemaphore_t Sema_System_on_Buffer;
static uint16_t System_on;

static SemaphoreHandle_t Sema_Start_blancher_Operation_handle;
static StaticSemaphore_t Sema_Start_blancher_Operation_Buffer;
static uint16_t Start_blancher_Operation;

static SemaphoreHandle_t Sema_Wash_Operation_handle;
static StaticSemaphore_t Sema_Wash_Operation_Buffer;
static uint16_t Wash_Operation;

static SemaphoreHandle_t Sema_Tank_Calibration_Operation_handle;
static StaticSemaphore_t Sema_Tank_Calibration_Operation_Buffer;
static uint16_t Tank_Calibration_Operation;

void RTE_operations_init(void){
	Sema_System_on_handle = xSemaphoreCreateBinaryStatic(&Sema_System_on_Buffer);
	Sema_Start_blancher_Operation_handle = xSemaphoreCreateBinaryStatic(&Sema_Start_blancher_Operation_Buffer);
	Sema_Wash_Operation_handle = xSemaphoreCreateBinaryStatic(&Sema_Wash_Operation_Buffer);
	Sema_Tank_Calibration_Operation_handle = xSemaphoreCreateBinaryStatic(&Sema_Tank_Calibration_Operation_Buffer);

}



void RTE_set_System_on(uint16_t u16System_on){
	System_on = u16System_on;
	//xSemaphoreGive(Sema_System_on_handle);
}

uint16_t RTE_get_System_on(void){
	//xSemaphoreTake(Sema_System_on_handle,portMAX_DELAY);
	return System_on;
}




void RTE_set_Start_blancher_Operation(uint16_t u16Start_blancher_Operation){
	Start_blancher_Operation = u16Start_blancher_Operation;
	//xSemaphoreGive(Sema_Start_blancher_Operation_handle);
}

uint16_t RTE_get_Start_blancher_Operation(void){
	//xSemaphoreTake(Sema_Start_blancher_Operation_handle,portMAX_DELAY);
	return Start_blancher_Operation;
}





void RTE_set_Wash_Operation(uint16_t u16Wash_Operation){
	Wash_Operation = u16Wash_Operation;
	//xSemaphoreGive(Sema_Wash_Operation_handle);
}

uint16_t RTE_get_Wash_Operation(void){
	//xSemaphoreTake(Sema_Wash_Operation_handle,portMAX_DELAY);
	return Wash_Operation;
}






void RTE_set_Tank_Calibration_Operation(uint16_t u16Tank_Calibration_Operation){
	Tank_Calibration_Operation = u16Tank_Calibration_Operation;
	//xSemaphoreGive(Sema_Tank_Calibration_Operation_handle);
}

uint16_t RTE_get_Tank_Calibration_Operation(void){
	//xSemaphoreTake(Sema_Tank_Calibration_Operation_handle,portMAX_DELAY);
	return Tank_Calibration_Operation;
}




