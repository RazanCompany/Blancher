/*
 * RTE_Tankslevels.c
 *
 * Created: 9/20/2018 3:10:27 AM
 *  Author: Mohab Adel
 */ 
// tank level 
// blancher level 


#include "../RTOS_Includes.h"
#include "RTE_tankslevels.h"

static SemaphoreHandle_t Sema_tank_level_handle;
static StaticSemaphore_t Sema_tank_level_Buffer;
static uint16_t tank_level;

static SemaphoreHandle_t Sema_blancher_level_handle;
static StaticSemaphore_t Sema_blancher_level_Buffer;
static uint16_t blancher_level;

void RTE_levels_init(void)
{
	Sema_tank_level_handle = xSemaphoreCreateBinaryStatic(&Sema_tank_level_Buffer);
	Sema_blancher_level_handle = xSemaphoreCreateBinaryStatic(&Sema_blancher_level_Buffer);
}


void RTE_set_tank_level(uint16_t u16tank_level)
{
	tank_level = u16tank_level ;
    //xSemaphoreGive(Sema_tank_level_handle);
}

uint16_t RTE_get_tank_level(void)
{
	//xSemaphoreTake(Sema_tank_level_handle,portMAX_DELAY);
	return tank_level ;
}

void RTE_set_blancher_level(uint16_t u16blancher_level)
{
	tank_level = u16blancher_level ;
	//xSemaphoreGive(Sema_blancher_level_handle);
}

uint16_t RTE_get_blancher_level(void)
{
	//xSemaphoreTake(Sema_blancher_level_handle,portMAX_DELAY);
	return blancher_level ;
}


